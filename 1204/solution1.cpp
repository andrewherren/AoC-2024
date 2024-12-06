#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    // Load the data "row-major" into a single string
    std::string filename = "1204/input.txt";
    std::fstream filestream(filename, std::ios::in);
    std::string combined_text;
    int num_rows = 0;
    int num_cols;
    for (std::string line; std::getline(filestream, line);) {
        if (num_rows == 0) {
            num_cols = line.size();
        }
        combined_text.append(line);
        num_rows++;
    }
    std::cout << "The data has " << num_rows << " rows and " << num_cols << " columns" << std::endl;
}
