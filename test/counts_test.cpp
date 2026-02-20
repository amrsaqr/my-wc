//
// Copyright 2025 Amr Saqr
//

#include "counts.h"

#include <gtest/gtest.h>

class CountsTest : public testing::Test {
 protected:
  void AssertCounts(const unsigned int expected_bytes,
    const unsigned int expected_lines,
    const unsigned int expected_words,
    const unsigned int expected_chars) {
    EXPECT_EQ(expected_bytes, counts_.GetBytes());
    EXPECT_EQ(expected_lines, counts_.GetLines());
    EXPECT_EQ(expected_words, counts_.GetWords());
    EXPECT_EQ(expected_chars, counts_.GetChars());
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

TEST_F(CountsTest, TestsPlusEqOperator) {
  Counts counts1(1, 2, 3, 4);
  counts_ += counts1;
  AssertCounts(1, 2, 3, 4);

  Counts counts2(4, 3, 2, 1);
  counts_ += counts2;
  AssertCounts(5, 5, 5, 5);
}
