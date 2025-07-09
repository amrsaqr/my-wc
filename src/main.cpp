//
// Copyright 2024 Amr Saqr
//

#include <iomanip>
#include <iostream>
#include <string>

#include "args_reader.h"
#include "counter.h"
#include "options.h"
using std::cout;
using std::endl;
using std::setw;

int main(int argc, char** argv) {
  bool file_path_failed = false;

  ArgsReader args_reader;
  args_reader.Read(argc, argv);

  Options options(args_reader.GetOptions());
  auto files_paths = args_reader.GetFilesPaths();

  if (files_paths.empty()) {
    Counter counter(options);
    counter.Count();
    counter.Print();
  } else {
    for (const string& file_path : files_paths) {
      Counter counter(options, file_path);
      if (counter.Count()) {
        counter.Print();
      } else {
        file_path_failed = true;
      }
    }
  }

  return file_path_failed ? 1 : 0;
}
