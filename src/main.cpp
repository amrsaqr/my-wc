//
// Copyright 2024 Amr Saqr
//

#include <string>
#include <utility>
#include <iostream>

#include "args_reader.h"
#include "driver.h"
#include "options.h"

using std::string;
using std::cout;

int main(int argc, char** argv) {
  ArgsReader args_reader;
  args_reader.Read(argc - 1, argv + 1);

  Options options(args_reader.GetOptions());
  Counter counter;

  return Driver::RunAndPrintResults(cout, options, args_reader.GetFilesPaths(), counter);
}
