//
// Copyright 2024 Amr Saqr
//

#include "counter.h"

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <istream>
#include <memory>
#include <sstream>
#include <string>
using std::cerr;
using std::cin;
using std::endl;
using std::ifstream;
using std::istream;
using std::make_unique;
using std::ostringstream;
using std::streamsize;
using std::unique_ptr;

Counter::Counter(const Options& options) : options_(options) {
  // TODO(amrsaqr): add a try catch here and improve multibyte checking.
  // Check the user-defined locale for multibyte characters support
  string current_locale(setlocale(LC_CTYPE, ""));
  if (current_locale.find("UTF-8") != string::npos ||
      current_locale.find("eucjp") != string::npos ||
      current_locale.find("GBK") != string::npos ||
      current_locale.find("Big5") != string::npos) {
    is_multibyte_locale_ = true;
  } else {
    is_multibyte_locale_ = false;
  }
}

bool Counter::Count(Counts* counts, string* error_output) {
  return Count(cin, counts, error_output);
}

bool Counter::Count(const string& file_path, Counts* counts,
                    string* error_output) {
  ifstream file(file_path, std::ios::in);
  if (!file.is_open()) {
    *error_output = "No such file or directory";
    return false;
  }

  file.exceptions(std::ios::badbit);
  return Count(file, counts, error_output);
}

bool Counter::Count(istream& in, Counts* counts, string* error_output) {
  // - A pointer to the conversion state object used for continuing the
  // conversion of a multibyte character across two different mbrtowc calls
  // - Only points to a state object if user-defined locale supports multibyte,
  // and we're counting characters
  unique_ptr<mbstate_t> mbstate =
      is_multibyte_locale_ && options_.CountingChars() ? std::make_unique<mbstate_t>() : nullptr;

  // Assuming a space before reading any bytes to assist with counting words
  bool last_char_is_space = true;

  // A flag to be set when we encounter an invalid byte sequence
  bool invalid_byte_sequence_encountered = false;

  // A loop that read the entire input stream (standard or file) in byte chunks
  // of kBufferSize
  while (true) {
    try {
      // Read from the input stream
      in.read(buffer_, kBufferSize);
    } catch (const std::ios_base::failure& e) {
      ostringstream oss;
      oss << "Error reading file (" << e.what() << ')';
      *error_output = oss.str();
      return false;
    }

    // Count how many bytes were read exactly because in the last iteration we
    // might not fill the whole buffer, so we can't assume we read the whole
    // kBufferSize
    const streamsize read_bytes = in.gcount();

    // If no bytes were read, we're simply done
    if (read_bytes == 0) {
      break;
    }

    // Add null-termination after the last read byte
    buffer_[read_bytes] = '\0';

    // If we should count bytes, add the read bytes to the Counts object bytes
    if (options_.CountingBytes()) {
      counts->IncBytes(read_bytes);
    }

    // This decides if we're going to iterate on bytes or wide characters
    if (is_multibyte_locale_ && options_.CountingChars()) {
      // The number of converted bytes in each mbrtowc call, to be used for
      // advancing the begin_ptr
      int converted_bytes = 0;

      // The wide character used for checking
      wchar_t wide_char;

      // Check the mbrtowc reference here for detailed explanation
      // https://en.cppreference.com/w/cpp/string/multibyte/mbrtowc.html
      // As long as begin_ptr hasn't reached the end_ptr yet, try to convert a
      // multibyte character and modify the counts object depending on options
      for (const char *begin_ptr = buffer_, *end_ptr = buffer_ + read_bytes;
           begin_ptr < end_ptr; begin_ptr += converted_bytes) {
        converted_bytes = static_cast<int>(
            mbrtowc(&wide_char, begin_ptr, end_ptr - begin_ptr, mbstate.get()));

        // Break if null or incomplete valid sequence encountered
        if (converted_bytes == 0 || converted_bytes == -2) {
          break;
        }

        // Special handling if an invalid sequence is encountered to make the
        // program more resilient to malformed input (similar to how the
        // original wc handles it)
        if (converted_bytes == -1) {
          // Set the invalid sequence flag
          invalid_byte_sequence_encountered = true;

          // Reset the mbstate_t object
          mbstate = make_unique<mbstate_t>();

          // Advance by 1 byte
          converted_bytes = 1;

          // Consider an invalid byte as a character
          counts->IncChars();

          continue;
        }

        if (options_.CountingLines() && wide_char == L'\n') {
          counts->IncLines();
        }

        if (options_.CountingWords()) {
          if (last_char_is_space && !iswspace(wide_char)) {
            counts->IncWords();
            last_char_is_space = false;
          } else if (!last_char_is_space && iswspace(wide_char)) {
            last_char_is_space = true;
          }
        }

        counts->IncChars();
      }
    } else {
      // Only iterate on the buffer if we should count words or lines
      if (options_.CountingWords() || options_.CountingLines()) {
        for (const char *begin_ptr = buffer_, *end_ptr = buffer_ + read_bytes;
             begin_ptr < end_ptr; ++begin_ptr) {
          if (options_.CountingLines() && *begin_ptr == '\n') {
            counts->IncLines();
          }

          if (options_.CountingWords()) {
            if (last_char_is_space && !isspace(*begin_ptr)) {
              counts->IncWords();
              last_char_is_space = false;
            } else if (!last_char_is_space && isspace(*begin_ptr)) {
              last_char_is_space = true;
            }
          }
        }
      }

      // If we should count characters, it should be the bytes count because
      // user-defined locale doesn't support multibyte
      if (options_.CountingChars()) {
        counts->IncChars(read_bytes);
      }
    }
  }

  // If we encountered an invalid sequence, we set the error output and still
  // return true because we chose a non-strict approach with malformed sequences
  if (invalid_byte_sequence_encountered) {
    *error_output = "Illegal byte sequence";
  }

  return true;
}
