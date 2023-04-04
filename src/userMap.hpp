#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <locale>
#include <regex>

#ifndef BIDLUA_CPP_USERMAP_HPP
#define BIDLUA_CPP_USERMAP_HPP

std::pair<std::map<std::string, std::string>, std::string> createProjectMap(const std::string& userMapPath, std::string& mainFileContent) {
    std::map<std::string, std::string> finalMap;

    std::ifstream file(userMapPath);

    // Create a custom map from the file passed by the "-map=path" flag.
    if (userMapPath != "null") {
        if (file.good()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string userMapContent = buffer.str();
            std::regex regex("ADD (.*?)::(.*?);");
            for (std::sregex_iterator it(userMapContent.begin(), userMapContent.end(), regex), end_it; it != end_it; ++it) {
                finalMap.insert(std::make_pair(it->str(1), it->str(2)));
            }
        } else {
            std::cout << "Error: file on \"" << userMapPath << "\" doesn't exist." << std::endl;
            finalMap.insert(std::make_pair("NO_MAP", "NO_MAP"));
        }
    }

    // We add values from the main file to the final map.
    std::regex regex("#add (.*?)::(.*?);");
    for (std::sregex_iterator it(mainFileContent.begin(), mainFileContent.end(), regex), end_it; it != end_it; ++it) {
        finalMap.insert(std::make_pair(it->str(1), it->str(2)));
        mainFileContent.erase(it->position(), it->length());
    }

    // After creating a map from the corresponding file and the main file, we return a pair from the map and the contents of the main file.
    return std::make_pair(finalMap, mainFileContent);
}

#endif  // BIDLUA_CPP_USERMAP_HPP