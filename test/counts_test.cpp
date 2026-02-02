//
// Copyright 2025 Amr Saqr
//

#include <gtest/gtest.h>
#include "counts.h"

class CountsTest : public testing::Test {
 protected:
  void AssertCounts(const unsigned int bytes,
    const unsigned int lines,
    const unsigned int words,
    const unsigned int chars) {
    ASSERT_EQ(bytes, counts_.GetBytes());
    ASSERT_EQ(lines, counts_.GetLines());
    ASSERT_EQ(words, counts_.GetWords());
    ASSERT_EQ(chars, counts_.GetChars());
  }

  Counts counts_;
};

TEST_F(CountsTest, TestsAllZeroesInitially) {
  AssertCounts(0, 0, 0, 0);
}

TEST_F(CountsTest, TestsIncBytes) {
  counts_.IncBytes();
  AssertCounts(1, 0, 0, 0);

  counts_.IncBytes(9);
  AssertCounts(10, 0, 0, 0);
}

TEST_F(CountsTest, TestsIncLines) {
  counts_.IncLines();
  AssertCounts(0, 1, 0, 0);

  counts_.IncLines(9);
  AssertCounts(0, 10, 0, 0);
}

TEST_F(CountsTest, TestsIncWords) {
  counts_.IncWords();
  AssertCounts(0, 0, 1, 0);

  counts_.IncWords(9);
  AssertCounts(0, 0, 10, 0);
}

TEST_F(CountsTest, TestsIncChars) {
  counts_.IncChars();
  AssertCounts(0, 0, 0, 1);

  counts_.IncChars(9);
  AssertCounts(0, 0, 0, 10);
}
