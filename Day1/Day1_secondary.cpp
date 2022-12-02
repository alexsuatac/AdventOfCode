// Algorithm plan:
// Read in data line by line and use a
// greedy algorithm to keep track of the
// top 3 largest sums, then sum them

#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

// takes a reference to a vector of current N largest numbers
// and a candidate then compares the candidate with each
// of the numbers in the vector, replacing the smallest
// of the values that it is greater than, or else do
// nothing if it is smaller than all the elements
void largestN(std::vector<int>& topNCalories, int candidate) {
    auto smallest = std::min_element(topNCalories.begin(), topNCalories.end());
    if (candidate > *smallest) {
        topNCalories[std::distance(topNCalories.begin(), smallest)] = candidate;
    }
}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);


    std::string curLine;
    std::vector<int> top3Calories = {0, 0, 0};
    int curCalories = 0;
    while (std::getline(ifs, curLine)) {
        if (curLine.empty()) {
            // insert into the vector if larger
            // than the smallest element already
            // in there
            largestN(top3Calories, curCalories);
            curCalories = 0;
        } else {
            curCalories += std::stoi(curLine);
        }
    }

    ifs.close();
    std::cout << std::accumulate(top3Calories.begin(), top3Calories.end(), 0) << std::endl;
    return 0;
}