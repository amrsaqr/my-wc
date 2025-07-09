//
// Copyright 2024 Amr Saqr
//

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <vector>
using std::vector;

class Options {
 public:
  explicit Options(const vector<char>& options);
  bool CountingBytes() const;
  bool CountingLines() const;
  bool CountingWords() const;
  bool CountingChars() const;

 private:
  bool counting_bytes_;
  bool counting_lines_;
  bool counting_words_;
  bool counting_chars_;
};

#endif  // OPTIONS_H_
