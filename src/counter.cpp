//
// Created by Amr Saqr on 31/07/2024.
//

#include "counter.h"

Counter::Counter() {
    reading_from_file_ = false;
    bytes_count = 0;
    lines_count = 0;
}

Counter::Counter(string file_path) : file_path_(std::move(file_path)) {
    reading_from_file_ = true;
    bytes_count = 0;
    lines_count = 0;
}

void Counter::Count(const vector<char>& options) {
    bool countingBytes = false;
    bool countingLines = false;
    for (char option : options) {
        if (option == 'c') {
            countingBytes = true;
        } else if (option == 'l') {
            countingLines = true;
        }
    }

    istream* in;
    if (reading_from_file_) {
        in = new ifstream(file_path_, std::ios::in);
    } else {
        in = &std::cin;
    }

    char ch;
    while (!in->eof()) {
        in->get(ch);

        if (countingBytes) {
            ++bytes_count;
        }

        if (countingLines && ch == '\n') {
            ++lines_count;
        }
    }

    if (reading_from_file_) {
        delete in;
    }
}

int Counter::GetBytesCount() {
    return bytes_count;
}

int Counter::GetLinesCount() {
    return lines_count;
}