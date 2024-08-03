//
// Created by Amr Saqr on 03/08/2024.
//

#include "options.h"

Options::Options(const vector<char> &options) {
    if (options.empty()) {
        counting_bytes_ = true;
        counting_lines_ = true;
        counting_words_ = true;
        counting_chars_ = false;
        return;
    }

    counting_bytes_ = false;
    counting_lines_ = false;
    counting_words_ = false;
    counting_chars_ = false;

    for (char option : options) {
        if (option == 'c') {
            counting_bytes_ = true;
            counting_chars_ = false;
        } else if (option == 'l') {
            counting_lines_ = true;
        } else if (option == 'w') {
            counting_words_ = true;
        } else if (option == 'm') {
            counting_chars_ = true;
            counting_bytes_ = false;
        }
    }
}

bool Options::CountingBytes() const {
    return counting_bytes_;
}

bool Options::CountingLines() const {
    return counting_lines_;
}

bool Options::CountingWords() const {
    return counting_words_;
}

bool Options::CountingChars() const {
    return counting_chars_;
}