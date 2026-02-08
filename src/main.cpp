//
// Copyright 2024 Amr Saqr
//

#include "driver.h"

int main(int argc, char** argv) {
  Driver driver(argc - 1, argv + 1);
  return driver.Run();
}
