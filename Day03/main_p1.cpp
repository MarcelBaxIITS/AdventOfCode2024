#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

std::vector<std::string> findAllMatches(const std::vector<std::string> &lines, const std::string &pattern) {
    std::regex regexPattern(pattern);
    std::vector<std::string> matches;

    for (const std::string line: lines) {
        for (std::sregex_iterator it(line.begin(), line.end(), regexPattern), end; it != end; ++it) {
            matches.push_back((*it).str());
        }
    }

    return matches;
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::pair<int, int> processMatch(const std::string &match) {
    std::string cleaned = std::regex_replace(match, std::regex("mul\\("), "");
    cleaned = std::regex_replace(cleaned, std::regex("\\)"), "");

    const std::vector<std::string> parts = split(cleaned, ',');

    if (parts.size() == 2) {
        int num1 = std::stoi(parts[0]);
        int num2 = std::stoi(parts[1]);
        return std::make_pair(num1, num2);
    }
    throw std::runtime_error("Invalid format: Expected two numbers separated by ','");
}

int main() {
    std::ifstream inputFile("./Day03/input_02_1.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    std::string pattern = "(mul\\()[0-9]*,[0-9]*\\)"; // Escaped regex pattern for digits

    std::vector<std::string> matches = findAllMatches(lines, pattern);
    int num = 0;
    for (const auto &match: matches) {
        std::pair<int, int> numbers = processMatch(match);
        num += numbers.first * numbers.second;
    }
    std::cout << num << std::endl;

    return 0;
}
