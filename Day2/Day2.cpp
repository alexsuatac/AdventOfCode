// Algorithm plan:
// Read in data line by line
// convert each character into a point
// keep a running sum of the total score

#include <iostream>
#include <fstream>
#include <string>
#include <map>

// convert the string into a point
// A/X = 1 | B/Y = 2 | C/Z = 3
static std::map<std::string, int> pointMap = {
    {"A", 1},
    {"B", 2},
    {"C", 3},
    {"X", 1},
    {"Y", 2},
    {"Z", 3}
};

static int getScore(const int attack, const int defense) {
    if (attack == defense) {
        return defense + 3; // draw
    }

    // determine which type of game was played
    // by summing the individual moves
    // determine the winner by comparing the moves
    // taking into account which type of game it was
    int sum = attack + defense;
    if ((attack > defense) && (sum == 3 || sum == 5) || // rock - paper game or paper - scissors game
        (attack < defense) && (sum == 4)) { // rock - scissors game
        return defense; // lose
    } else {
        return defense + 6; // win
    }

}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    int totalScore = 0;
    while (std::getline(ifs, curLine)) {
        int attack = pointMap.at(curLine.substr(0,1));
        int defense = pointMap.at(curLine.substr(2,1));
        totalScore += getScore(attack, defense);
    }

    ifs.close();
    std::cout << totalScore << std::endl;
    return 0;
}