// Algorithm plan:
// Read in data line by line
// Separate each line into both halves
// Find the element that appears in both halves
// Keep track of the running total of each item priority

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

static int getPriority(const std::string& rucksack) {
    // split the rucksack up into two vectors
    // one for each compartment
    const size_t halfway = rucksack.size()/2;
    std::vector<char> rsFirst(rucksack.begin(), rucksack.begin()+halfway);
    std::vector<char> rsSecond(rucksack.begin()+halfway, rucksack.end());

    // sort
    std::sort(rsFirst.begin(), rsFirst.end());
    std::sort(rsSecond.begin(), rsSecond.end());

    // find the first instance in both sorted ranges where the values are equal
    std::vector<char> result(1);
    std::set_intersection(rsFirst.begin(), rsFirst.end(), 
                            rsSecond.begin(), rsSecond.end(), result.begin());

    return PRIORITY_SCORE.at(result.at(0));
}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    int total = 0;
    while (std::getline(ifs, curLine)) {
        total += getPriority(curLine);
    }

    ifs.close();
    std::cout << total << std::endl;
    return 0;
}