//
// Created by Amr Saqr on 03/08/2024.
//

#include "options.h"

Options::Options(const vector<char> &options) {
    counting_bytes_ = false;
    counting_lines_ = false;
    counting_words_ = false;

    for (char option : options) {
        if (option == 'c') {
            counting_bytes_ = true;
        } else if (option == 'l') {
            counting_lines_ = true;
        } else if (option == 'w') {
            counting_words_ = true;
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