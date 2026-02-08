//
// Copyright 2026 Amr Saqr
//

#ifndef DRIVER_H_
#define DRIVER_H_

#include <string>
#include <vector>
#include <optional>

#include "args_reader.h"
#include "options.h"
#include "counts.h"

using std::string;
using std::vector;
using std::optional;
using std::string_view;

class Driver {
 public:
  Driver(int argc, const char* const* argv);

  [[nodiscard]] int Run() const;

 protected:
  /**
   * Checks the user-defined locale for multibyte characters support
   * @return true if multibyte characters are supported, false otherwise
   */
  [[nodiscard]] static bool IsMultibyteLocale();

  /**
 * Print counts depending on program options
 * @param options The arguments passed to the program
 * @param counts The counts based on options
 * @param optional_file_path An optional file path for which the counts have been done
 */
  static void Print(const Options& options, const Counts& counts, const optional<string_view>& optional_file_path = {});

  ArgsReader args_reader_;
};

#endif  // DRIVER_H_
