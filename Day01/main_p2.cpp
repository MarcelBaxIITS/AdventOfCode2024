#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
    std::ifstream inputFile("./Day01/input_01_1.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    std::vector<int> left, right;
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

    int score = 0;
    for (int num : left) {
        auto count = std::count(right.begin(), right.end(), num);
        score += static_cast<int>(count) * num;
    }

    std::cout << "Total score: " << score << std::endl;
    return 0;
}