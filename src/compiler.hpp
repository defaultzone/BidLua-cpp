#include <fstream>
#include <map>
#include <filesystem>
#include "replace.hpp"
#include "userMap.hpp"
#include "names/names.hpp"

#ifndef BIDLUA_CPP_COMPILER_HPP
#define BIDLUA_CPP_COMPILER_HPP
#endif  // BIDLUA_CPP_COMPILER_HPP

void compile(const std::string inputPath, std::string outputPath, std::string userMapPath, std::string flagStatus) {
    std::ifstream inputFile(inputPath);
    if (inputFile.good()) {
        std::ofstream outputFile(outputPath);
        if (outputFile.good()) {
            std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

            auto [userMapInitialize, newFileContent] = createProjectMap(userMapPath, fileContent);
            std::map<std::string, std::string> userMap;
            if (userMapInitialize.find("NO_MAP") == userMapInitialize.end()) {
                userMap.insert(userMapInitialize.begin(), userMapInitialize.end());
            }

            std::string outputFileContent;
            if (flagStatus == "true") {
                outputFileContent = replaceKeys(newFileContent, userMap);
            } else {
                newFileContent = replaceKeys(newFileContent, userMap);
                outputFileContent = replaceKeys(newFileContent, names);
            }

            outputFile << outputFileContent;
            outputFile.close();
        } else {
            std::cerr << "Error creating output file." << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Error opening input file." << std::endl;
    }
}