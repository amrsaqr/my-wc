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


void Print(const Options& options, const Counts& counts, const string* file_path = nullptr) {
  if (options.CountingLines()) {
    cout << setw(8) << counts.GetLines();
  }

  if (options.CountingWords()) {
    cout << setw(8) << counts.GetWords();
  }

  if (options.CountingChars()) {
    cout << setw(8) << counts.GetChars();
  }

  if (options.CountingBytes()) {
    cout << setw(8) << counts.GetBytes();
  }

  if (file_path) {
    cout << ' ' << *file_path;
  }

  cout << endl;
}

int main(int argc, char** argv) {
  ArgsReader args_reader;
  args_reader.Read(argc, argv);

  Options options(args_reader.GetOptions());
  auto files_paths = args_reader.GetFilesPaths();

  Counter counter(options);
  bool file_path_failed = false;

  if (files_paths.empty()) {
    Counts counts;
    string error_output;

    if (counter.Count(&counts, &error_output)) {
      Print(options, counts);
    } else {
      cout << error_output << endl;
    }
  } else {
    Counts total_counts;
    for (const string& file_path : files_paths) {
      Counts counts;
      string error_output;

      if (counter.Count(file_path, &counts, &error_output)) {
        // print, and sum in totals
        Print(options, counts, &file_path);
        total_counts += counts;
      } else {
        cout << file_path << ": " << error_output << endl;
        file_path_failed = true;
      }
    }

    if (files_paths.size() > 1) {
      string total_as_file_path = "total";
      Print(options, total_counts, &total_as_file_path);
    }
  }

  return file_path_failed ? 1 : 0;
}
