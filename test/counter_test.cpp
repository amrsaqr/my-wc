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

  void AssertCounts(const unsigned int bytes, const unsigned int lines,
    const unsigned int words, const unsigned int chars) {
    ASSERT_EQ(bytes, counts_.GetBytes());
    ASSERT_EQ(lines, counts_.GetLines());
    ASSERT_EQ(words, counts_.GetWords());
    ASSERT_EQ(chars, counts_.GetChars());
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
