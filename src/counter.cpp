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
  try {
    mbstate_t mbstate = mbstate_t();
    bool last_char_is_space = true;  // assuming a space before reading any
                                     // bytes to assist with counting words
    unsigned int left_over_bytes = 0;

    while (true) {
      in.read(buffer_ + left_over_bytes, kBufferSize - left_over_bytes);
      const streamsize read_bytes = in.gcount();
      buffer_[left_over_bytes + read_bytes] = '\0';

      if (read_bytes == 0) {
        break;
      }

      if (options_.CountingBytes()) {
        counts->IncBytes(read_bytes);
      }

      if (options_.CountingWords() || options_.CountingLines()) {
        const char* begin_ptr = buffer_ + left_over_bytes;
        const char* end_ptr = begin_ptr + read_bytes;

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

      if (options_.CountingChars()) {
        const char* begin_ptr = buffer_ + left_over_bytes;
        const char* end_ptr = begin_ptr + read_bytes;
        size_t converted_bytes = 0;

        // try adding the condition of buffer_ptr < buffer_end_ptr
        while (begin_ptr < end_ptr &&
               (converted_bytes = mbrtowc(nullptr, begin_ptr,
                                          end_ptr - begin_ptr, &mbstate)) > 0) {
          counts->IncChars();
          begin_ptr += converted_bytes;
        }

        if (begin_ptr == end_ptr) {
          left_over_bytes = 0;
        } else if (converted_bytes == -1) {
          *error_output = "Encountered invalid character";
          return false;
        } else if (converted_bytes == -2) {
          left_over_bytes = end_ptr - begin_ptr;
          memcpy(buffer_, buffer_ + (kBufferSize - left_over_bytes),
                 left_over_bytes);
        }
      }
    }

    return true;
  } catch (const std::ios_base::failure& e) {
    ostringstream oss;
    oss << "Error reading file (" << e.what() << ')';
    *error_output = oss.str();
    return false;
  }
}
