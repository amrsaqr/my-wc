//
// Copyright 2024 Amr Saqr
//

#include "counter.h"

#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
using std::cin;
using std::ifstream;
using std::istream;
using std::ostringstream;
using std::streamsize;

Counter::Counter(const Options& options) : options_(options) {}

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
  // The conversion state object used for continuing the conversion of a
  // multibyte character across two different mbrtowc calls
  mbstate_t mbstate = mbstate_t();
  // Assuming a space before reading any bytes to assist with counting words
  bool last_char_is_space = true;
  // The bytes left over from the last iteration, so that we start reading
  // into the buffer after those leftovers
  unsigned int left_over_bytes = 0;

  // A loop that read the entire input stream (standard or file) in byte chunks
  // of kBufferSize
  while (true) {
    try {
      // Read from the input stream starting from right after the leftover bytes
      in.read(buffer_ + left_over_bytes, kBufferSize - left_over_bytes);
    } catch (const std::ios_base::failure& e) {
      ostringstream oss;
      oss << "Error reading file (" << e.what() << ')';
      *error_output = oss.str();
      return false;
    }

    // Count how many bytes were read exactly because in the last iteration we
    // might not fill the whole buffer
    const streamsize read_bytes = in.gcount();

    // Null terminate after the last read byte
    buffer_[left_over_bytes + read_bytes] = '\0';

    // If no bytes were read, we're simply done
    if (read_bytes == 0) {
      break;
    }

    // If we should count bytes, add the read bytes to the Counts object bytes
    if (options_.CountingBytes()) {
      counts->IncBytes(read_bytes);
    }

    // If we should count words or lines
    if (options_.CountingWords() || options_.CountingLines()) {
      // The begin_ptr should start right after the leftovers because those
      // were already processed
      const char* begin_ptr = buffer_ + left_over_bytes;
      // The end_ptr should be right after the read bytes
      const char* end_ptr = begin_ptr + read_bytes;

      // Loop through the [begin_ptr, end_ptr) range and do two things:
      // 1. Count the newline occurrences and add to the Counts object lines
      // 2. Count any transition from a space character to a non-space
      // character as a new word and add to the Counts object words
      for (; begin_ptr < end_ptr; ++begin_ptr) {
        if (*begin_ptr == '\n') {
          counts->IncLines();
        }

        if (last_char_is_space && !isspace(*begin_ptr)) {
          counts->IncWords();
          last_char_is_space = false;
        } else if (!last_char_is_space && isspace(*begin_ptr)) {
          last_char_is_space = true;
        }
      }
    }

    // If we should count characters
    if (options_.CountingChars()) {
      // The begin_ptr should start right after the leftovers because those
      // were already processed
      const char* begin_ptr = buffer_ + left_over_bytes;
      // The end_ptr should be right after the read bytes
      const char* end_ptr = begin_ptr + read_bytes;
      // The number of converted bytes in each mbrtowc call to be used for
      // advancing the begin_ptr
      size_t converted_bytes = 0;

      // Check the mbrtowc reference here for detailed explanation
      // https://en.cppreference.com/w/cpp/string/multibyte/mbrtowc.html
      // As long as begin_ptr hasn't reached the end_ptr yet, try to convert a
      // multibyte character and increment the Counts object chars
      while (begin_ptr < end_ptr &&
             (converted_bytes = mbrtowc(nullptr, begin_ptr, end_ptr - begin_ptr,
                                        &mbstate)) > 0) {
        counts->IncChars();
        begin_ptr += converted_bytes;
      }

      // After the loop exit, there are 3 possible outcomes
      // 1. begin_ptr is pointing at end_ptr, which means the examined range
      // had all the multibyte characters fitted perfectly
      // 2. We got an error of (-1), which means the function encountered an
      // invalid multibyte sequence
      // 3. We got a result of (-2), which means the function encountered a
      // valid but incomplete multibyte sequence, which means it should be
      // continued in the next iteration (next buffer read)
      if (begin_ptr == end_ptr) {
        left_over_bytes = 0;
      } else if (converted_bytes == -1) {
        *error_output = "Encountered invalid character";
        return false;
      } else if (converted_bytes == -2) {
        // Here we calculate the leftovers, and copy them to the beginning of
        // the buffer
        left_over_bytes = end_ptr - begin_ptr;
        memcpy(buffer_, buffer_ + (kBufferSize - left_over_bytes),
               left_over_bytes);
      }
    }
  }

  return true;
}
