#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
using namespace std;

// Directions: up, right, down, left
const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void printGrid(const vector<string>& grid) {
    for (const string& row : grid) {
        cout << row << endl;
    }
    cout << endl;
}

int simulateGuard(vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    int startX = -1, startY = -1, direction = -1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '^') {
                startX = i;
                startY = j;
                direction = 0;
                break;
            } else if (grid[i][j] == '>') {
                startX = i;
                startY = j;
                direction = 1;
                break;
            } else if (grid[i][j] == 'v') {
                startX = i;
                startY = j;
                direction = 2;
                break;
            } else if (grid[i][j] == '<') {
                startX = i;
                startY = j;
                direction = 3;
                break;
            }
        }
    }

    set<pair<int, int>> visited;
    visited.insert({startX, startY});
    grid[startX][startY] = 'X';

    int x = startX, y = startY;
    int iteration = 0;
    const int MAX_ITERATIONS = 10000;

    while (true) {
        iteration++;
        if (iteration > MAX_ITERATIONS) {
            cerr << "Error: Exceeded maximum iterations. Possible infinite loop." << endl;
            break;
        }

        int nextX = x + directions[direction].first;
        int nextY = y + directions[direction].second;

        if (nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols) {
            break;
        }

        if (grid[nextX][nextY] == '#') {
            direction = (direction + 1) % 4;
            continue;
        }

        x = nextX;
        y = nextY;

        if (visited.insert({x, y}).second)

        grid[x][y] = 'X';
    }

    return visited.size();
}

int main() {
    string filename = "input.txt";

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }

    vector<string> grid;
    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    inputFile.close();

    int distinctPositions = simulateGuard(grid);
    cout << "Distinct positions visited: " << distinctPositions << endl;

    return 0;
}
