//
// Copyright 2025 Amr Saqr
//
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "args_reader.h"

TEST(ArgsReaderTest, NoOptionsNoFiles) {
  ArgsReader args_reader;
  char arg0[] = "my_wc";
  char* argv[] = {arg0};
  args_reader.Read(1, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  EXPECT_EQ(options.size(), 0);
  EXPECT_EQ(files_paths.size(), 0);
}

TEST(ArgsReaderTest, OneOptionNoFiles) {
  ArgsReader args_reader;
  char arg0[] = "my_wc";
  char arg1[] = "-c";
  char* argv[] = {arg0, arg1};
  args_reader.Read(2, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  ASSERT_EQ(options.size(), 1);
  EXPECT_EQ(options[0], 'c');
  EXPECT_EQ(files_paths.size(), 0);
}

TEST(ArgsReaderTest, MultiOptionsNoFiles) {
  ArgsReader args_reader;
  char arg0[] = "my_wc";
  char arg1[] = "-c";
  char arg2[] = "-l";
  char arg3[] = "-w";
  char* argv[] = {arg0, arg1, arg2, arg3};
  args_reader.Read(4, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  ASSERT_EQ(options.size(), 3);
  EXPECT_EQ(options[0], 'c');
  EXPECT_EQ(options[1], 'l');
  EXPECT_EQ(options[2], 'w');
}

TEST(ArgsReaderTest, MultiOptionsGroupedNoFiles) {
  ArgsReader args_reader;
  char arg0[] = "my_wc";
  char arg1[] = "-clw";
  char* argv[] = {arg0, arg1};
  args_reader.Read(2, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  ASSERT_EQ(options.size(), 3);
  EXPECT_EQ(options[0], 'c');
  EXPECT_EQ(options[1], 'l');
  EXPECT_EQ(options[2], 'w');
}

TEST(ArgsReaderTest, NoOptionsOneFile) {
  ArgsReader args_reader;
  char arg0[] = "my_wc";
  char arg1[] = "file.txt";
  char* argv[] = {arg0, arg1};
  args_reader.Read(2, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  EXPECT_EQ(options.size(), 0);
  ASSERT_EQ(files_paths.size(), 1);
  EXPECT_EQ(files_paths[0], "file.txt");
}

TEST(ArgsReaderTest, NoOptionsMultiFiles) {
  ArgsReader args_reader;
  char arg0[] = "my_wc";
  char arg1[] = "file1.txt";
  char arg2[] = "file2.txt";
  char* argv[] = {arg0, arg1, arg2};
  args_reader.Read(3, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  EXPECT_EQ(options.size(), 0);
  ASSERT_EQ(files_paths.size(), 2);
  EXPECT_EQ(files_paths[0], "file1.txt");
  EXPECT_EQ(files_paths[1], "file2.txt");
}

TEST(ArgsReaderTest, MultiOptionsMultiFiles) {
  ArgsReader args_reader;
  char arg0[] = "my_wc";
  char arg1[] = "-m";
  char arg2[] = "-lw";
  char arg3[] = "file1.txt";
  char arg4[] = "file2.txt";
  char* argv[] = {arg0, arg1, arg2, arg3, arg4};
  args_reader.Read(5, argv);

  const vector<char> options = args_reader.GetOptions();
  const vector<string> files_paths = args_reader.GetFilesPaths();

  ASSERT_EQ(options.size(), 3);
  EXPECT_EQ(options[0], 'm');
  EXPECT_EQ(options[1], 'l');
  EXPECT_EQ(options[2], 'w');
  ASSERT_EQ(files_paths.size(), 2);
  EXPECT_EQ(files_paths[0], "file1.txt");
  EXPECT_EQ(files_paths[1], "file2.txt");
}
