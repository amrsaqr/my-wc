//
// Copyright 2026 Amr Saqr
//

#include "driver.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

#include "options.h"
#include "counter.h"

using std::cerr;
using std::endl;
using std::setw;
using std::cin;
using std::ios;
using std::setw;
using std::ifstream;

int Driver::RunAndPrintResults(ostream& out, const Options& options,
                               const vector<string>& files_paths,
                               const Counter& counter) {
  bool is_multibyte_locale = IsMultibyteLocale();
  bool all_counting_successful = true;

  // If no files were passed to the program, then we count from standard input
  if (files_paths.empty()) {
    Counts counts;
    string error_output;
    all_counting_successful = counter.Count(cin, options, is_multibyte_locale, &counts, &error_output);
    PrintResultLine(out, options, all_counting_successful, counts, error_output);
  } else {  // Files paths were passed to the program, so we count for each file
    size_t successful_counts = 0;
    Counts total_counts;

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

      PrintResultLine(out, options, counting_successful, counts, error_output, file_path);

      if (counting_successful) {
        ++successful_counts;
        total_counts += counts;
      }

      all_counting_successful &= counting_successful;
    }

    // Only print a total line if successful file counts are more than 1
    if (successful_counts > 1) {
      PrintResultLine(out, options, true, total_counts, "", "total");
    }
  }

  return all_counting_successful ? 0 : 1;
}

void Driver::PrintResultLine(
    ostream& out, const Options& options, bool counting_successful,
    const Counts& counts, string_view error_output,
    const optional<string_view>& optional_file_path) {
  if (!error_output.empty()) {
    if (optional_file_path.has_value()) {
      out << optional_file_path.value() << ": ";
    }

    out << error_output << endl;
  }

  if (counting_successful) {
    if (options.CountingLines()) {
      out << setw(8) << counts.GetLines();
    }

    if (options.CountingWords()) {
      out << setw(8) << counts.GetWords();
    }

    if (options.CountingChars()) {
      out << setw(8) << counts.GetChars();
    }

    if (options.CountingBytes()) {
      out << setw(8) << counts.GetBytes();
    }

    if (optional_file_path.has_value()) {
      out << ' ' << optional_file_path.value();
    }

    out << endl;
  }
}

bool Driver::IsMultibyteLocale() {
  if (!setlocale(LC_CTYPE, "")) {
    cerr << "Warning: Could not get user-defined locale. Assuming no multibyte characters support." << endl;
    return false;
  }

  return (MB_CUR_MAX > 1);
}
