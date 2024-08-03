//
// Created by Amr Saqr on 30/07/2024.
//

#include "args_reader.h"
#include "options.h"
#include "counter.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;

int main(int argc, char** argv) {
    ArgsReader args_reader;
    args_reader.Read(argc, argv);

    Options options(args_reader.GetOptions());
    auto files_paths = args_reader.GetFilesPaths();

    if (files_paths.empty()) {
        Counter counter(options);
        counter.Count();
        counter.Print();
    } else {
        for (const string &file_path : files_paths) {
            Counter counter(options, file_path);
            counter.Count();
            counter.Print();
        }
    }

    return 0;
}