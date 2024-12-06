#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

int main() {
    // Load the data into a single string
    std::string filename = "1203/input.txt";
    std::fstream filestream(filename, std::ios::in);
    std::string combined_text;
    for (std::string line; std::getline(filestream, line);) {
        combined_text.append(line);
    }

    // Parse, execute and sum the valid multiplication operations in the string
    int output = 0;
    std::string a, b;
    std::regex expr_regex("(mul\\([0-9]+,[0-9]+\\))|(do\\(\\))|(don\\'t\\(\\))");
    std::regex parse1_regex("mul\\(");
    std::regex parse2_regex("\\)");
    bool op_enabled = true;
    auto expr_begin = std::sregex_iterator(combined_text.begin(), combined_text.end(), expr_regex);
    auto expr_end = std::sregex_iterator();
    for (auto i = expr_begin; i != expr_end; ++i) {
        // Determine whether we are parsing a do/don't switch or a multiplication operation
        std::smatch regex_match = *i;
        std::string regex_match_string = regex_match.str();
        if (regex_match_string.substr(0, 3) == "do(") {
            op_enabled = true;
        } else if (regex_match_string.substr(0, 3) == "don") {
            op_enabled = false;
        } else {
            if (op_enabled) {
                // Extract the "###,###" component of the "mul(###,###)" string
                regex_match_string = regex_match_string.substr(4, regex_match_string.size() - 1);
                
                // Split into two strings without the comma
                std::stringstream regex_match_stream(regex_match_string);
                std::getline(regex_match_stream, a, ',');
                std::getline(regex_match_stream, b, ',');
                
                // Convert strings to integers and add their product to the running total
                output += std::stoi(a) * std::stoi(b);
            }
        }
    }

    std::cout << "Sum of valid string multiplications = " << output << std::endl;
}
