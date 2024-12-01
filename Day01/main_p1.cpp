#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>

int main() {
    std::ifstream inputFile("./Day01/input_01_1.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    std::vector<int> left, right, differences;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        int a, b;
        if (lineStream >> a >> b) {
            left.push_back(a);
            right.push_back(b);
        } else {
            std::cerr << "Invalid line format: " << line << std::endl;
            return 1;
        }
    }
    inputFile.close();

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int totalDifference = 0;
    for (size_t i = 0; i < left.size(); i++) {
        int diff = std::abs(left[i] - right[i]);
        totalDifference += diff;
    }

    std::cout << "Total Difference: " << totalDifference << std::endl;

    return 0;
}