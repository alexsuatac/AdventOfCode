// Algorithm plan:
// Read in data line by line
// Separate into groups of three
// Find the intersection of each group
// Return running total of the priority scores

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

static const std::map<char, int> PRIORITY_SCORE =
{
  {'a', 1},
  {'b', 2},
  {'c', 3},
  {'d', 4},
  {'e', 5},
  {'f', 6},
  {'g', 7},
  {'h', 8},
  {'i', 9},
  {'j', 10},
  {'k', 11},
  {'l', 12},
  {'m', 13},
  {'n', 14},
  {'o', 15},
  {'p', 16},
  {'q', 17},
  {'r', 18},
  {'s', 19},
  {'t', 20},
  {'u', 21},
  {'v', 22},
  {'w', 23},
  {'x', 24},
  {'y', 25},
  {'z', 26},
  {'A', 27},
  {'B', 28},
  {'C', 29},
  {'D', 30},
  {'E', 31},
  {'F', 32},
  {'G', 33},
  {'H', 34},
  {'I', 35},
  {'J', 36},
  {'K', 37},
  {'L', 38},
  {'M', 39},
  {'N', 40},
  {'O', 41},
  {'P', 42},
  {'Q', 43},
  {'R', 44},
  {'S', 45},
  {'T', 46},
  {'U', 47},
  {'V', 48},
  {'W', 49},
  {'X', 50},
  {'Y', 51},
  {'Z', 52}  
};

static int getPriority(std::vector<std::string>& group) {
    // split the strings into their own vectors
    std::vector<char> elf1(group[0].begin(), group[0].end());
    std::vector<char> elf2(group[1].begin(), group[1].end());
    std::vector<char> elf3(group[2].begin(), group[2].end());
    
    // sort
    std::sort(elf1.begin(), elf1.end());
    std::sort(elf2.begin(), elf2.end());
    std::sort(elf3.begin(), elf3.end());
    

    // find the intersection of all three vectors
    std::vector<char> elf1_elf2;
    std::set_intersection(elf1.begin(), elf1.end(), 
                            elf2.begin(), elf2.end(), back_inserter(elf1_elf2));
    
    std::vector<char> result;
    std::set_intersection(elf1_elf2.begin(), elf1_elf2.end(), 
                            elf3.begin(), elf3.end(), back_inserter(result));


    return PRIORITY_SCORE.at(result.at(0));
}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    int total = 0;
    int cnt = 0;
    std::vector<std::string> group; 
    while (std::getline(ifs, curLine)) {
        group.push_back(curLine);
        if (++cnt == 3) {
            total += getPriority(group);
            cnt = 0;
            group.clear();
        }
    }

    ifs.close();
    std::cout << total << std::endl;
    return 0;
}