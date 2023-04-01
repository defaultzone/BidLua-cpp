#include <iostream>
#include <map>
#include <string>

#ifndef BIDLUA_CPP_REPLACE_H
#define BIDLUA_CPP_REPLACE_H
#endif  // BIDLUA_CPP_REPLACE_H

std::string replaceKeys(const std::string& input, const std::map<std::string, std::string>& map, const std::string& fileExtension) {
    std::string output;
    std::uint32_t n { static_cast<uint32_t>(input.length()) };
    std::uint16_t i { 0 };

    while (i < n) { // TODO: Refactor this.
        if (input.find("[[", i) == i) { // Skip until closing brackets.
            int j = input.find("]]", i + 2);
            if (j >= 0) {
                output.append(input, i, j + 2);
                i = j + 2;
            } else {
                j = n;
                output.append(input, i, j);
                i = j;
            }
        } else if (input.find("[=[", i) == i) { // Skip until closing brackets.
            int j = input.find("]=]", i + 2);
            if (j >= 0) {
                output.append(input, i, j + 3);
                i = j + 3;
            } else {
                j = n;
                output.append(input, i, j);
                i = j;
            }
        } else if (input.find("—[[", i) == i) { // Skip until closing brackets.
            int j = input.find("]]", i + 2);
            if (j >= 0) {
                output.append(input, i, j + 2);
                i = j + 2;
            } else {
                j = n;
                output.append(input, i, j);
                i = j;
            }
        } else if (input.find("—[=[", i) == i) { // Skip until closing brackets.
            int j = input.find("]=]", i + 2);
            if (j >= 0) {
                output.append(input, i, j + 3);
                i = j + 3;
            } else {
                j = n;
                output.append(input, i, j);
                i = j;
            }
        } else if (input.find("--", i) == i) { // Skip until end of line.
            int j = input.find('\n', i + 2);
            if (j >= 0) {
                output.append(input, i, j);
                i = j;
            } else {
                j = n;
                output.append(input, i, j);
                i = j;
            }
        } else if (input.find('\"', i) == i) { // Skip until closing quote.
            int j = input.find('"', i + 1);
            if (j >= 0) {
                output.append(input, i, j + 1);
                i = j + 1;
            } else {
                j = n;
                output.append(input, i, j);
                i = j;
            }
        } else if (input.find('\'', i) == i) { // Skip until closing quote.
            int j = input.find('\'', i + 1);
            if (j >= 0) {
                output.append(input, i, j + 1);
                i = j + 1;
            } else {
                j = n;
                output.append(input, i, j);
                i = j;
            }
        } else { // Try to match a key from the map
            bool found = false;
            for (const auto & it : map) {
                std::string key { it.first };
                std::string value { it.second };
                std::string safeKey, safeValue;

                if (fileExtension == ".blya") {
                    safeKey = key;
                    safeValue = value;
                } else {
                    safeKey = value;
                    safeValue = key;
                }

                if (input.find(safeKey, i) == i) {
                    output.append(safeValue);
                    i += safeKey.length();
                    found = true;
                    break;
                }
            }
            if (!found) {
                output.push_back(input[i]);
                i++;
            }
        }
    }

    return output;
}