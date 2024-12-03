#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

struct Result {
    std::string value;
    int line;
    int start;

    Result(const std::string &strVal, int lineVal, int startVal)
        : value(strVal), line(lineVal), start(startVal) {
    }
};

std::vector<Result> findAllRegexMatchesAsResult(const std::vector<std::string> &lines, const std::string &regex) {
    std::regex regexPattern(regex);
    std::vector<Result> matches;
    int lineNo = 0;

    for (const std::string line: lines) {
        for (std::sregex_iterator it(line.begin(), line.end(), regexPattern), end; it != end; ++it) {
            matches.emplace_back((*it).str(), lineNo, (*it).position());
        }
        lineNo++;
    }

    return matches;
}

std::vector<std::pair<int, int> > findAllRegexMatchesAsNumberAndLine(const std::vector<std::string> &lines,
                                                                     const std::string &regex) {
    std::regex regexPattern(regex);
    std::vector<std::pair<int, int> > matches;
    int lineNo = 0;

    for (const std::string line: lines) {
        for (std::sregex_iterator it(line.begin(), line.end(), regexPattern), end; it != end; ++it) {
            matches.push_back(std::make_pair((*it).position(), lineNo));
        }
        lineNo++;
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

std::pair<int, int> findNext(const std::vector<std::pair<int, int> > &matches,
                             int givenNumber, int givenLine) {
    for (const auto &result: matches) {
        if (result.second < givenLine) continue;


        if ((result.first > givenNumber && result.second == givenLine) || (
                result.first < givenNumber && result.second > givenLine)) {
            return std::make_pair(result.first, result.second);
        }
    }
    return std::make_pair(-1, -1);
}


bool shouldChangeToDont(const std::pair<int, int> &nextDont, const Result &match) {
    return !(nextDont.first == -1 || match.line < nextDont.second || (
                 match.line == nextDont.second && match.start < nextDont.first));
}

bool shouldChangeToDo(const std::pair<int, int> &nextDo, const Result &match) {
    return !(nextDo.first == -1 || match.line < nextDo.second || (
                 match.line == nextDo.second && match.start < nextDo.first));
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


    std::string pattern = "(mul\\()[0-9]*,[0-9]*\\)";
    std::string dontPattern = "don't\\(\\)";
    std::string doPattern = "do\\(\\)";

    std::vector<Result> matches = findAllRegexMatchesAsResult(lines, pattern);
    std::vector<std::pair<int, int> > donts = findAllRegexMatchesAsNumberAndLine(lines, dontPattern);
    std::vector<std::pair<int, int> > dos = findAllRegexMatchesAsNumberAndLine(lines, doPattern);

    bool doDont = true;
    std::pair<int, int> nextDont = findNext(donts, 0, 0);
    std::pair<int, int> nextDo = findNext(dos, 0, 0);
    int num = 0;

    for (const Result match: matches) {
        if (doDont && shouldChangeToDont(nextDont, match)) {
            doDont = false;
            nextDo = findNext(dos, match.start, match.line);
        } else if (!doDont && shouldChangeToDo(nextDo, match)) {
            doDont = true;
            nextDont = findNext(donts, match.start, match.line);
        }

        if (doDont == true) {
            std::pair<int, int> numbers = processMatch(match.value);
            num += numbers.first * numbers.second;
        }
    }
    std::cout << num << std::endl;

    return 0;
}
