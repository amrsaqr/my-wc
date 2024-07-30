//
// Created by Amr Saqr on 30/07/2024.
//

#include "args_reader.h"
void ArgsReader::Read(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        char* arg = argv[i];
        int arg_len = strlen(arg);

        if (arg_len > 0) {
            if (arg[0] == '-') {
                for (int j = 1; j < arg_len; ++j) {
                    options_.push_back(arg[j]);
                }
            }
            else {
                files_paths_.emplace_back(arg);
            }
        }
    }
}

vector<char> ArgsReader::GetOptions() {
    return options_;
}

vector<string> ArgsReader::GetFilesPaths() {
    return files_paths_;
}