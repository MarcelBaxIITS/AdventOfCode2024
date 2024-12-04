#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool checkForwardBackwardAtIndex(const int row, const int col, const std::vector<std::string>& lines) {
    if (col + 3 < lines[row].size()) {
        const std::string testString = lines[row].substr(col, 4);
        if (testString == "XMAS" || testString == "SAMX") {
            return true;
        }
    }

    return false;
}

bool checkDiagonalLeft(const int row, const int col, const std::vector<std::string>& lines) {
    if (row + 3 < lines.size() && col - 3 >= 0) {
        std::string testString;
        for (int i = row, j = col; i < row + 4; ++i, j--) {
            testString += lines[i][j];
        }
        if (testString == "XMAS" || testString == "SAMX") {
            return true;
        }
    }
    return false;
}

bool checkDiagonalRight(const int row, const int col, const std::vector<std::string>& lines) {
    if (row + 3 < lines.size() && col + 3 < lines[row].size()) {
        std::string testString;
        for (int i = row, j = col; i < row + 4; ++i, j++) {
            testString += lines[i][j];
        }
        if (testString == "XMAS" || testString == "SAMX") {
            return true;
        }
    }
    return false;
}

bool checkUpDown(const int row, const int col, const std::vector<std::string>& lines) {
    if (row + 3 < lines.size()) {
        std::string testString;
        for (int i = row; i < row + 4; ++i) {
            testString += lines[i][col];
        }
        if (testString == "XMAS" || testString == "SAMX") {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream inputFile("./Day04/input_1.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }
    std::vector<int> left, right, differences;
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();


    int count = 0;
    for (int row = 0; row < lines.size(); ++row) {
        for (int col = 0; col < lines.size(); ++col) {
            bool foundFB = false;
            if (checkForwardBackwardAtIndex(row, col, lines)) {
                count++;
                foundFB = true;
            }
            if (checkDiagonalLeft(row, col, lines)) {
                count++;
            }
            if (checkDiagonalRight(row, col, lines)) {
                count++;
            }
            if (checkUpDown(row, col, lines)) {
                count++;
            }
            if (foundFB) {
                col += 2;
            }
        }
    }

    std::cout << "Total count: " << count << std::endl;

    return 0;
}
