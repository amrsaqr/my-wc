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
using std::nullopt;
using std::make_optional;

Driver::Driver(const Options& options, vector<string>&& files_paths, Counter&& counter) :
options_(options), files_paths_(std::move(files_paths)), counter_(std::move(counter)) {}

void Driver::Run() {
  bool is_multibyte_locale = IsMultibyteLocale();

  // If no files were passed to the program, then we count from standard input
  if (files_paths_.empty()) {
    Counts counts;
    string error_output;
    bool counting_successful = counter_.Count(cin, options_, is_multibyte_locale, &counts, &error_output);

    results_.emplace_back(counting_successful,
      error_output.empty() ? nullopt : make_optional(std::move(error_output)),
      nullopt,
      counts);
  } else {  // Files paths were passed to the program, so we count for each file
    for (string& file_path : files_paths_) {
      Counts counts;
      string error_output;
      bool counting_successful = false;

      ifstream file(file_path, ios::in);
      if (!file.is_open()) {
        error_output = "No such file or directory";
      } else {
        counting_successful = counter_.Count(file, options_, is_multibyte_locale, &counts, &error_output);
      }

      results_.emplace_back(counting_successful,
      error_output.empty() ? nullopt : make_optional(std::move(error_output)),
      std::move(file_path),
      counts);
    }
  }
}

bool Driver::IsMultibyteLocale() {
  if (!setlocale(LC_CTYPE, "")) {
    cerr << "Warning: Could not get user-defined locale. Assuming no multibyte characters support." << endl;
    return false;
  }

  return (MB_CUR_MAX > 1);
}

void Driver::Print(ostream& out, const Counts& counts, const optional<string>& optional_file_path) const {
  if (options_.CountingLines()) {
    out << setw(8) << counts.GetLines();
  }

  if (options_.CountingWords()) {
    out << setw(8) << counts.GetWords();
  }

  if (options_.CountingChars()) {
    out << setw(8) << counts.GetChars();
  }

  if (options_.CountingBytes()) {
    out << setw(8) << counts.GetBytes();
  }

  if (optional_file_path.has_value()) {
    out << ' ' << optional_file_path.value();
  }

  out << endl;
}

int Driver::PrintResultsTo(ostream& out) const {
  bool all_counting_successful = true;
  size_t successful_counts = 0;
  Counts total_counts;

  for (const auto& result : results_) {
    if (result.error_output.has_value()) {
      if (result.file_path.has_value()) {
        out << result.file_path.value() << ": ";
      }

      out << result.error_output.value() << endl;
    }

    if (result.successful) {
      Print(out, result.counts, result.file_path);
      ++successful_counts;
      total_counts += result.counts;
    }

    all_counting_successful &= result.successful;
  }

  // Only print a total line if successful file counts are more than 1
  if (successful_counts > 1) {
    Print(out, total_counts, "total");
  }

  return all_counting_successful ? 0 : 1;
}
