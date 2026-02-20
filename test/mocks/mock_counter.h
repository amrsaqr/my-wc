//
// Copyright 2026 Amr Saqr
//

#ifndef TEST_MOCKS_MOCK_COUNTER_H_
#define TEST_MOCKS_MOCK_COUNTER_H_

#include <gmock/gmock.h>
#include <istream>
#include <string>
#include "counter.h"
#include "options.h"
#include "counts.h"

class MockCounter : public Counter {
 public:
  MockCounter() : Counter(1) {}
  MOCK_METHOD(bool, Count, (std::istream& in, const Options& options,
    bool is_multibyte_locale, Counts* counts, string* error_output), (const));
};

#endif  // TEST_MOCKS_MOCK_COUNTER_H_
