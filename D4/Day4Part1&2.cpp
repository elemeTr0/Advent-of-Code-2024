#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;


bool matchesWord(const vector<string>& grid, int startRow, int startCol, int dRow, int dCol) {
    string word = "XMAS";
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < word.length(); ++i) {
        int newRow = startRow + i * dRow;
        int newCol = startCol + i * dCol;

        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) return false;
        if (grid[newRow][newCol] != word[i]) return false;
    }

    return true;
}

// Function to count the occurrences of the word in all directions
int countWordOccurrences(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<pair<int, int>> directions = {
        {0, 1},   // right
        {0, -1},  // left
        {1, 0},   // down
        {1, 1},   // down-right
        {1, -1},  // down-left
        {-1, 0},  // up
        {-1, 1},  // up-right
        {-1, -1}  // up-left
    };

    int count = 0;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            for (const auto& direction : directions) {
                int dRow = direction.first;
                int dCol = direction.second;
                if (matchesWord(grid, row, col, dRow, dCol)) {
                    count++;
                }
            }
        }
    }

    return count;
}

bool matchesXShape(const vector<string>& grid, int centerRow, int centerCol) {
    int topLeftRow = centerRow - 1, topLeftCol = centerCol - 1;
    int topRightRow = centerRow - 1, topRightCol = centerCol + 1;
    int bottomLeftRow = centerRow + 1, bottomLeftCol = centerCol - 1;
    int bottomRightRow = centerRow + 1, bottomRightCol = centerCol + 1;

    string wordOne = string(1, grid[topLeftRow][topLeftCol]) +
                     string(1, grid[centerRow][centerCol]) +
                     string(1, grid[bottomRightRow][bottomRightCol]);

    string wordTwo = string(1, grid[topRightRow][topRightCol]) +
                     string(1, grid[centerRow][centerCol]) +
                     string(1, grid[bottomLeftRow][bottomLeftCol]);

    unordered_set<string> validWords = {"MAS", "SAM"};
    return validWords.count(wordOne) > 0 && validWords.count(wordTwo) > 0;
}

int countXShapeOccurrences(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    for (int row = 1; row < rows - 1; ++row) {
        for (int col = 1; col < cols - 1; ++col) {
            if (matchesXShape(grid, row, col)) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    ifstream inputFile("input.txt");


    vector<string> grid;
    string line;
    while (getline(inputFile, line)) {
        grid.push_back(line);
    }


    int partOne = countWordOccurrences(grid);
    cout << "Part 1: " << partOne << endl;

    int partTwo = countXShapeOccurrences(grid);
    cout << "Part 2: " << partTwo << endl;

    return 0;
}
