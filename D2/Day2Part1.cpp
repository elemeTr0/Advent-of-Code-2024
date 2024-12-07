#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

bool isSafe(const vector<int>& levels) {

    bool isIncreasing = true;
    bool isDecreasing = true;

    for (size_t i = 1; i < levels.size(); ++i) {
        int diff = levels[i] - levels[i - 1];

        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }

        if (diff > 0) {
            isDecreasing = false;
        } else if (diff < 0) {
            isIncreasing = false;
        }
    }

    return isIncreasing || isDecreasing;
}


bool isSafeAfterRemovingOne(const vector<int>& levels) {

    for (size_t i = 0; i < levels.size(); ++i) {
        vector<int> modifiedLevels;


        for (size_t j = 0; j < levels.size(); ++j) {
            if (j != i) {
                modifiedLevels.push_back(levels[j]);
            }
        }


        if (isSafe(modifiedLevels)) {
            return true;
        }
    }

    return false;
}

int main() {

    ifstream inputFile("input.txt");

    vector<vector<int>> reports;
    string line;


    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<int> report;
        int number;

        while (ss >> number) {
            report.push_back(number);
        }

        if (!report.empty()) {
            reports.push_back(report);
        }
    }

    inputFile.close();


    int safeCount = 0;
    for (const auto& report : reports) {
        if (isSafe(report)) {
            ++safeCount;
        } else if (isSafeAfterRemovingOne(report)) {
            ++safeCount;
        }
    }

    cout << "Number of safe reports: " << safeCount << endl;
    return 0;
}
