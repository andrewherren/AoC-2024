#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

int main() {
    // Load the data "row-major" into a single string, so that element (i,j) in the input grid
    // is accessed by the (i * num_cols + j) character in the string.
    std::string filename = "1204/input.txt";
    std::fstream filestream(filename, std::ios::in);
    std::string combined_text_rowmajor;
    int num_rows = 0;
    int num_cols;
    for (std::string line; std::getline(filestream, line);) {
        if (num_rows == 0) {
            num_cols = line.size();
        }
        combined_text_rowmajor.append(line);
        num_rows++;
    }
    std::cout << "The data has " << num_rows << " rows and " << num_cols << " columns" << std::endl;

    // Loop through each row / column, leaving a buffer of one character on each side of the iterator
    // If we find an "A", look for a valid "M-A-S" x "M-A-S" pattern
    int total_matches = 0;
    const char* a = "A";
    const char* m = "M";
    const char* s = "S";
    for (int i = 1; i < num_rows - 1; i++) {
        for (int j = 1; j < num_cols - 1; j++) {
            if (combined_text_rowmajor[i*num_cols + j] == *a) {
                // Check for the x-mas pattern
                if (combined_text_rowmajor[(i-1)*num_cols + (j-1)] == *m) {
                    if (combined_text_rowmajor[(i-1)*num_cols + (j+1)] == *m) {
                        if ((combined_text_rowmajor[(i+1)*num_cols + (j-1)] == *s) && 
                            (combined_text_rowmajor[(i+1)*num_cols + (j+1)] == *s)) {
                                total_matches++;
                        }
                    } else if (combined_text_rowmajor[(i-1)*num_cols + (j+1)] == *s) {
                        if ((combined_text_rowmajor[(i+1)*num_cols + (j-1)] == *m) && 
                            (combined_text_rowmajor[(i+1)*num_cols + (j+1)] == *s)) {
                                total_matches++;
                        }
                    }
                } else if (combined_text_rowmajor[(i-1)*num_cols + (j-1)] == *s) {
                    if (combined_text_rowmajor[(i-1)*num_cols + (j+1)] == *s) {
                        if ((combined_text_rowmajor[(i+1)*num_cols + (j-1)] == *m) && 
                            (combined_text_rowmajor[(i+1)*num_cols + (j+1)] == *m)) {
                                total_matches++;
                        }
                    } else if (combined_text_rowmajor[(i-1)*num_cols + (j+1)] == *m) {
                        if ((combined_text_rowmajor[(i+1)*num_cols + (j-1)] == *s) && 
                            (combined_text_rowmajor[(i+1)*num_cols + (j+1)] == *m)) {
                                total_matches++;
                        }
                    }
                }
            }
        }
    }
    
    // Total matches
    std::cout << "There are " << total_matches << " total valid appearances of \"X-MAS\" in the provided data" << std::endl;
}
