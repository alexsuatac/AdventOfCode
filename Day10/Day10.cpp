#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>

static long X = 0; // global var for the register
struct instruction {
    std::string instruction;
    int val;
};
// parse the instructions and store them here
static std::vector<instruction> instructions = {};
struct state {
    std::string instruction;
    unsigned numCyclesToComplete;
    long XatCycleN;
};
 // store the instruction, cycle at which it was
 // executed and the value of X for each step of the program
static std::vector<state> memory = {};


// split a string up
std::vector<std::string> split(const std::string& str) {
    std::stringstream ss(str);
    std::string parsed;
    std::vector<std::string> result;
    while(std::getline(ss, parsed, ' ')) {
        result.push_back(parsed);
    }

    return result;
}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    int cycle = 0;
    while(std::getline(ifs, curLine)) {
        if(curLine == "noop") {
            instructions.push_back({.instruction = curLine, .val = 0});
        } else {
            auto parsed = split(curLine);
            instructions.push_back({.instruction = parsed[0], .val = std::stoi(parsed[1])});
        }
    }

    ifs.close();
    return 0;
}