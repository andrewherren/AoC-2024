#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    // Load the data
    std::string filename = "1202/input.txt";
    std::fstream filestream(filename, std::ios::in);
    int safe_count = 0;
    int line_num = 1;
    for (std::string line; std::getline(filestream, line);) {
        std::stringstream linestream(line);
        std::string elem_string;
        int prev_elem, curr_elem;
        // Extract the first element in the list
        std::getline(linestream, elem_string, ' ');
        prev_elem = std::stoi(elem_string);
        bool has_increase{false};
        bool has_decrease{false};
        bool has_diff_out_of_range{false};
        bool is_safe{true};
        // Loop through the line, looking for "unsafe" exceptions
        while (std::getline(linestream, elem_string, ' ')) {
            curr_elem = std::stoi(elem_string);
            if (curr_elem == prev_elem) {
                has_diff_out_of_range = true;
                is_safe = false;
                break;
            } else if (curr_elem > prev_elem) {
                has_increase = true;
                if (curr_elem - prev_elem > 3) {
                    has_diff_out_of_range = true;
                    is_safe = false;
                    break;
                }
            } else if (curr_elem < prev_elem) {
                has_decrease = true;
                if (prev_elem - curr_elem > 3) {
                    has_diff_out_of_range = true;
                    is_safe = false;
                    break;
                }
            }
            if (has_decrease && has_increase) {
                is_safe = false;
                break;
            }
            prev_elem = curr_elem;
        }
        safe_count += (is_safe) ? 1 : 0;
    }
    std::cout << "Total number of safe reports = " << safe_count << std::endl;
}
