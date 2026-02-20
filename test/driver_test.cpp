//
// Copyright 2026 Amr Saqr
//

#include "driver.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "options.h"
#include "counts.h"
#include "mocks/mock_counter.h"

using std::cin;
using std::endl;
using std::ostringstream;
using std::ofstream;
using std::remove;
using testing::_;
using testing::Ref;
using testing::Return;
using testing::Not;
using testing::DoAll;
using testing::SetArgPointee;

class DriverTest : public testing::Test {
 public:
  DriverTest() : options_({}) {}

 protected:
  static void SetUpTestSuite() {
    file1_.open("file1.txt");

    file2_.open("file2.txt");
  }

  static void TearDownTestSuite() {
    file1_.close();
    remove("file1.txt");

    file2_.close();
    remove("file2.txt");
  }

  MockCounter mock_counter_;
  ostringstream oss_;
  Options options_;

  static ofstream file1_;
  static ofstream file2_;
};

ofstream DriverTest::file1_;
ofstream DriverTest::file2_;

TEST_F(DriverTest, TestsStandardInputWithSuccessfulCounting) {
  Counts counts(10, 1, 2, 0);
  EXPECT_CALL(mock_counter_, Count(Ref(cin), _, _, _, _))
  .Times(1)
  .WillOnce(DoAll(SetArgPointee<3>(counts), Return(true)));

  int result = Driver::RunAndPrintResults(oss_, options_, {}, mock_counter_);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(oss_.str(), "       1       2      10\n");
}

TEST_F(DriverTest, TestsStandardInputWithSuccessfulCountingAndWarningMessage) {
  Counts counts(10, 1, 2, 0);
  EXPECT_CALL(mock_counter_, Count(Ref(cin), _, _, _, _))
  .Times(1)
  .WillOnce(DoAll(SetArgPointee<3>(counts), SetArgPointee<4>("warning message"), Return(true)));

  int result = Driver::RunAndPrintResults(oss_, options_, {}, mock_counter_);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(oss_.str(), "warning message\n       1       2      10\n");
}

TEST_F(DriverTest, TestsStandardInputWithUnsuccessfulCountingAndErrorMessage) {
  Counts counts(1, 2, 3, 4);
  EXPECT_CALL(mock_counter_, Count(Ref(cin), _, _, _, _))
  .Times(1)
  .WillOnce(DoAll(SetArgPointee<3>(counts), SetArgPointee<4>("error message"), Return(false)));

  int result = Driver::RunAndPrintResults(oss_, options_, {}, mock_counter_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(oss_.str(), "error message\n");
}

TEST_F(DriverTest, TestsOneNonExistentFile) {
  EXPECT_CALL(mock_counter_, Count(_, _, _, _, _)).Times(0);

  int result = Driver::RunAndPrintResults(oss_, options_, {"non_existent_file.txt"}, mock_counter_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(oss_.str(), "non_existent_file.txt: No such file or directory\n");
}

TEST_F(DriverTest, TestsTwoNonExistentFiles) {
  EXPECT_CALL(mock_counter_, Count(_, _, _, _, _)).Times(0);

  int result = Driver::RunAndPrintResults(oss_, options_,
    {"non_existent_file1.txt", "non_existent_file2.txt"}, mock_counter_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(oss_.str(), "non_existent_file1.txt: No such file or directory\n"
                        "non_existent_file2.txt: No such file or directory\n");
}

TEST_F(DriverTest, TestsTwoExistentFiles) {
  Counts counts1(10, 1, 2, 0);
  Counts counts2(5, 1, 1, 0);
  EXPECT_CALL(mock_counter_, Count(Not(Ref(cin)), _, _, _, _))
  .Times(2)
  .WillOnce(DoAll(SetArgPointee<3>(counts1), Return(true)))
  .WillOnce(DoAll(SetArgPointee<3>(counts2), Return(true)));

  int result = Driver::RunAndPrintResults(oss_, options_,
    {"file1.txt", "file2.txt"}, mock_counter_);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(oss_.str(), "       1       2      10 file1.txt\n"
                        "       1       1       5 file2.txt\n"
                        "       2       3      15 total\n");
}

TEST_F(DriverTest, TestsTwoExistentFilesAndTwoNonExistentFiles) {
  Counts counts1(10, 1, 2, 0);
  Counts counts2(5, 1, 1, 0);
  EXPECT_CALL(mock_counter_, Count(Not(Ref(cin)), _, _, _, _))
  .Times(2)
  .WillOnce(DoAll(SetArgPointee<3>(counts1), Return(true)))
  .WillOnce(DoAll(SetArgPointee<3>(counts2), Return(true)));

  int result = Driver::RunAndPrintResults(oss_, options_,
    {"file1.txt", "non_existent_file1.txt", "non_existent_file2.txt", "file2.txt"}, mock_counter_);
  EXPECT_EQ(result, 1);
  EXPECT_EQ(oss_.str(), "       1       2      10 file1.txt\n"
                        "non_existent_file1.txt: No such file or directory\n"
                        "non_existent_file2.txt: No such file or directory\n"
                        "       1       1       5 file2.txt\n"
                        "       2       3      15 total\n");
}
