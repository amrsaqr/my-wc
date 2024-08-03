//
// Created by Amr Saqr on 03/08/2024.
//

#ifndef MY_WC_OPTIONS_H
#define MY_WC_OPTIONS_H

#include <vector>
using std::vector;

class Options {
public:
    Options(const vector<char>& options);
    bool CountingBytes() const;
    bool CountingLines() const;
    bool CountingWords() const;

private:
    bool counting_bytes_;
    bool counting_lines_;
    bool counting_words_;
};


#endif //MY_WC_OPTIONS_H
