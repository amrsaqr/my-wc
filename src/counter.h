//
// Copyright 2024 Amr Saqr
//

#ifndef COUNTER_H_
#define COUNTER_H_

#include <string>
#include <vector>

#include "options.h"

using std::string;
using std::vector;

class Counter {
 public:
  explicit Counter(const Options& options);

  Counter(const Options& options, string file_path);

  // Returns false if and only if reading_from_file_ is true and a failure
  // happened while opening the file
  bool Count();

  void Print() const;

 private:
  const Options options_;
  const string file_path_;

  bool reading_from_file_;
  size_t bytes_count_{0};
  size_t lines_count_{0};
  size_t words_count_{0};
  size_t chars_count_{0};
};

#endif  // COUNTER_H_
