#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    // Load the data
    std::string filename = "1201/input.txt";
    std::fstream filestream(filename, std::ios::in);
    std::vector<int> list1;
    std::vector<int> list2;
    int a, b;
    for (std::string line; std::getline(filestream, line);) {
        std::stringstream linestream(line);
        linestream >> a >> b;
        list1.push_back(a);
        list2.push_back(b);
    }

    // Compute similarity score between the two vectors
    int similarity_score = 0;
    for (const auto& elem : list1) {
        similarity_score += std::count(list2.begin(), list2.end(), elem);
    }
    std::cout << "Similarity score = " << similarity_score << std::endl;
}
