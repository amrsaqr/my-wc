//
// Copyright 2026 Amr Saqr
//

#ifndef COUNT_RESULT_H_
#define COUNT_RESULT_H_

#include <string>
#include <utility>

#include "counts.h"

using std::string;
using std::optional;

struct CountResult {
  CountResult(bool successful, optional<string> error_output, optional<string> file_path, const Counts& counts) :
    successful(successful), error_output(std::move(error_output)), file_path(std::move(file_path)), counts(counts) {}

  bool successful;
  optional<string> error_output;
  optional<string> file_path;
  Counts counts;
};

#endif  // COUNT_RESULT_H_
