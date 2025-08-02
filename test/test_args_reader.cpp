//
// Copyright 2025 Amr Saqr
//
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "args_reader.h"

#define ARGS_READER_TEST ArgsReaderTest

// Demonstrate some basic assertions.
TEST(ARGS_READER_TEST, NoOptionsNoFiles) {
  ArgsReader args_reader;
  char arg[] = "my_wc";
  char* argv[1] = {arg};
  args_reader.Read(1, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  ASSERT_EQ(options.size(), 0);
  ASSERT_EQ(files_paths.size(), 0);
}

TEST(ARGS_READER_TEST, OneOptionNoFiles) {
  ArgsReader args_reader;
  char arg0[] = "my_wc";
  char arg1[] = "-c";
  char* argv[2] = {arg0, arg1};
  args_reader.Read(2, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  ASSERT_EQ(options.size(), 1);
  ASSERT_EQ(options[0], 'c');
  ASSERT_EQ(files_paths.size(), 0);
}
