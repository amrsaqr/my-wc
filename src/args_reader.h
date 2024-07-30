//
// Created by Amr Saqr on 30/07/2024.
//

#ifndef MY_WC_ARGS_READER_H
#define MY_WC_ARGS_READER_H

#include <vector>
#include <string>
using std::vector;
using std::string;

class ArgsReader {
public:
    ArgsReader() = default;

    void Read(int argc, char** argv);

    vector<char> GetOptions();

    vector<string> GetFilesPaths();
private:
    vector<char> options_;
    vector<string> files_paths_;
};


#endif //MY_WC_ARGS_READER_H
