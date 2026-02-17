//
// Copyright 2026 Amr Saqr
//

#include "driver.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#include "options.h"
#include "counter.h"

using std::cerr;
using std::endl;
using std::setw;
using std::cout;
using std::cin;
using std::ios;
using std::setw;
using std::ifstream;

Driver::Driver(const Options& options, vector<string>&& files_paths, Counter&& counter) :
options_(options), files_paths_(std::move(files_paths)), counter_(std::move(counter)) {}

int Driver::Run() const {
  bool is_multibyte_locale = IsMultibyteLocale();
  bool all_counting_successful = true;

  // If no files were passed to the program, then we count from standard input
  if (files_paths_.empty()) {
    Counts counts;
    string error_output;

    all_counting_successful = counter_.Count(cin, options_, is_multibyte_locale, &counts, &error_output);

    if (!error_output.empty()) {
      cout << error_output << endl;
    }

    if (all_counting_successful) {
      Print(counts);
    }
  } else {  // Files paths were passed to the program, so we count for each file
    Counts total_counts;
    size_t successful_counts = 0;

    for (const string& file_path : files_paths_) {
      Counts counts;
      string error_output;

      bool counting_successful = false;
      ifstream file(file_path, ios::in);
      if (!file.is_open()) {
        error_output = "No such file or directory";
      } else {
        counting_successful = counter_.Count(file, options_, is_multibyte_locale, &counts, &error_output);
      }

      if (!error_output.empty()) {
        cout << file_path << ": " << error_output << endl;
      }

      if (counting_successful) {
        Print(counts, file_path);
        total_counts += counts;
        ++successful_counts;
      }

      all_counting_successful &= counting_successful;
    }

    // Only print a total line if successful file counts are more than 1
    if (successful_counts > 1) {
      const string total_as_file_path = "total";
      Print(total_counts, total_as_file_path);
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

void Driver::Print(const Counts& counts, const optional<string_view>& optional_file_path) const {
  if (options_.CountingLines()) {
    cout << setw(8) << counts.GetLines();
  }

  if (options_.CountingWords()) {
    cout << setw(8) << counts.GetWords();
  }

  if (options_.CountingChars()) {
    cout << setw(8) << counts.GetChars();
  }

  if (options_.CountingBytes()) {
    cout << setw(8) << counts.GetBytes();
  }

  if (optional_file_path.has_value()) {
    cout << ' ' << optional_file_path.value();
  }

  cout << endl;
}
