#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

int calculateTotalDistance(vector<int>& leftList, vector<int>& rightList) {
    sort(leftList.begin(), leftList.end());
    sort(rightList.begin(), rightList.end());

    int totalDistance = 0;
    for (size_t i = 0; i < leftList.size(); i++) {
        int difference = abs(leftList[i] - rightList[i]);
        totalDistance += difference;
    }

    return totalDistance;
}

int main() {
    string fileName = "input.txt";

    ifstream inputFile(fileName);

    vector<int> leftList, rightList;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        int leftNum, rightNum;
        if (ss >> leftNum >> rightNum) {
            leftList.push_back(leftNum);
            rightList.push_back(rightNum);
        }
    }

    int totalDistance = calculateTotalDistance(leftList, rightList);

    cout << "The total distance between the lists is: " << totalDistance << endl;

    return 0;
}
