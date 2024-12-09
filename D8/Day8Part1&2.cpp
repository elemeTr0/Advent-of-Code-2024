#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <complex>
#include <string>
#include <sstream>

using namespace std;

using Complex = complex<int>;
using Map = unordered_map<Complex, char, hash<Complex>>;

namespace std {
    template <>
    struct hash<Complex> {
        size_t operator()(const Complex& c) const {
            return hash<int>()(c.real()) ^ (hash<int>()(c.imag()) << 1);
        }
    };
}

unordered_set<Complex> GetUniquePositions(const string& input,
                                           vector<Complex> (*getAntinodes)(const Complex&, const Complex&, const Map&));
vector<Complex> GetAntinodes1(const Complex& srcAntenna, const Complex& dstAntenna, const Map& map);
vector<Complex> GetAntinodes2(const Complex& srcAntenna, const Complex& dstAntenna, const Map& map);
Map GetMap(const string& input);

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open file 'input.txt'" << endl;
        return 1;
    }

    string input;
    string line;
    while (getline(inputFile, line)) {
        input += line + "\n";
    }
    inputFile.close();

    cout << "Part 1: " << GetUniquePositions(input, GetAntinodes1).size() << endl;
    cout << "Part 2: " << GetUniquePositions(input, GetAntinodes2).size() << endl;

    return 0;
}

unordered_set<Complex> GetUniquePositions(const string& input,
                                           vector<Complex> (*getAntinodes)(const Complex&, const Complex&, const Map&)) {
    Map map = GetMap(input);
    vector<Complex> antennaLocations;

    for (const auto& [pos, val] : map) {
        if (isalnum(val)) {
            antennaLocations.push_back(pos);
        }
    }

    unordered_set<Complex> result;

    for (const auto& srcAntenna : antennaLocations) {
        for (const auto& dstAntenna : antennaLocations) {
            if (srcAntenna != dstAntenna && map.at(srcAntenna) == map.at(dstAntenna)) {
                auto antinodes = getAntinodes(srcAntenna, dstAntenna, map);
                result.insert(antinodes.begin(), antinodes.end());
            }
        }
    }

    return result;
}

vector<Complex> GetAntinodes1(const Complex& srcAntenna, const Complex& dstAntenna, const Map& map) {
    vector<Complex> antinodes;
    Complex dir = dstAntenna - srcAntenna;
    Complex antinode = dstAntenna + dir;

    if (map.find(antinode) != map.end()) {
        antinodes.push_back(antinode);
    }

    return antinodes;
}

vector<Complex> GetAntinodes2(const Complex& srcAntenna, const Complex& dstAntenna, const Map& map) {
    vector<Complex> antinodes;
    Complex dir = dstAntenna - srcAntenna;
    Complex antinode = dstAntenna;

    while (map.find(antinode) != map.end()) {
        antinodes.push_back(antinode);
        antinode += dir;
    }

    return antinodes;
}

Map GetMap(const string& input) {
    Map map;
    istringstream stream(input);
    string line;
    int y = 0;

    while (getline(stream, line)) {
        for (int x = 0; x < (int)line.size(); x++) {
            map[{x, -y}] = line[x];
        }
        y++;
    }

    return map;
}
