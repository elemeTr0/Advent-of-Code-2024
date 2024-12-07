#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <string>
#include <chrono>

using namespace std;

const map<char, pair<int, int>> DIRECTION_MOVEMENT = {
    {'^', {-1, 0}},
    {'>', {0, 1}},
    {'V', {1, 0}},
    {'<', {0, -1}}
};

const map<char, char> NEXT_DIRECTION = {
    {'^', '>'},
    {'>', 'V'},
    {'V', '<'},
    {'<', '^'}
};

struct Timer {
    chrono::high_resolution_clock::time_point start_time;

    Timer() { start_time = chrono::high_resolution_clock::now(); }
    ~Timer() {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
        cout << "Execution time: " << duration << " ms" << endl;
    }
};

void mainLogic(const string& input) {
    vector<vector<char>> patrol_map;
    size_t pos = 0, end;
    while ((end = input.find('\n', pos)) != string::npos) {
        patrol_map.push_back(vector<char>(input.begin() + pos, input.begin() + end));
        pos = end + 1;
    }
    patrol_map.push_back(vector<char>(input.begin() + pos, input.end()));

    int size_y = patrol_map.size();
    int size_x = patrol_map[0].size();

    pair<int, int> start_guard_pos = {0, 0};

    // Find the starting position of the guard
    for (int y = 0; y < size_y; ++y) {
        for (int x = 0; x < size_x; ++x) {
            if (patrol_map[y][x] == '^') {
                start_guard_pos = {y, x};
                break;
            }
        }
    }

    cout << "Starting position of guard: (" << start_guard_pos.first << ", " << start_guard_pos.second << ")" << endl;

    char direction = '^';
    set<pair<int, int>> initially_visited;
    pair<int, int> guard_pos = start_guard_pos;

    // Simulate the initial guard movement
    while (guard_pos.first >= 0 && guard_pos.first < size_y &&
           guard_pos.second >= 0 && guard_pos.second < size_x) {
        initially_visited.insert(guard_pos);
        auto movement = DIRECTION_MOVEMENT.at(direction);
        pair<int, int> new_pos = {guard_pos.first + movement.first, guard_pos.second + movement.second};
        if (new_pos.first < 0 || new_pos.first >= size_y || new_pos.second < 0 || new_pos.second >= size_x) {
            break;
        }
        if (patrol_map[new_pos.first][new_pos.second] == '#') {
            direction = NEXT_DIRECTION.at(direction);
        } else {
            guard_pos = new_pos;
        }
    }

    cout << "Guard initially visited " << initially_visited.size() << " positions." << endl;

    int count = 0;

    // Simulate for each possible obstacle placement
    for (int ob_y = 0; ob_y < size_y; ++ob_y) {
        for (int ob_x = 0; ob_x < size_x; ++ob_x) {
            if (initially_visited.count({ob_y, ob_x}) == 0 || make_pair(ob_y, ob_x) == start_guard_pos || patrol_map[ob_y][ob_x] == '#') {
                continue;
            }

            guard_pos = start_guard_pos;
            direction = '^';
            set<tuple<int, int, char>> visited_direction;

            // Simulate with an obstacle placed at (ob_y, ob_x)
            while (guard_pos.first >= 0 && guard_pos.first < size_y &&
                   guard_pos.second >= 0 && guard_pos.second < size_x) {
                if (visited_direction.count({guard_pos.first, guard_pos.second, direction}) > 0) {
                    cout << "Guard loop detected at: (" << guard_pos.first << ", " << guard_pos.second << ") with direction " << direction << endl;
                    count++;
                    break;
                }
                visited_direction.insert({guard_pos.first, guard_pos.second, direction});
                auto movement = DIRECTION_MOVEMENT.at(direction);
                pair<int, int> new_pos = {guard_pos.first + movement.first, guard_pos.second + movement.second};
                if (new_pos.first < 0 || new_pos.first >= size_y || new_pos.second < 0 || new_pos.second >= size_x) {
                    break;
                }
                if (patrol_map[new_pos.first][new_pos.second] == '#' || new_pos == make_pair(ob_y, ob_x)) {
                    direction = NEXT_DIRECTION.at(direction);
                } else {
                    guard_pos = new_pos;
                }
            }
        }
    }

    cout << "Total positions where placing an obstacle would create a loop: " << count << endl;
}

int main() {
    Timer timer;

    ifstream input_file("input.txt");  // Open the input file named "input.txt"
    if (!input_file.is_open()) {
        cerr << "Failed to open file: input.txt" << endl;
        return 1;
    }

    string input((istreambuf_iterator<char>(input_file)), istreambuf_iterator<char>());
    input_file.close();  // Close the file after reading

    mainLogic(input);

    return 0;
}
