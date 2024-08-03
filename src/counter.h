//
// Created by Amr Saqr on 31/07/2024.
//

#ifndef MY_WC_COUNTER_H
#define MY_WC_COUNTER_H

#include "options.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Counter {
public:
    Counter(const Options& options);

    Counter(const Options& options, string file_path);

    void Count();

    void Print() const;

private:
    void Init();
    const Options options_;
    const string file_path_;

    bool reading_from_file_;
    size_t bytes_count_;
    size_t lines_count_;
    size_t words_count_;
    size_t chars_count_;
};


#endif //MY_WC_COUNTER_H
