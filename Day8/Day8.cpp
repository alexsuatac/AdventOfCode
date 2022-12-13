#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#include <map>

static std::map<size_t, std::map<size_t, int>> vis_map = {};

// add trees that are visible to a map so that
// they are checked to not be counted more than once
void findVisible(const std::vector<int> &treeline)
{
    static size_t row = 0;

    auto addToMapFromLeft = [&](auto tree) {
        for(auto i = 0; i < treeline.size(); ++i) {
            auto maxSoFar = *std::max_element(treeline.begin(), treeline.begin()+i);
            if(treeline[i] > maxSoFar) {
                // mark that the tree is visible from at least one direction
                // if the tree is already marked visible this will have no effect
                vis_map[row][i] = 1;
            }
        }
    };

    std::for_each(treeline.begin(), treeline.end(), addToMapFromLeft);

    auto addToMapFromRight = [&](auto tree) {
        for(auto i = treeline.size()-1; i > 0; --i) {
            auto maxSoFar = *std::max_element(treeline.rbegin(), treeline.rend()-(i+1));
            if(treeline[i] > maxSoFar) {
                // mark that the tree is visible from at least one direction
                // if the tree is already marked visible this will have no effect
                vis_map[row][i] = 1;
            }
        }
    };
    std::for_each(treeline.rbegin(), treeline.rend(), addToMapFromRight);

    // mark both edges as visible
    vis_map[row][0] = 1;
    vis_map[row][treeline.size()-1] = 1;

    // reset row counter when moving onto transpose of matrix
    if(++row == treeline.size()-2) row = 0;
}

int main()
{
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    std::vector<std::vector<int>> grid;
    while (std::getline(ifs, curLine))
    {
        std::vector<int> tmp;
        for (auto const &digit : curLine)
        {
            tmp.push_back(std::stoi(std::string(1, digit)));
        }
        grid.push_back(tmp);
    }

    // do the algorithm for both the original layout and its transpose
    std::for_each(grid.begin() + 1, grid.end() - 1,
                  [&](auto t) {findVisible({t.begin(), t.end()}); });

    // get transpose
    std::vector<std::vector<int>> gridT = grid;
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            gridT[j][i] = grid[i][j];
        }
    }

    std::for_each(gridT.begin() + 1, gridT.end() - 1,
                  [&](auto t) {findVisible({t.begin(), t.end()}); });
    
    size_t totalVisible = 4; // the four corners of the grid that are not visited in this algorithm

    for(auto const& col : vis_map) {
        totalVisible += col.second.size();
    }

    ifs.close();
    std::cout << totalVisible << std::endl;
    return 0;
}