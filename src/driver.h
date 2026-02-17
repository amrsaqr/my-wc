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
#include "count_result.h"

using std::string;
using std::vector;
using std::optional;
using std::ostream;

class Driver {
 public:
  Driver(const Options& options, vector<string>&& files_paths, Counter&& counter);

  void Run();

  [[nodiscard]] int PrintResultsTo(ostream& out) const;

 protected:
  /**
   * Checks the user-defined locale for multibyte characters support
   * @return true if multibyte characters are supported, false otherwise
   */
  [[nodiscard]] static bool IsMultibyteLocale();

  /**
 * Print counts depending on program options
 * @param counts The counts
 * @param optional_file_path An optional file path for which the counts have been done
 */
  void Print(ostream& out, const Counts& counts, const optional<string>& optional_file_path = {}) const;

  Options options_;
  vector<string> files_paths_;
  Counter counter_;
  vector<CountResult> results_;
};

#endif  // DRIVER_H_
