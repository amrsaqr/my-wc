//
// Copyright 2024 Amr Saqr
//

#include "args_reader.h"

#include <string>
#include <vector>

void ArgsReader::Read(int argc, const char* const* argv) {
  // First read options until done, or you hit a potential file path (argument
  // that doesn't start with a '-')
  int i = 0;
  for (; i < argc && argv[i][0] == '-'; ++i) {
    for (int j = 1; argv[i][j]; ++j) {
      options_.emplace_back(argv[i][j]);
    }
  }

  // Now that we're done reading options, any argument that follows is
  // considered a file path
  for (; i < argc; ++i) {
    files_paths_.emplace_back(argv[i]);
  }
}

const vector<char>& ArgsReader::GetOptions() const { return options_; }

const vector<string>& ArgsReader::GetFilesPaths() const { return files_paths_; }
