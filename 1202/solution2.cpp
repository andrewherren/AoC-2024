#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
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
        bool is_safe;
        // Unpack elements into a vector
        std::vector<int> linevec((std::istream_iterator<int>(linestream)), std::istream_iterator<int>());
        // Compute first differences
        std::vector<int> linevec_diffs(linevec.size());
        std::adjacent_difference(linevec.begin(), linevec.end(), linevec_diffs.begin());
        int valid_increases = 0;
        int valid_decreases = 0;
        for (int i = 1; i < linevec_diffs.size(); i++) {
            if ((linevec_diffs[i] >= 1) && (linevec_diffs[i] <= 3)) {
                valid_increases++;
            } else if ((linevec_diffs[i] <= -1) && (linevec_diffs[i] >= -3)) {
                valid_decreases++;
            }
        }
        // Determine whether an entry is "safe"
        if ((valid_increases == linevec.size() - 1) || (valid_decreases == linevec.size() - 1)) {
            is_safe = true;
        } else {
            for (int i = 0; i < linevec_diffs.size(); i++) {
                // Consider removing each element in an entry
                int proposed_valid_increases = valid_increases;
                int proposed_valid_decreases = valid_decreases;
                if ((i == 0) || (i == linevec_diffs.size() - 1)) {
                    // Consider removing the first or last elements
                    // Since the "first" element shows up as the second adjacent difference, 
                    // we must handle indexing carefully
                    int elem_diff = (i == 0) ? linevec_diffs[i + 1] : linevec_diffs[i];
                    if ((elem_diff >= 1) && (elem_diff <= 3)) {
                        proposed_valid_increases--;
                    } else if ((elem_diff <= -1) && (elem_diff >= -3)) {
                        proposed_valid_decreases--;
                    }
                    // Check if this results in a "safe" entry
                    if ((proposed_valid_increases == linevec.size() - 2) || (proposed_valid_decreases == linevec.size() - 2)) {
                        is_safe = true;
                        break;
                    } else {
                        is_safe = false;
                    }
                } else {
                    // Consider removing any of the interior elements
                    int first_diff = linevec_diffs[i];
                    int second_diff = linevec_diffs[i + 1];
                    int combined_diff = linevec_diffs[i + 1] + linevec_diffs[i];
                    if ((first_diff >= 1) && (first_diff <= 3)) {
                        proposed_valid_increases--;
                    } else if ((first_diff <= -1) && (first_diff >= -3)) {
                        proposed_valid_decreases--;
                    }
                    if ((second_diff >= 1) && (second_diff <= 3)) {
                        proposed_valid_increases--;
                    } else if ((second_diff <= -1) && (second_diff >= -3)) {
                        proposed_valid_decreases--;
                    }
                    if ((combined_diff >= 1) && (combined_diff <= 3)) {
                        proposed_valid_increases++;
                    } else if ((combined_diff <= -1) && (combined_diff >= -3)) {
                        proposed_valid_decreases++;
                    }
                    // Check if this results in a "safe" entry
                    if ((proposed_valid_increases == linevec.size() - 2) || (proposed_valid_decreases == linevec.size() - 2)) {
                        is_safe = true;
                        break;
                    } else {
                        is_safe = false;
                    }
                }
            }
        }
        safe_count += (is_safe) ? 1 : 0;
    }
    std::cout << "Total number of safe reports = " << safe_count << std::endl;
}
