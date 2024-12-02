#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

bool isAscending(const std::vector<int> &row) {
    for (int i = 1; i < row.size(); i++) {
        if (row[i] <= row[i - 1]) {
            return false;
        }
    }
    return true;
}

bool isDescending(const std::vector<int> &row) {
    for (int i = 1; i < row.size(); i++) {
        if (row[i] >= row[i - 1]) {
            return false;
        }
    }
    return true;
}

bool isDifferenceValid(const std::vector<int> &row) {
    for (int i = 1; i < row.size(); i++) {
        if (std::abs(row[i] - row[i - 1]) > 3) {
            return false;
        }
    }
    return true;
}

bool isValid(const std::vector<int> &row) {
    return (isAscending(row) || isDescending(row)) && isDifferenceValid(row);
}

bool isValidWithDampener(const std::vector<int> &row) {
    for (int i = 0; i < row.size(); i++) {
        std::vector<int> newRow = row;
        newRow.erase(newRow.begin() + i);
        if (isValid(newRow))
            return true;
    }
    return false;
}

int main() {
    std::ifstream inputFile("./Day02/input_02_1.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    std::vector<std::vector<int> > rows;
    std::string line;

    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        std::vector<int> row;
        int num;

        while (lineStream >> num) {
            row.push_back(num);
        }

        rows.push_back(row);
    }

    int valid = 0;
    for (const auto &row: rows) {
        if (isValidWithDampener(row))
            valid++;
    }

    std::cout << valid << std::endl;
    return 0;
}
