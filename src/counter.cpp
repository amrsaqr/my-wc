//
// Created by Amr Saqr on 31/07/2024.
//

#include "counter.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <utility>
#include <codecvt>
#include <locale>
#include <cwctype>
using std::istream;
using std::ifstream;
using std::cin;
using std::cout;
using std::cerr;
using std::setw;
using std::endl;
using std::wstring;
using std::getline;
using std::codecvt_utf8;
using std::wstring_convert;

Counter::Counter(const Options& options) : options_(options) {
    reading_from_file_ = false;
}

Counter::Counter(const Options& options, string file_path) : options_(options), file_path_(std::move(file_path)) {
    reading_from_file_ = true;
}

bool Counter::Count() {
    istream* in;
    if (reading_from_file_) {
        in = new ifstream(file_path_, std::ios::in);

        if (in->fail()) {
            cerr << file_path_ << ": Error opening file" << endl;
            delete in;
            return false;
        }
    } else {
        in = &cin;
    }

    string line;
    while (getline(*in, line)) {
        // Count the bytes in the narrow (ASCII or UTF-8 like) string
        if (options_.CountingBytes()) {
            bytes_count_ += line.size();
        }

        // Convert to a wide string to be able to identify wide characters
        if (options_.CountingWords() || options_.CountingChars()) {
            wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convert;
            wstring wline = convert.from_bytes(line);

            if (options_.CountingChars()) {
                chars_count_ += wline.size();
            }

            if (options_.CountingWords()) {
                for (int i = 0; i < wline.size(); ++i) {
                    if (!iswspace(wline[i]) && (!i || iswspace(wline[i - 1]))) {
                        ++words_count_;
                    }
                }
            }
        }

        // Increase the bytes count, chars count, and lines count for the newline character
        if (options_.CountingBytes()) {
            ++bytes_count_;
        }

        if (options_.CountingChars()) {
            ++chars_count_;
        }

        if (options_.CountingLines()) {
            ++lines_count_;
        }
    }

    if (reading_from_file_) {
        dynamic_cast<ifstream*>(in)->close();
        delete in;
    }

    return true;
}

void Counter::Print() const {
    if (options_.CountingLines()) {
        cout << setw(8) << lines_count_;
    }

    if (options_.CountingWords()) {
        cout << setw(8) << words_count_;
    }

    if (options_.CountingChars()) {
        cout << setw(8) << chars_count_;
    }

    if (options_.CountingBytes()) {
        cout << setw(8) << bytes_count_;
    }

    if (reading_from_file_) {
        cout << ' ' << file_path_;
    }

    cout << endl;
}