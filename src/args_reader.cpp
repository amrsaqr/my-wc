//
// Created by Amr Saqr on 30/07/2024.
//

#include "args_reader.h"
void ArgsReader::Read(int argc, char** argv) {
    // First read options until done, or you hit a potential file path (argument that doesn't start with a '-')
    int i = 1;
    for (; i < argc && argv[i][0] == '-'; ++i) {
        for (int j = 1; argv[i][j]; ++j) {
            options_.emplace_back(argv[i][j]);
        }
    }

    // Now that we're done reading options, any argument that follows is considered a file path
    for (; i < argc; ++i) {
        files_paths_.emplace_back(argv[i]);
    }
}

vector<char> ArgsReader::GetOptions() {
    return options_;
}

vector<string> ArgsReader::GetFilesPaths() {
    return files_paths_;
}