// Algorithm plan:
// Read in data line by line
// Put together a subsequence
// described by that line and
// append it to the master sequence.
// Use stacks as the data structure for
// the crates

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>

//#include "Sequence.h"

class Sequence {
public:
    Sequence () = default;
    ~Sequence() = default;
    
    Sequence& move(unsigned moveCmd);
    Sequence& to(unsigned toCmd);
    Sequence& from(unsigned fromCmd);

    std::vector<unsigned> seq;
};

Sequence& Sequence::move(unsigned moveCmd) {
    seq.push_back(moveCmd);
    return *this;
}

Sequence& Sequence::to(unsigned toCmd) {
    seq.push_back(toCmd);
    return *this;
}

Sequence& Sequence::from(unsigned fromCmd) {
    seq.push_back(fromCmd);
    return *this;
}

// check if there is a non-number in the string
// return false if there is anything other than digits
bool isDigit(const std::string& str) {
    return !str.empty() && 
            str.find_first_not_of(" 0123456789") == std::string::npos;
}

size_t getStackIndex(size_t crateIndex) {
    if (crateIndex < 4) return 0;

    size_t stackIndex = 0;
    while (crateIndex > 4) {
        crateIndex -= 4;
        stackIndex++;
    }

    return stackIndex;
}

// push the crate names into the desired stack
void pushCratesToStack(std::string &input, std::vector<std::stack<char>>& crateStackVec) {
    const std::string CRATE_NAMES ("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::size_t found = input.find_first_of(CRATE_NAMES);
    while (found != std::string::npos) {
        size_t stackIndex = getStackIndex(found);
        crateStackVec[stackIndex].push(input[found]);
        found = input.find_first_of(CRATE_NAMES, found + 1);
    }
}

// for part 1
void moveCrates(std::vector<Sequence>& seqList, std::vector<std::stack<char>>& crates) {
    for(auto const& sequence : seqList) {
        unsigned numCratesToMove = sequence.seq[0];
        unsigned src = sequence.seq[1]-1;
        unsigned dest = sequence.seq[2]-1;

        for(int i = 0; i < numCratesToMove; i++) {
            crates[dest].push(crates[src].top());
            crates[src].pop();
        }   
    }
}

// for part 2
void moveMultipleCrates(std::vector<Sequence>& seqList, std::vector<std::stack<char>>& crates) {
    for(auto const& sequence : seqList) {
        unsigned numCratesToMove = sequence.seq[0];
        unsigned src = sequence.seq[1]-1;
        unsigned dest = sequence.seq[2]-1;

        // push onto a temp stack then pop back
        // onto the new stack - result is as if the whole
        // chunk were moved at once
        std::stack<char> tmp;
        for(int i = 0; i < numCratesToMove; ++i) {
            tmp.push(crates[src].top());
            crates[src].pop();
        }

        for(int i = 0; i < numCratesToMove; ++i) {
            crates[dest].push(tmp.top());
            tmp.pop();
        }
    }
}

// remove the "move", "from" and "to" keywords
void sanitizeInputStr(std::string &input) {
    std::size_t found = input.find_first_of("move");
    while (found != std::string::npos) {
        for (size_t i = found; i < found+4; i++) {
            input[i] = ' ';
        }
        break;
    }
    found = input.find_first_of("from");
    while (found != std::string::npos) {
        for (size_t i = found; i < found+4; i++) {
            input[i] = ' ';
        }
        break;
    }
    found = input.find_first_of("to");
    while (found != std::string::npos) {
        for (size_t i = found; i < found+2; i++) {
            input[i] = ' ';
        }
        break;
    }
}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;

    std::vector<std::string> slice;
    unsigned totalStacks = 0;
    while (std::getline(ifs, curLine)) {
        // collect the intial state of the crates
        // stop when the list of numbers is found
        if (!isDigit(curLine)) {
            slice.push_back(curLine);
        } else {
            break;
        }
    }

    // the biggest number in this line
    // is the number of stacks required.
    std::stringstream ss(curLine);
    unsigned val;
    while (ss >> val) {
        if (val > totalStacks) {
            totalStacks = val;
        }
    }

    // create N stacks, and iterate
    // backward through the slice vector, 
    // pushing the elements into their
    // respective stacks from the bottom up
    std::vector<std::stack<char>> crates(totalStacks);
    std::for_each(slice.rbegin(), slice.rend(),
        [&](auto s) { pushCratesToStack(s, crates); });

    // parse the move, from and to commands
    // since ifs is now pointing at the first 
    // sequence
    std::vector<Sequence> masterSequence;
    while(std::getline(ifs, curLine)) {
        if (curLine == "") continue;
        sanitizeInputStr(curLine);
        std::stringstream ss(curLine);
        unsigned val;
        std::vector<unsigned> seqCmd;
        while (ss >> val) {
            seqCmd.push_back(val);
        } 

        // create a sequence and append it to the
        // master sequence
        Sequence s;
        s.move(seqCmd[0]).to(seqCmd[1]).from(seqCmd[2]);
        masterSequence.push_back(s);
    }

    // Finally, carry out the sequence on the stack
    // of crates
    // moveCrates(masterSequence, crates);
    moveMultipleCrates(masterSequence, crates);

    ifs.close();
    std::string result("");
    for(const auto& crate : crates) {
        result.append(std::string{crate.top()});
    }

    std::cout << result << std::endl;
    return 0;
}