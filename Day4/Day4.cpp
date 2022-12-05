// Algorithm plan:
// Read in data line by line
// Separate into pairs of two numbers
// Compare each pair to determine if 
// one is contained by the other
// Keep track of number of such pairs

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static bool isContained(unsigned elf1_l, unsigned elf1_u,
                         unsigned elf2_l, unsigned elf2_u) {
    if ((elf1_l <= elf2_l) && (elf1_u >= elf2_u) ||
        (elf1_l >= elf2_l) && (elf1_u <= elf2_u)) {
            return true;
        }
    
    return false;
}

void sanitizeInputStr(std::string &input) {
    std::size_t found = input.find_first_of("-");
    while (found != std::string::npos) {
        input[found] = ' ';
        found = input.find_first_of("-", found + 1);
    }
    found = input.find_first_of(",");
    while (found != std::string::npos) {
        input[found] = ' ';
        found = input.find_first_of(",", found + 1);
    }
}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    int totalPairs = 0;
    while (std::getline(ifs, curLine)) {
        // replace the "-" and "," with " " 
        // to help with conversion to unsigned int
        sanitizeInputStr(curLine);
        unsigned elf1_lower, elf1_upper, elf2_lower, elf2_upper;
        std::stringstream ss(curLine);
        ss >> elf1_lower >> elf1_upper >> elf2_lower >> elf2_upper;
        if (isContained(elf1_lower, elf1_upper, elf2_lower, elf2_upper)) {
            totalPairs++;
        }
    }

    ifs.close();
    std::cout << totalPairs << std::endl;
    return 0;
}