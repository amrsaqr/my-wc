//
// Copyright 2026 Amr Saqr
//

#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "options.h"
#include "counter.h"
#include "counts.h"

using std::string;
using std::vector;
using std::optional;
using std::ostream;
using std::string_view;
using std::nullopt;

class Driver {
 public:
  [[nodiscard]] static int RunAndPrintResults(ostream& out, const Options& options,
    const vector<string>&files_paths, const Counter& counter);

 protected:
  static void PrintResultLine(ostream& out, const Options& options, bool counting_successful,
    const Counts& counts, string_view error_output, const optional<string_view>& optional_file_path = nullopt);

  /**
   * Checks the user-defined locale for multibyte characters support
   * @return true if multibyte characters are supported, false otherwise
   */
  [[nodiscard]] static bool IsMultibyteLocale();
};

#endif  // DRIVER_H_
