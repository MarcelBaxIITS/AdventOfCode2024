#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

std::vector<std::pair<std::string, int> > findAllRegexMatches(const std::string &content,
                                                                      const std::string &regex) {
    std::regex regexPattern(regex);
    std::vector<std::pair<std::string, int> > matches;

    for (std::sregex_iterator it(content.begin(), content.end(), regexPattern), end; it != end; ++it) {
        matches.push_back(std::make_pair((*it).str(), (*it).position()));
    }

    return matches;
}

std::vector<int> findAllRegexMatchesPosition(const std::string &content,
                                                    const std::string &regex) {
    std::regex regexPattern(regex);
    std::vector<int> matches;

    for (std::sregex_iterator it(content.begin(), content.end(), regexPattern), end; it != end; ++it) {
        matches.push_back((*it).position());
    }

    return matches;
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream stream(str);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
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
    std::string content;
    while (std::getline(inputFile, line)) {
        content += line;
    }


    std::string pattern = "(mul\\()[0-9]*,[0-9]*\\)";
    std::string dontPattern = "don't\\(\\)";
    std::string doPattern = "do\\(\\)";

    std::vector<std::pair<std::string, int> > matches = findAllRegexMatches(content, pattern);
    std::vector<int> donts = findAllRegexMatchesPosition(content, dontPattern);
    std::vector<int> dos = findAllRegexMatchesPosition(content, doPattern);
    dos.insert(dos.begin(), 0);

    int num = 0;
    int doIndex = 0;
    int dontIndex = 0;
    int nearestSmallerDo = -1;
    int nearestSmallerDont = -1;
    for (const std::pair<std::string, int> match: matches) {
        while (nearestSmallerDo < match.second && doIndex < dos.size() && dos[doIndex] < match.second) {
            nearestSmallerDo = dos[doIndex];
            doIndex++;
        }
        while (nearestSmallerDont < match.second && dontIndex < donts.size() && donts[dontIndex] < match.second) {
            nearestSmallerDont = donts[dontIndex];
            dontIndex++;
        }

        if (nearestSmallerDo > nearestSmallerDont) {
            std::pair<int, int> numbers = processMatch(match.first);
            num += numbers.first * numbers.second;
        }
    }
    std::cout << num << std::endl;

    return 0;
}
