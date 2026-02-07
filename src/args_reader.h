//
// Copyright 2024 Amr Saqr
//

#ifndef ARGS_READER_H_
#define ARGS_READER_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

class ArgsReader {
 public:
  ArgsReader() = default;

  void Read(int argc, const char* const* argv);

  [[nodiscard]] const vector<char>& GetOptions() const;

  [[nodiscard]] const vector<string>& GetFilesPaths() const;

 private:
  vector<char> options_;
  vector<string> files_paths_;
};

#endif  // ARGS_READER_H_
