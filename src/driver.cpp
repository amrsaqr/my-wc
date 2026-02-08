//
// Copyright 2026 Amr Saqr
//

#include "driver.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "options.h"
#include "counter.h"

using std::cerr;
using std::endl;
using std::setw;
using std::cout;
using std::cin;
using std::ios;
using std::ifstream;

Driver::Driver(int argc, const char* const* argv) {
  args_reader_.Read(argc, argv);
}

int Driver::Run() const {
  bool is_multibyte_locale = IsMultibyteLocale();

  Options options(args_reader_.GetOptions());
  const vector<string>& files_paths = args_reader_.GetFilesPaths();

  Counter counter;
  bool all_counting_successful = true;

  // If no files were passed to the program, then we count from standard input
  if (files_paths.empty()) {
    Counts counts;
    string error_output;

    all_counting_successful = counter.Count(cin, options, is_multibyte_locale, &counts, &error_output);

    if (!error_output.empty()) {
      cout << error_output << endl;
    }

    if (all_counting_successful) {
      Print(options, counts);
    }
  } else {  // Files paths were passed to the program, so we count for each file
    Counts total_counts;
    size_t successful_counts = 0;

    for (const string& file_path : files_paths) {
      Counts counts;
      string error_output;

      bool counting_successful = false;
      ifstream file(file_path, ios::in);
      if (!file.is_open()) {
        error_output = "No such file or directory";
      } else {
        counting_successful = counter.Count(file, options, is_multibyte_locale, &counts, &error_output);
      }

      if (!error_output.empty()) {
        cout << file_path << ": " << error_output << endl;
      }

      if (counting_successful) {
        Print(options, counts, file_path);
        total_counts += counts;
        ++successful_counts;
      }

      all_counting_successful &= counting_successful;
    }

    // Only print a total line if successful file counts are more than 1
    if (successful_counts > 1) {
      const string total_as_file_path = "total";
      Print(options, total_counts, total_as_file_path);
    }
  }

  return all_counting_successful ? 0 : 1;
}

bool Driver::IsMultibyteLocale() {
  if (!setlocale(LC_CTYPE, "")) {
    cerr << "Warning: Could not get user-defined locale. Assuming no multibyte characters support." << endl;
    return false;
  }

  return (MB_CUR_MAX > 1);
}

void Driver::Print(const Options& options, const Counts& counts, const optional<string_view>& optional_file_path) {
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

  if (optional_file_path.has_value()) {
    cout << ' ' << optional_file_path.value();
  }

  cout << endl;
}
