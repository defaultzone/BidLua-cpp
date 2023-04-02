#include <iostream>
#include <map>
#include <string>
#include <regex>

#ifndef BIDLUA_CPP_REPLACE_H
#define BIDLUA_CPP_REPLACE_H
#endif  // BIDLUA_CPP_REPLACE_H

std::string replaceKeys(const std::string& input, const std::map<std::string, std::string>& map) {
    std::string output;
    std::uint32_t i = 0;

    while (i < static_cast<uint32_t>(input.length())) {
        std::string c { input };
        std::map<std::string, std::string> skipUntilMap {
                {"--", "\n"},
                {"--[[", "]]"},
                {"--[=[", "]=]"},
                {"[[", "]]"},
                {"[=[", "]=]"}
        };

        bool skipFound = false;
        for (auto const& [key, value] : skipUntilMap) {
            if (c.substr(i, key.length()) == key) {
                i += key.length();  // Skip key ...
                output += key;      // ... and insert it in output.
                while (c.substr(i, value.length()) != value) {
                    output += c[i];
                    i++;
                }
                skipFound = true;
                break;
            }
        }
        if (!skipFound) {
            bool mapFound = false;
            for (auto const& [mapKey, mapValue] : map) {
                if (c.substr(i, mapKey.length()) == mapKey) {
                    i += mapKey.length();
                    output += mapValue;
                    mapFound = true;
                    break;
                }
            }
            if (!mapFound) {
                output += c[i];
                i++;
            }
        }
    }

    return output;
}