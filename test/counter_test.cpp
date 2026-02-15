//
// Copyright 2026 Amr Saqr
//

#include "counter.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "options.h"
#include "counts.h"
#include "gtest/gtest.h"

using std::ostringstream;
using std::istringstream;
using std::string;
using std::endl;

class CounterTest : public testing::Test {
 protected:
  void DoTestAndSetActualOutputs(const string& input_string, const vector<char>& options_list,
    bool is_multibyte_locale, unsigned int buffer_size) {
    if (is_multibyte_locale) {
      setlocale(LC_CTYPE, "en_US.UTF-8");
    } else {
      setlocale(LC_CTYPE, "C");
    }

    istringstream iss(input_string);
    Options options(options_list);

    Counter counter(buffer_size);
    counter.Count(iss, options, is_multibyte_locale, &counts_, &error_output_);
  }

  void AssertCounts(const unsigned int expected_bytes, const unsigned int expected_lines,
    const unsigned int expected_words, const unsigned int expected_chars) {
    EXPECT_EQ(expected_bytes, counts_.GetBytes());
    EXPECT_EQ(expected_lines, counts_.GetLines());
    EXPECT_EQ(expected_words, counts_.GetWords());
    EXPECT_EQ(expected_chars, counts_.GetChars());
  }

  Counts counts_;
  string error_output_;
};

TEST_F(CounterTest, TestsSimpleStringWithDefaultOptionsAndNoMultibyteLocale) {
  DoTestAndSetActualOutputs("Hello World!\n", {}, false, 4);

  AssertCounts(13, 1, 2, 0);

  ASSERT_EQ(error_output_, "");
}

TEST_F(CounterTest, TestsEmptyStringWithDefaultOptionsAndNoMultibyteLocale) {
  DoTestAndSetActualOutputs("", {}, false, 4);

  AssertCounts(0, 0, 0, 0);

  ASSERT_EQ(error_output_, "");
}

TEST_F(CounterTest, TestsSpacesOnlyWithDefaultOptionsAndNoMultibyteLocale) {
  DoTestAndSetActualOutputs(" \n \t ", {}, false, 4);

  AssertCounts(5, 1, 0, 0);

  ASSERT_EQ(error_output_, "");
}

TEST_F(CounterTest, TestsMultibyteStringWithDefaultOptionsAndMultibyteLocale) {
  DoTestAndSetActualOutputs("z\u00df\u6c34\U0001d10b", {}, true, 2);

  AssertCounts(10, 0, 1, 0);

  ASSERT_EQ(error_output_, "");
}

TEST_F(CounterTest, TestsMultibyteStringWithMOptionAndMultibyteLocale) {
  DoTestAndSetActualOutputs("z\u00df\u6c34\U0001d10b", {'m'}, true, 2);

  AssertCounts(0, 0, 0, 4);

  ASSERT_EQ(error_output_, "");
}

TEST_F(CounterTest, TestsMultibyteStringWithMOptionAndNoMultibyteLocale) {
  DoTestAndSetActualOutputs("z\u00df\u6c34\U0001d10b", {'m'}, false, 2);

  AssertCounts(0, 0, 0, 10);

  ASSERT_EQ(error_output_, "");
}

TEST_F(CounterTest, TestsMultibyteStringWithMLWOptionsAndMultibyteLocale) {
  DoTestAndSetActualOutputs("z\u00df\u6c34\U0001d10b\n", {'m', 'l', 'w'}, true, 2);

  AssertCounts(0, 1, 1, 5);

  ASSERT_EQ(error_output_, "");
}

TEST_F(CounterTest, TestsMultilineMultibyteStringWithMLWOptionsAndMultibyteLocale) {
  string word1 = "z\u00df\u6c34\U0001d10b";
  string word2 = "r\u00e9sum\u00e9";

  // This should match the file under "/test-files/test-small.txt"
  ostringstream oss;
  oss << word2 << ' ' << word2 << endl;
  oss << word2 << ' ' << word1 << endl;
  oss << word1 << ' ' << word2 << endl;

  DoTestAndSetActualOutputs(oss.str(), {'m', 'l', 'w'}, true, 2);

  AssertCounts(0, 3, 6, 38);

  ASSERT_EQ(error_output_, "");
}

TEST_F(CounterTest, TestsIllegalByteSequenceResiliencyWithMWOptionsAndMultibyteLocale) {
  // Sequence:
  // 'A' (1 byte)
  // \xFF (Illegal)
  // ' ' (Space)
  // \xE3\x81\x82 ('あ' - 3 bytes)
  DoTestAndSetActualOutputs("A\xFF \xE3\x81\x82", {'m', 'w'}, true, 2);

  // Chars: 1 ('A') + 1 (Illegal) + 1 (Space) + 1 ('あ') = 4
  AssertCounts(0, 0, 2, 4);

  ASSERT_EQ(error_output_, "Illegal byte sequence");
}

TEST_F(CounterTest, TestsIllegalByteSequenceResiliencyWithMWOptionsAndNoMultibyteLocale) {
  // Sequence:
  // 'A' (1 byte)
  // \xFF (Illegal)
  // ' ' (Space)
  // \xE3\x81\x82 ('あ' - 3 bytes)
  DoTestAndSetActualOutputs("A\xFF \xE3\x81\x82", {'m', 'w'}, false, 2);

  // Chars (Bytes because of NoMultibyteLocale): 1 ('A') + 1 (Illegal) + 1 (Space) + 3 ('あ') = 6
  AssertCounts(0, 0, 2, 6);

  ASSERT_EQ(error_output_, "");
}
