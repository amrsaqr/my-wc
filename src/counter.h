//
// Created by Amr Saqr on 31/07/2024.
//

#ifndef MY_WC_COUNTER_H
#define MY_WC_COUNTER_H

#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
using std::string;
using std::vector;
using std::istream;
using std::ifstream;

class Counter {
public:
    Counter();

    Counter(string file_path);

    void Count(const vector<char>& options);

    int GetBytesCount();

    int GetLinesCount();

private:
    bool reading_from_file_;
    const string file_path_;
    int bytes_count;
    int lines_count;
};


#endif //MY_WC_COUNTER_H
