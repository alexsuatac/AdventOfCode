// Algorithm plan:
// Read in data string
// iterate over slices of 4 elements
// creating a set out of each
// once a set of size N exists
// the message delimiter has been found

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

// return the message
auto getEndOfMessage(std::string& msg, size_t delimSize) {
    std::string::iterator it;
    for (it = msg.begin(); it != msg.end(); ++it) {
        std::string tmp(it, it+delimSize);
        if(std::unordered_set<char> (tmp.begin(), tmp.end()).size() == delimSize) break;
    }
    return std::distance(msg.begin(), it+delimSize);
}
int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    std::getline(ifs, curLine);
    ifs.close();

    std::cout << "Part1: " << getEndOfMessage(curLine, 4) << std::endl;
    std::cout << "Part2: " << getEndOfMessage(curLine, 14) << std::endl;
    return 0;
}