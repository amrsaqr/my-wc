//
// Copyright 2025 Amr Saqr
//

#include <gtest/gtest.h>
#include "counts.h"

TEST(CountsTest, TestsIncBytes) {
  Counts counts;
  ASSERT_EQ(counts.GetBytes(), 0);

  counts.IncBytes();
  ASSERT_EQ(counts.GetBytes(), 1);

  counts.IncBytes(9);
  ASSERT_EQ(counts.GetBytes(), 10);
}

TEST(CountsTest, TestsIncLines) {
  Counts counts;
  ASSERT_EQ(counts.GetLines(), 0);

  counts.IncLines();
  ASSERT_EQ(counts.GetLines(), 1);

  counts.IncLines(9);
  ASSERT_EQ(counts.GetLines(), 10);
}

TEST(CountsTest, TestsIncWords) {
  Counts counts;
  ASSERT_EQ(counts.GetWords(), 0);

  counts.IncWords();
  ASSERT_EQ(counts.GetWords(), 1);

  counts.IncWords(9);
  ASSERT_EQ(counts.GetWords(), 10);
}

TEST(CountsTest, TestsIncChars) {
  Counts counts;
  ASSERT_EQ(counts.GetChars(), 0);

  counts.IncChars();
  ASSERT_EQ(counts.GetChars(), 1);

  counts.IncChars(9);
  ASSERT_EQ(counts.GetChars(), 10);
}
