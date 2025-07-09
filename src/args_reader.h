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

  void Read(int argc, char** argv);

  vector<char> GetOptions();

  vector<string> GetFilesPaths();

 private:
  vector<char> options_;
  vector<string> files_paths_;
};

#endif  // ARGS_READER_H_
