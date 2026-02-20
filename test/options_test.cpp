//
// Copyright 2025 Amr Saqr
//

#include "options.h"

#include <gtest/gtest.h>
#include <vector>
#include <string>

using std::string;

struct OptionsTestData {
  bool output_counting_bytes;
  bool output_counting_lines;
  bool output_counting_words;
  bool output_counting_chars;
  vector<char> input_options_args;

  OptionsTestData(bool output_counting_bytes,
    bool output_counting_lines,
    bool output_counting_words,
    bool output_counting_chars,
    std::initializer_list<char> input_options_args) :
  output_counting_bytes(output_counting_bytes),
  output_counting_lines(output_counting_lines),
  output_counting_words(output_counting_words),
  output_counting_chars(output_counting_chars),
  input_options_args(input_options_args) {}
};

class OptionsTest : public ::testing::TestWithParam<OptionsTestData> {
 public:
  OptionsTest() = default;
};

TEST_P(OptionsTest, ReturnsCorrectFlags) {
  Options options(GetParam().input_options_args);
  EXPECT_EQ(options.CountingBytes(), GetParam().output_counting_bytes);
  EXPECT_EQ(options.CountingLines(), GetParam().output_counting_lines);
  EXPECT_EQ(options.CountingWords(), GetParam().output_counting_words);
  EXPECT_EQ(options.CountingChars(), GetParam().output_counting_chars);
}

INSTANTIATE_TEST_SUITE_P(MultipleOptionVariations, OptionsTest, testing::Values(
  OptionsTestData(true, true, true, false, {}),
  OptionsTestData(true, true, false, false, {'c', 'l'}),
  OptionsTestData(false, false, true, true, {'m', 'w'}),
  OptionsTestData(false, true, true, true, {'c', 'l', 'w', 'm'}),
  OptionsTestData(true, true, true, false, {'m', 'l', 'w', 'c'})),
  [](const testing::TestParamInfo<OptionsTestData>& info) -> string {
    if (info.param.input_options_args.empty()) {
      return "no_options";
    }

    return string(info.param.input_options_args.begin(), info.param.input_options_args.end());
  });
