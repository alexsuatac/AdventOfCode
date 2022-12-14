// Algorithm plan:
// Read in data string line by line
// We have all the information without
// having to move around the filesystem.
// Instead, the total size of every directory
// needs to be kept track of as well as the
// relationship between them - then at the end
// iterate through that final data structure,
// summing all the sizes that are <= 100,000

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <vector>

struct dir {
    std::vector<dir> subdirs;
    std::string name;
    int totalSize;
};

// refernce to the currently active directory
static std::stack<dir*> navHistory = {};
static std::vector<dir> filesystem = {};
static dir* curDir = nullptr;

// check if there is a non-number in the string
// return false if there is anything other than digits
bool isDigit(const std::string& str) {
    return !str.empty() && 
            str.find_first_not_of("0123456789") == std::string::npos;
}

void parseFilesystem(std::vector<std::string>& cmd) {
    dir tmp {.subdirs = {}, .name = "", .totalSize = 0};

    if (cmd.size() > 2 && cmd[2] == "/") {
        tmp.name = "/";
        filesystem.push_back(tmp);
        curDir = &filesystem[0];
        navHistory.push(curDir);
        return;
    }

    if (cmd[1] == "cd") {
        if (cmd[2] == ".."){ 
            // change to the parent directory
            auto subDirSize = curDir->totalSize;
            navHistory.pop();
            curDir = navHistory.top();
            curDir->totalSize += subDirSize;
        } else {
            for (size_t i = 0; i < curDir->subdirs.size(); ++i) {
                if (curDir->subdirs[i].name == cmd[2]) {
                    curDir = &curDir->subdirs[i];
                    navHistory.push(curDir);
                    return;
                }
            }
        }
    } else if (cmd[0] == "dir") {
        tmp.name = cmd[1];
        curDir->subdirs.push_back(tmp);
    } else if (isDigit(cmd[0])) {
        curDir->totalSize += std::stoi(cmd[0]);
    }

}

int accumulateSize(std::vector<dir> dirs, dir* cur, int& sum) {
    if (cur->subdirs.empty()) {
        return cur->totalSize;
    }

    for (auto c : dirs) {
        cur = &c;
        sum += accumulateSize(c.subdirs, cur, sum);
    }

    return sum;
}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    while(std::getline(ifs, curLine)) {
        std::vector<std::string> cmds;
        std::stringstream ss (curLine);
        std::string parsed;
        while(std::getline(ss, parsed, ' ')) {
            cmds.push_back(parsed);
        }
        if (cmds[1] != "ls") {
            parseFilesystem(cmds);
        }
    }

    // now that the filesystem is mapped, add the total
    // size of the subdirectories to the parent directories
    int sum = 0;
    int& totalSum = sum;
    accumulateSize(filesystem, &filesystem[0], totalSum);
    std::cout << totalSum << std::endl;

    ifs.close();
    return 0;
}