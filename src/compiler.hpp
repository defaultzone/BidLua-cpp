#include <fstream>
#include <map>
#include <filesystem>
#include <sstream>
#include "replace.hpp"
#include "userMap.hpp"
#include "names/names.hpp"

#ifndef BIDLUA_CPP_COMPILER_HPP
#define BIDLUA_CPP_COMPILER_HPP
#endif  // BIDLUA_CPP_COMPILER_HPP

void compile(const std::string inputPath, std::string outputPath, std::string userMapPath, std::string flagStatus) {
    std::ifstream inputFile(inputPath);
    std::string inputFileExtension { std::filesystem::path(inputPath).extension().string() };
    if (inputFile.good()) {
        std::ofstream outputFile(outputPath);
        if (outputFile.good()) {
            std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            std::cout << "DEBUG | _FILE_CONTENT: " << fileContent << std::endl;

            auto [userMapInitialize, newFileContent] = createProjectMap(userMapPath, fileContent);
            std::map<std::string, std::string> userMap;
            if (userMapInitialize.find("NO_MAP") == userMapInitialize.end()) {
                userMap.insert(userMapInitialize.begin(), userMapInitialize.end());
            }

            std::stringstream ss;
            for (auto const& pair : userMap) {
                ss << pair.first << ": " << pair.second << std::endl;
            }
            std::cout << "DEBUG | SS: " << ss.str() << std::endl;

            std::string outputFileContent;
            if (flagStatus == "true") {
                outputFileContent = replaceKeys(newFileContent, userMap, inputFileExtension);
            } else {
                newFileContent = replaceKeys(newFileContent, userMap, inputFileExtension);
                outputFileContent = replaceKeys(newFileContent, names, inputFileExtension);
            }

            std::cout << "DEBUG | OUTPUT FILE CONTENT: " << outputFileContent << std::endl;
            std::cout << "DEBUG | NEW FILE CONTENT: " << newFileContent << std::endl;
            std::cout << "DEBUG | INPUT_FILE_EXTENSION: " << inputFileExtension << std::endl;
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