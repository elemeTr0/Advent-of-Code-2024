#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    string filePath = "input.txt";

    ifstream inputFile(filePath);

    string memory((istreambuf_iterator<char>(inputFile)),
                  istreambuf_iterator<char>());

    inputFile.close();

    regex validMulRegex(R"(mul\((\d{1,3}),(\d{1,3})\))");

    smatch match;
    int totalSum = 0;

    string::const_iterator searchStart(memory.cbegin());
    while (regex_search(searchStart, memory.cend(), match, validMulRegex)) {
        int x = stoi(match[1].str());
        int y = stoi(match[2].str());

        totalSum += x * y;

        searchStart = match.suffix().first;
    }

    cout << "The total sum of all valid mul instructions is: " << totalSum << endl;

    return 0;
}
