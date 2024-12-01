#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
    std::ifstream inputfile("./day01/input_01_1.txt");
    if (!inputfile) {
        std::cerr << "error: could not open file." << std::endl;
        return 1;
    }

    std::vector<int> left, right;
    std::string line;

    while (std::getline(inputfile, line)) {
        std::istringstream linestream(line);
        int a, b;
        if (linestream >> a >> b) {
            left.push_back(a);
            right.push_back(b); // store the second numbe
        } else {
            std::cerr << "invalid line format: " << line << std::endl;
            return 1;
        }
    }
    inputfile.close();

    std::sort(left.begin(), left.end());

    std::unordered_map<int, int> right_counts;
    for (int num : right) {
        right_counts[num]++;
    }

    int score = 0;
    std::vector<int> counts;
    for (int num : left) {
        score += (right_counts[num]) * num;
    }

    std::cout << "total score: " << score << std::endl;
    return 0;
}