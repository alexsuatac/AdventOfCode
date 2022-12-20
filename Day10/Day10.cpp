#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

static long X = 1; // global var for the register
static const size_t SCREEN_WIDTH = 40;
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
    char pixel;
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

// return true if pixel is in sprite
bool isCurPixelInSprite(unsigned &curPixel) {
    if (curPixel == SCREEN_WIDTH) curPixel = 0;
    return (curPixel == (X-1) ||
            curPixel == X ||
            curPixel == (X+1) );
}

// process the code
void runProcess() {
    unsigned cycle = 0;
    unsigned &curPix = cycle; 
    char pix;

    // store the initial state
    state tmp = {.instruction = "initial", .cycleN = cycle, .XatCycleN = X, .pixel = '\0'};
    memory.push_back(tmp);
    
    for(auto const& line : instructions) {
        if(line.instruction == "noop") {
            (isCurPixelInSprite(curPix) ? pix = '#' : pix = '.');
            cycle += 1;
            
            memory.push_back({.instruction = line.instruction, .cycleN = cycle, .XatCycleN = X, .pixel = pix});
        } else {
            // store the state at the first clock
            (isCurPixelInSprite(curPix) ? pix = '#' : pix = '.');
            cycle += 1;
            memory.push_back({.instruction = line.instruction, .cycleN = cycle, .XatCycleN = X, .pixel = pix });
            
            // update the register and store the state with the second clock
            (isCurPixelInSprite(curPix) ? pix = '#' : pix = '.');
            cycle += 1;
            X += line.val;
            memory.push_back({.instruction = line.instruction, .cycleN = cycle, .XatCycleN = X , .pixel = pix});
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

void renderScreen() {
    size_t cnt = 1;
    for(auto it = memory.begin()+1; it != memory.end(); ++it) {
        std::cout << it->pixel;
        if(cnt++ == SCREEN_WIDTH) {
            std::cout << "\n";
            cnt = 1;
        }
    }
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
    renderScreen();
    ifs.close();
    return 0;
}