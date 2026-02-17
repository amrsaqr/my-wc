//
// Copyright 2024 Amr Saqr
//

#include <string>
#include <utility>

#include "args_reader.h"
#include "driver.h"
#include "options.h"

using std::string;

int main(int argc, char** argv) {
  ArgsReader args_reader;
  args_reader.Read(argc - 1, argv + 1);

  Options options(args_reader.GetOptions());

  Driver driver(options, std::move(args_reader.GetFilesPaths()), std::move(Counter()));
  return driver.Run();
}
