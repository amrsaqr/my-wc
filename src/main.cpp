//
// Created by Amr Saqr on 30/07/2024.
//

#include "args_reader.h"
#include "counter.h"
#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    ArgsReader args_reader;
    args_reader.Read(argc, argv);

    auto options = args_reader.GetOptions();
    auto files_paths = args_reader.GetFilesPaths();

    if (files_paths.empty()) {
        Counter counter;
        counter.Count(options);
        cout << counter.GetLinesCount() << ' ' << counter.GetBytesCount() << endl;
    } else {
        for (const string &file_path : files_paths) {
            Counter counter(file_path);
            counter.Count(options);
            cout << counter.GetLinesCount() << ' ' << counter.GetBytesCount() << ' ' << file_path << endl;
        }
    }

    return 0;
}