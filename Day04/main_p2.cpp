#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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
    for (int row = 1; row < lines.size() - 1; ++row) {
        for (int col = 1; col < lines.size() - 1; ++col) {
            if (lines[row][col] == 'A') {
                char uL = lines[row - 1][col - 1];
                char uR = lines[row - 1][col + 1];
                char dL = lines[row + 1][col - 1];
                char dR = lines[row + 1][col + 1];

                int mCount = 0;
                if (uL == 'M') {
                    mCount++;
                }
                if (uR == 'M') {
                    mCount++;
                }
                if (dL == 'M') {
                    mCount++;
                }
                if (dR == 'M') {
                    mCount++;
                }

                int sCount = 0;
                if (uL == 'S') {
                    sCount++;
                }
                if (uR == 'S') {
                    sCount++;
                }
                if (dL == 'S') {
                    sCount++;
                }
                if (dR == 'S') {
                    sCount++;
                }
                if (sCount == 2 && mCount == 2) {
                    if ((uL == uR) || (uL == dL) ) {
                       count++;
                    }
                }
            }
        }
    }


    std::cout << "Total count: " << count << std::endl;

    return 0;
}
