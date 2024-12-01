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


    int result = 0;
    for (size_t i = 0; i < leftList.size(); i++) {
        int p=0;
        for (size_t j = 0; j < leftList.size(); j++) {
                if(leftList[i]==rightList[j])
                p++;
    }
    result=result+leftList[i]*p;
    }

    return result;
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

    int result = calculateTotalDistance(leftList, rightList);

    cout << "The result is: " << result << endl;

    return 0;
}
