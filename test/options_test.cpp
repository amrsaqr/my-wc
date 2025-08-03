//
// Copyright 2025 Amr Saqr
//

#include <gtest/gtest.h>
#include <vector>
#include "options.h"

TEST(OptionsTest, TestsNoOptions) {
  vector<char> options_args;
  Options options(options_args);

  ASSERT_TRUE(options.CountingBytes());
  ASSERT_TRUE(options.CountingLines());
  ASSERT_TRUE(options.CountingWords());
  ASSERT_FALSE(options.CountingChars());
}

TEST(OptionsTest, TestsExplicitOptions) {
  vector options_args{'c', 'l'};
  Options options(options_args);

  ASSERT_TRUE(options.CountingBytes());
  ASSERT_TRUE(options.CountingLines());
  ASSERT_FALSE(options.CountingWords());
  ASSERT_FALSE(options.CountingChars());

  options_args = {'m', 'w'};
  options = Options(options_args);

  ASSERT_FALSE(options.CountingBytes());
  ASSERT_FALSE(options.CountingLines());
  ASSERT_TRUE(options.CountingWords());
  ASSERT_TRUE(options.CountingChars());
}

TEST(OptionsTest, TestsBytesCharsLatestOverwrite) {
  vector options_args{'c', 'l', 'w', 'm'};
  Options options(options_args);

  ASSERT_FALSE(options.CountingBytes());
  ASSERT_TRUE(options.CountingLines());
  ASSERT_TRUE(options.CountingWords());
  ASSERT_TRUE(options.CountingChars());

  options_args = {'m', 'l', 'w', 'c'};
  options = Options(options_args);

  ASSERT_TRUE(options.CountingBytes());
  ASSERT_TRUE(options.CountingLines());
  ASSERT_TRUE(options.CountingWords());
  ASSERT_FALSE(options.CountingChars());
}
