// Algorithm plan:
// Read in data line by line and use a
// greedy algorithm to keep track of the
// largest sum

#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    int mostCalories = 0;
    int curCalories = 0;
    while (std::getline(ifs, curLine)) {
        if (curLine.empty()) {
            if (curCalories > mostCalories) {
                mostCalories = curCalories;
            }
            curCalories = 0;
        } else {
            curCalories += std::stoi(curLine);
        }
    }

    ifs.close();
    std::cout << mostCalories << std::endl;
    return 0;
}