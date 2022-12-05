// Algorithm plan:
// Read in data line by line
// Expand each pair into a sequence
// Check if there is an intersection between
// the two sets, and return true if there is
// Keep track of how many intersections there are

#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

static bool doesOverlap(std::vector<unsigned>& elf1, std::vector<unsigned>& elf2) {
    std::vector<unsigned> intersection;
    std::set_intersection(elf1.begin(), elf1.end(),
                            elf2.begin(), elf2.end(),
                            back_inserter(intersection));

    return !intersection.empty();
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

void generateSequence(std::vector<unsigned>& elf, unsigned lower, unsigned upper) {
    std::iota(elf.begin(), elf.begin()+(upper-lower)+1, lower);
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

        // create a sequence using the upper and lower bounds
        // for each elf
        unsigned elf1_lower, elf1_upper, elf2_lower, elf2_upper;
        std::stringstream ss(curLine);
        ss >> elf1_lower >> elf1_upper >> elf2_lower >> elf2_upper;

        std::vector<unsigned> elf1((elf1_upper-elf1_lower)+1);
        generateSequence(elf1, elf1_lower, elf1_upper);

        std::vector<unsigned> elf2((elf2_upper-elf2_lower)+1);
        generateSequence(elf2, elf2_lower, elf2_upper);

        if (doesOverlap(elf1, elf2)) {
            totalPairs++;
        }
    }

    ifs.close();
    std::cout << totalPairs << std::endl;
    return 0;
}