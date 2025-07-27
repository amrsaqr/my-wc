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

/**
 * Print counts depending on program options
 * @param options The arguments passed to the program
 * @param counts The counts based on options
 * @param file_path An optional file path for which the counts have been done
 */
void Print(const Options& options, const Counts& counts,
           const string* file_path = nullptr) {
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
  // Extract the program arguments
  ArgsReader args_reader;
  args_reader.Read(argc, argv);

  // Build the counting options using the arguments
  Options options(args_reader.GetOptions());
  auto files_paths = args_reader.GetFilesPaths();

  // Build a counter object using the options
  Counter counter(options);
  bool all_counting_successful = true;

  // If no files were passed to the program, then we count from standard input
  if (files_paths.empty()) {
    Counts counts;
    string error_output;

    bool counting_successful = counter.Count(&counts, &error_output);

    if (!error_output.empty()) {
      cout << error_output << endl;
    }

    if (counting_successful) {
      Print(options, counts);
    }

    all_counting_successful = counting_successful;
  } else {  // Files paths were passed to the program, so we count for each file
    Counts total_counts;
    size_t successful_counts = 0;

    for (const string& file_path : files_paths) {
      Counts counts;
      string error_output;

      bool counting_successful = counter.Count(file_path, &counts, &error_output);

      if (!error_output.empty()) {
        cout << file_path << ": " << error_output << endl;
      }

      if (counting_successful) {
        Print(options, counts, &file_path);
        total_counts += counts;
        ++successful_counts;
      }

      all_counting_successful &= counting_successful;
    }

    // Only print a total line if successful file counts are more than 1
    if (successful_counts > 1) {
      const string total_as_file_path = "total";
      Print(options, total_counts, &total_as_file_path);
    }
  }

  return all_counting_successful ? 0 : 1;
}
