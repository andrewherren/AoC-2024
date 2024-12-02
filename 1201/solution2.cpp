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
    std::stable_sort(list1.begin(), list1.end());
    int similarity_score = 0;
    int element_count;
    int run_length = 1;
    for (int i = 0; i < list1.size(); i++) {
        // Determine whether a run is completed
        bool end_of_run = (
            (i == list1.size() - 1) || 
            ((i < list1.size() - 1) ? (list1[i + 1] != list1[i]) : false)
        );
        if (end_of_run) {
            // Write existing counter to similarity score
            element_count = std::count(list2.begin(), list2.end(), list1[i]);
            similarity_score += element_count * run_length * list1[i];
            // Reset run length
            run_length = 1;
        } else {
            // Increment run length
            run_length += 1;
        }
    }
    std::cout << "Similarity score = " << similarity_score << std::endl;
}
