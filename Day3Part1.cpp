#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
    std::string filePath = "input.txt";

    std::ifstream inputFile(filePath);
    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return 1;
    }

    std::string memory((std::istreambuf_iterator<char>(inputFile)),
                       std::istreambuf_iterator<char>());

    inputFile.close();

    std::regex validMulRegex(R"(mul\((\d{1,3}),(\d{1,3})\))");

    std::smatch match;
    int totalSum = 0;

    std::string::const_iterator searchStart(memory.cbegin());
    while (std::regex_search(searchStart, memory.cend(), match, validMulRegex)) {
        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());

        totalSum += x * y;

        searchStart = match.suffix().first;
    }

    std::cout << "The total sum of all valid mul instructions is: " << totalSum << std::endl;

    return 0;
}
