//
// Copyright 2025 Amr Saqr
//

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <initializer_list>
#include "args_reader.h"

using std::initializer_list;

class ArgsReaderTest : public testing::Test {
 protected:
  void InitArgsReader(initializer_list<const char*> args) {
    if (args.size() == 0) {
      return;
    }

    vector args_copy(args.begin(), args.end());

    args_reader_.Read(static_cast<int>(args.size()), args_copy.data());
    options_ = args_reader_.GetOptions();
    files_paths_ = args_reader_.GetFilesPaths();
  }

  ArgsReader args_reader_;
  vector<char> options_;
  vector<string> files_paths_;
};

TEST_F(ArgsReaderTest, TestsNoOptionsNoFiles) {
  InitArgsReader({});

  EXPECT_EQ(options_.size(), 0);

  EXPECT_EQ(files_paths_.size(), 0);
}

TEST_F(ArgsReaderTest, TestsOneOptionNoFiles) {
  InitArgsReader({"-c"});

  ASSERT_EQ(options_.size(), 1);
  EXPECT_EQ(options_[0], 'c');

  EXPECT_EQ(files_paths_.size(), 0);
}

TEST_F(ArgsReaderTest, TestsMultiOptionsNoFiles) {
  InitArgsReader({"-c", "-l", "-w"});

  ASSERT_EQ(options_.size(), 3);
  EXPECT_EQ(options_[0], 'c');
  EXPECT_EQ(options_[1], 'l');
  EXPECT_EQ(options_[2], 'w');

  EXPECT_EQ(files_paths_.size(), 0);
}

TEST_F(ArgsReaderTest, TestsMultiOptionsGroupedNoFiles) {
  InitArgsReader({"-clw"});

  ASSERT_EQ(options_.size(), 3);
  EXPECT_EQ(options_[0], 'c');
  EXPECT_EQ(options_[1], 'l');
  EXPECT_EQ(options_[2], 'w');

  EXPECT_EQ(files_paths_.size(), 0);
}

TEST_F(ArgsReaderTest, TestsNoOptionsOneFile) {
  InitArgsReader({"file.txt"});

  EXPECT_EQ(options_.size(), 0);

  ASSERT_EQ(files_paths_.size(), 1);
  EXPECT_EQ(files_paths_[0], "file.txt");
}

TEST_F(ArgsReaderTest, TestsNoOptionsMultiFiles) {
  InitArgsReader({"file1.txt", "file2.txt"});

  EXPECT_EQ(options_.size(), 0);

  ASSERT_EQ(files_paths_.size(), 2);
  EXPECT_EQ(files_paths_[0], "file1.txt");
  EXPECT_EQ(files_paths_[1], "file2.txt");
}

TEST_F(ArgsReaderTest, TestsMultiOptionsMultiFiles) {
  InitArgsReader({"-m", "-lw", "file1.txt", "file2.txt"});

  ASSERT_EQ(options_.size(), 3);
  EXPECT_EQ(options_[0], 'm');
  EXPECT_EQ(options_[1], 'l');
  EXPECT_EQ(options_[2], 'w');

  ASSERT_EQ(files_paths_.size(), 2);
  EXPECT_EQ(files_paths_[0], "file1.txt");
  EXPECT_EQ(files_paths_[1], "file2.txt");
}

TEST_F(ArgsReaderTest, TestsOptionsIgnoredAfterFilesPathsStart) {
  InitArgsReader({"-l", "file.txt", "-m"});

  ASSERT_EQ(options_.size(), 1);
  EXPECT_EQ(options_[0], 'l');

  ASSERT_EQ(files_paths_.size(), 2);
  EXPECT_EQ(files_paths_[0], "file.txt");
  EXPECT_EQ(files_paths_[1], "-m");
}
