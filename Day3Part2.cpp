#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    string filePath = "input.txt";
    ifstream inputFile(filePath);
    if (!inputFile) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return 1;
    }

    string memory((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    regex pattern(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");
    smatch match;
    int totalSum = 0;
    bool isEnabled = true;

    string::const_iterator searchStart(memory.cbegin());
    while (regex_search(searchStart, memory.cend(), match, pattern)) {
        if (match[0] == "do()") {
            isEnabled = true;
        } else if (match[0] == "don't()") {
            isEnabled = false;
        } else if (match[1].matched && match[2].matched && isEnabled) {
            int x = stoi(match[1].str());
            int y = stoi(match[2].str());
            totalSum += x * y;
        }
        searchStart = match.suffix().first;
    }

    cout << "The total sum of all enabled mul instructions is: " << totalSum << endl;
    return 0;
}
