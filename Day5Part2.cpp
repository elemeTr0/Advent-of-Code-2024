#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

bool isValidOrder(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules) {
    unordered_map<int, int> position;
    for (int i = 0; i < update.size(); i++) {
        position[update[i]] = i;
    }

    for (const auto& [x, ySet] : rules) {
        if (position.find(x) != position.end()) {
            for (int y : ySet) {
                if (position.find(y) != position.end() && position[x] >= position[y]) {
                    return false;
                }
            }
        }
    }

    return true;
}

vector<int> reorderUpdate(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules) {
    unordered_map<int, int> inDegree;
    unordered_map<int, vector<int>> graph;
    for (int page : update) {
        inDegree[page] = 0;
        graph[page] = {};
    }

    for (const auto& [x, ySet] : rules) {
        if (inDegree.find(x) != inDegree.end()) {
            for (int y : ySet) {
                if (inDegree.find(y) != inDegree.end()) {
                    graph[x].push_back(y);
                    inDegree[y]++;
                }
            }
        }
    }

    priority_queue<int, vector<int>, greater<int>> zeroInDegree;
    for (const auto& [node, degree] : inDegree) {
        if (degree == 0) {
            zeroInDegree.push(node);
        }
    }

    vector<int> sortedUpdate;
    while (!zeroInDegree.empty()) {
        int node = zeroInDegree.top();
        zeroInDegree.pop();
        sortedUpdate.push_back(node);

        for (int neighbor : graph[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                zeroInDegree.push(neighbor);
            }
        }
    }

    return sortedUpdate;
}

int main() {
    ifstream inputFile("input.txt");


    string line;
    unordered_map<int, unordered_set<int>> rules;
    vector<vector<int>> updates;

    while (getline(inputFile, line) && !line.empty()) {
        stringstream ss(line);
        string rule;
        while (getline(ss, rule, ' ')) {
            int x, y;
            sscanf(rule.c_str(), "%d|%d", &x, &y);
            rules[x].insert(y);
        }
    }
    while (getline(inputFile, line)) {
        stringstream ss(line);
        vector<int> update;
        int page;
        while (ss >> page) {
            update.push_back(page);
            if (ss.peek() == ',') ss.ignore();
        }
        updates.push_back(update);
    }

    inputFile.close();

    int middleSum = 0;

    for (const auto& update : updates) {
        if (!isValidOrder(update, rules)) {
            vector<int> correctedUpdate = reorderUpdate(update, rules);
            middleSum += correctedUpdate[correctedUpdate.size() / 2];
        }
    }

    cout << "Sum of middle page numbers for corrected updates: " << middleSum << endl;

    return 0;
}
