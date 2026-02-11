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

TEST_F(CounterTest, TestsSimpleAsciiString) {
  ostringstream oss;
  oss << "Hello World!" << endl;

  DoTestAndSetActualOutputs(oss.str(), {'c', 'l', 'w'}, false, 4);

  AssertCounts(13, 1, 2, 0);

  ASSERT_EQ(error_output_, "");
}
