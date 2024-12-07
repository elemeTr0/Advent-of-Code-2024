#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

long long evaluateExpression(const vector<long long>& numbers, const vector<char>& operators) {
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        }
    }
    return result;
}

bool canMatchTarget(const vector<long long>& numbers, long long target) {
    size_t numOperators = numbers.size() - 1;
    size_t totalCombinations = 1ULL << numOperators;
    for (size_t mask = 0; mask < totalCombinations; ++mask) {
        vector<char> operators;
        for (size_t i = 0; i < numOperators; ++i) {
            if (mask & (1ULL << i)) {
                operators.push_back('+');
            } else {
                operators.push_back('*');
            }
        }
        if (evaluateExpression(numbers, operators) == target) {
            return true;
        }
    }
    return false;
}

bool processEquation(const string& line, long long& target) {
    stringstream ss(line);
    string temp;
    vector<long long> numbers;

    getline(ss, temp, ':');
    if (temp.empty()) {
        cerr << "Error: Missing target value in line: " << line << endl;
        return false;
    }

    try {
        target = stoll(temp);
    } catch (const exception& e) {
        cerr << "Error: Invalid target value '" << temp << "' in line: " << line << endl;
        return false;
    }
    while (getline(ss, temp, ' ')) {
        if (!temp.empty()) {
            try {
                numbers.push_back(stoll(temp));
            } catch (const exception& e) {
                cerr << "Error: Invalid number '" << temp << "' in line: " << line << endl;
                return false;
            }
        }
    }

    if (numbers.empty()) {
        cerr << "Error: No numbers provided for target value " << target << " in line: " << line << endl;
        return false;
    }

    return canMatchTarget(numbers, target);
}

int main() {
    ifstream inputFile("input.txt");

    string line;
    long long totalSum = 0;

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            long long target;
            if (processEquation(line, target)) {
                totalSum += target;
            }
        }
    }

    inputFile.close();
    cout << "Total sum of solvable equations: " << totalSum << endl;
    return 0;
}
