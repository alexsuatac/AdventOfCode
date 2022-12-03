// Algorithm plan:
// Read in data line by line
// convert each character into a point
// keep a running sum of the total score

#include <iostream>
#include <fstream>
#include <string>
#include <map>

// convert the string into a point
// rock = 1 | paper = 2 | scissors = 3
static std::map<std::string, int> pointMap = {
    {"A", 1}, // r
    {"B", 2}, // p
    {"C", 3}, // s
    {"X", 1}, // r
    {"Y", 2}, // p
    {"Z", 3}  // s
};

static int getScore(const std::string& attack, const std::string& requiredDefense) {
    if (requiredDefense == "Y") { // must draw
        return pointMap.at(attack) + 3;
    }

    if (requiredDefense == "X") { // must lose
        if (attack == "A") {
            return 3;
        } else if (attack == "B") {
            return 1;
        } else {
            return 2;
        }
    }

    if (requiredDefense == "Z") { // must win
        if (attack == "A") {
            return 2 + 6;
        } else if (attack == "B") {
            return 3 + 6;
        } else {
            return 1 + 6;
        }
    }
    return 0;

}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    int totalScore = 0;
    while (std::getline(ifs, curLine)) {
        totalScore += getScore(curLine.substr(0,1), 
            curLine.substr(2,1));
    }

    ifs.close();
    std::cout << totalScore << std::endl;
    return 0;
}