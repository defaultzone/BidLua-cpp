#include <iostream>
#include <cstring>
#include "compiler.hpp"
#include "info.h"

void printHelpText(const std::string& programPath) {
    std::stringstream helpText;
    helpText    << "usage: " << programPath << " [key] [file] [options...]\n\n"
                << "key:\n"
                << "\t-h, --help\tdisplay this\n"
                << "\t--info\t\tdisplay info about BidLua\n"
                << "\t-i FILE\t\tcompile just the file\n"
                << "\t-I FILE\t\tcompile the file that contains [options...]\n"
                << "options:\n"
                << "\t-m, --map FILE\t\tallows you to use your map in the main file\n"
                << "\t-n, --ignore-default-map\tignore default map\n"
                << "\t-o, --output FILE\t\twrite compiled code to specific file, by default\n"
                << "it is <output file path without extension> + .lua";
    std::cout << helpText.str() << std::endl;
}

int main(int argc, char** argv) {
    std::string inputPath, outputPath, mapPath;
    std::string programPath { argv[0] };
    bool ignoreDefaultCompilerMap { false };

    if (argc >= 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printHelpText(programPath);
        } else if (strcmp(argv[1], "--info") == 0) {
            std::stringstream infoText;
            infoText << "BidLua Copyright (C) 2023 defaultzon3 (or just DZONE)\n"
                     << "\tThis program comes with ABSOLUTELY NO WARRANTY;\n"
                     << "\tThis program is free software: you can redistribute it and/or modify it under the\n"
                     << "\tterms of the GNU General Public License as published by the Free Software Foundation,\n"
                     << "\teither version 3 of the License, or (at your option) any later version.\n"
                     << "version:\t" << BIDLUA_VERSION << std::endl
                     << "repository url:\t" << BIDLUA_REPOSITORY_URL;
            std::cout << infoText.str() << std::endl;
        } else {
            for (int i = 3; i < argc; i++) {
                if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--map") == 0) {
                    if (argc >= i + 1) {
                        mapPath = argv[i + 1];
                    } else {
                        std::cerr << "Expected 'FILE' in setting map path. For more information, type '-h' or '--help'." << std::endl;
                        mapPath = "null";
                    }
                } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                    if (argc >= i + 1) {
                        outputPath = argv[i + 1];
                    } else {
                        std::size_t dotPosition{inputPath.find_last_of('.')};
                        outputPath = argv[2].substr(0, dotPosition) + ".lua";
                    }
                }

                ignoreDefaultCompilerMap = strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--ignore-default-map") == 0;
            }

            if (argc != 1) {
                compile(argv[2], outputPath, mapPath, ignoreDefaultCompilerMap, (strcmp(argv[1], "-o") == 0));
            } else {
                std::cerr << "Expected 'FILE' after [key], but got nothing." << std::endl;
            }
        }
    } else {
        printHelpText(programPath);
    }

    return EXIT_SUCCESS;
}
