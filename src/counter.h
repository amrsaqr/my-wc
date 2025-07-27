//
// Copyright 2024 Amr Saqr
//

#ifndef COUNTER_H_
#define COUNTER_H_

#include <string>
#include <vector>

#include "counts.h"
#include "options.h"

using std::string;
using std::vector;

class Counter {
 public:
  explicit Counter(const Options& options);

  /**
   * For counting from standard stream
   * @param counts an out param for the Counts object
   * @param error_output an out param for the error (NULL if no error happened)
   * @return true if counting was successful, and false otherwise (in case of a
   * stream error)
   */
  bool Count(Counts* counts, string* error_output);

  /**
   * For counting from a file stream
   * @param file_path the path to the file
   * @param counts an out param for the Counts object
   * @param error_output an out param for the error (NULL if no error happened)
   * @return true if counting was successful, and false otherwise (in case of a
   * stream error)
   */
  bool Count(const string& file_path, Counts* counts, string* error_output);

 private:
  /**
   * A helper function to implement the counting logic
   * @param in the input stream object (can be standard stream or file stream)
   * @param counts an out param for the Counts object
   * @param error_output an out param for the error (NULL if no error happened)
   * @return true if counting was successful, and false otherwise (in case of a
   * stream error)
   */
  bool Count(std::istream& in, Counts* counts, string* error_output);

  /**
   * A helper function that handles incrementing the lines and words count
   * @param wide_char the wide character to check against
   * @param last_char_is_space an in/out param that says whether the character
   * just before "wide_char" was a white-space character or not, and should be
   * updated depending on wide_char
   * @param counts an out param for the Counts object
   */
  void HandleLinesAndWords(wchar_t wide_char, bool& last_char_is_space,
                           Counts* counts);

  const Options options_;

  // Use 64KB read chunks to improve the performance of reading from input
  // streams
  static constexpr unsigned int kBufferSize = 64 * 1024;

  // The buffer for reading from input streams, of size kBufferSize plus one
  // more for null-termination
  char buffer_[kBufferSize + 1]{};

  // Whether the user-defined locale supports multibyte characters
  bool is_multibyte_locale_;
};

#endif  // COUNTER_H_
