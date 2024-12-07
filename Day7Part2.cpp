#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

long long concatenate(long long a, long long b) {
    string concat = to_string(a) + to_string(b);
    return stoll(concat);
}

bool canMatchTargetRecursive(const vector<long long>& numbers, long long target, size_t index, long long currentValue, unordered_map<string, bool>& memo, int depth) {

    if (index == numbers.size()) {
        return currentValue == target;
    }

    string key = to_string(index) + "_" + to_string(currentValue);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    bool result = false;

    // Addition
    result |= canMatchTargetRecursive(numbers, target, index + 1, currentValue + numbers[index], memo, depth + 1);

    // Multiplication
    result |= canMatchTargetRecursive(numbers, target, index + 1, currentValue * numbers[index], memo, depth + 1);

    // Concatenation
    result |= canMatchTargetRecursive(numbers, target, index + 1, concatenate(currentValue, numbers[index]), memo, depth + 1);

    memo[key] = result;
    return result;
}

bool canMatchTarget(const vector<long long>& numbers, long long target) {
    unordered_map<string, bool> memo;
    return canMatchTargetRecursive(numbers, target, 1, numbers[0], memo, 0);
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
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    string line;
    long long totalSum = 0;
    int lineCount = 0;

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            long long target;
            if (processEquation(line, target)) {
                totalSum += target;
            }
            lineCount++;
        }
    }

    inputFile.close();
    cout << "Total sum of solvable equations: " << totalSum << endl;
    return 0;
}
