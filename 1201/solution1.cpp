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

    // Sort the two lists and compute the requested difference metric
    std::stable_sort(list1.begin(), list1.end());
    std::stable_sort(list2.begin(), list2.end());
    int total_diff = 0;
    for (int i = 0; i < list1.size(); i++) {
        total_diff += std::abs(list1.at(i) - list2.at(i));
    }
    std::cout << "Total difference = " << total_diff << std::endl;
}
