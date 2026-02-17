//
// Copyright 2026 Amr Saqr
//

#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>
#include <vector>
#include <optional>

#include "options.h"
#include "counter.h"

using std::string;
using std::vector;
using std::optional;
using std::string_view;

class Driver {
 public:
  Driver(const Options& options, vector<string>&& files_paths, Counter&& counter);

  [[nodiscard]] int Run() const;

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
  void Print(const Counts& counts, const optional<string_view>& optional_file_path = {}) const;

  Options options_;
  vector<string> files_paths_;
  Counter counter_;
};

#endif  // DRIVER_H_
