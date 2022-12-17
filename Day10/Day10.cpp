#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

static long X = 1; // global var for the register
struct instruction {
    std::string instruction;
    int val;
};
// parse the instructions and store them here
static std::vector<instruction> instructions = {};
struct state {
    std::string instruction;
    unsigned cycleN;
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

// process the code
void runProcess() {
    unsigned cycle = 0;

    // store the initial state
    state tmp = {.instruction = "initial", .cycleN = cycle, .XatCycleN = X};
    memory.push_back(tmp);

    for(auto const& line : instructions) {
        if(line.instruction == "noop") {
            cycle += 1;
            memory.push_back({.instruction = line.instruction, .cycleN = cycle, .XatCycleN = X});
        } else {
            // store the state at the first clock
            cycle += 1;
            memory.push_back({.instruction = line.instruction, .cycleN = cycle, .XatCycleN = X});
            
            // update the register and store the state with the second clock
            cycle += 1;
            X += line.val;
            memory.push_back({.instruction = line.instruction, .cycleN = cycle, .XatCycleN = X});
        }
    }
}

int getSumOfSignalStrengths() {
    return 20 * memory[19].XatCycleN +
            60 * memory[59].XatCycleN +
            100 * memory[99].XatCycleN +
            140 * memory[139].XatCycleN +
            180 * memory[179].XatCycleN +
            220 * memory[219].XatCycleN;
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

    runProcess();
    std::cout << "part 1: " << getSumOfSignalStrengths() << std::endl;

    ifs.close();
    return 0;
}