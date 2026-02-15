//
// Copyright 2024 Amr Saqr
//

#ifndef COUNTER_H_
#define COUNTER_H_

#include <string>
#include <vector>
#include <memory>

#include "counts.h"
#include "options.h"

using std::string;
using std::vector;
using std::unique_ptr;

class Counter {
 public:
  explicit Counter(unsigned int buffer_size = kBufferSize);

  /**
   * Given an input stream and options, it implements the counting algorithm
   * @param in the input stream object (can be standard stream or file stream)
   * @param options the program options for counting
   * @param is_multibyte_locale whether the locale is multibyte or not
   * @param counts an out param for the Counts object
   * @param error_output an out param for the error (NULL if no error happened)
   * @return true if counting was successful, and false otherwise (in case of a
   * stream error)
   */
  bool Count(std::istream& in, const Options& options, bool is_multibyte_locale,
    Counts* counts, string* error_output) const;

  virtual ~Counter();

 private:
  /**
   * A helper function that handles incrementing the lines and words count
   * @param wide_char the wide character to check against
   * @param last_char_is_space an in/out param that says whether the character
   * just before "wide_char" was a white-space character or not, and should be
   * updated depending on wide_char
   * @param counts an out param for the Counts object
   */
  static void HandleLinesAndWords(wchar_t wide_char, bool counting_lines,
    bool counting_words, bool& last_char_is_space, Counts* counts);

  // Use 64KB read chunks to improve the performance of reading from input
  // streams
  static constexpr unsigned int kBufferSize = 64 * 1024;

  // The buffer for reading from input streams
  char* buffer_;

  // The buffer size to use
  unsigned int buffer_size_;
};

#endif  // COUNTER_H_
