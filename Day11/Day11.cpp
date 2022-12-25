#include <algorithm>
#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

// encapsulate monkey behaviour
struct monkey_behaviour {
    std::pair<int, std::string> op;
    int test_op;
    std::pair<size_t, size_t> pos_op;
};
struct monkey {
    int cnt = 0;
    std::queue<int> items;
    bool is_multiplied_by_self;
    bool test_result;
    size_t monkey_pos;
    monkey_behaviour mb;
};

// split a string up
std::vector<std::string> split(const std::string& str, const char delim = ' ') {
    std::stringstream ss(str);
    std::string parsed;
    std::vector<std::string> result;
    while(std::getline(ss, parsed, delim)) {
        result.push_back(parsed);
    }

    return result;
}

std::queue<int> getStartingItems(const std::string& itemList) {
    auto all = split({itemList.begin()+18, itemList.end()}, ',');

    std::queue<int> items;
    for(auto const& item : all) {
        items.push(std::stoi(item));
    }

    return items;
}

auto getOperationOperand(const std::string& operationStr, bool& isMultipliedBySelf) {
    int operand = -1;
    if (std::isdigit(operationStr[25])) {
        std::string numStr({operationStr.begin()+25, operationStr.end()}); 
        operand = std::stoi(numStr);
        isMultipliedBySelf = false;
    } else {
        isMultipliedBySelf = true;
    }

    std::string op ({operationStr[23]});
    if (op == "+") {
        return std::pair<int, std::string>(operand, "+");
    }
    
    return std::pair<int, std::string>(operand, "*");
}

int doOperation(std::pair<int, std::string> op, int item, bool isMultipliedBySelf) {
    if(op.second == "+") {
        return (item + op.first) / 3;
    } else if (isMultipliedBySelf) {
        return (item * item) / 3;
    }
    
    return (item * op.first) / 3;
}

int getTestOperand(const std::string& testStr) {
    std::string testVal({testStr.begin()+21, testStr.end()});
    return std::stoi(testVal);
}

bool doTest(int val, int item) {
    return (item % val) == 0;
}

std::pair<size_t, size_t> getMonkeyPositionOperands(const std::string& m1, const std::string& m2) {
    std::string monkey1({m1.begin()+29, m1.end()});
    std::string monkey2({m2.begin()+30, m2.end()});

    auto first = static_cast<size_t> (std::stoi(monkey1));
    auto second = static_cast<size_t> (std::stoi(monkey2));

    return std::pair<size_t, size_t>(first, second); 
}

size_t getMonkeyPosition(size_t pos1, size_t pos2, bool cond) {
    if (cond) {
        return pos1;
    }
  
    return pos2;
}

void processMonkeyState(std::vector<monkey>& monkeys, const int N) {
    for(size_t i = 0; i < N; ++i) {
        for(auto & monkey : monkeys) {
            while(!monkey.items.empty()) {
                // process the next state
                monkey.items.front() = doOperation(monkey.mb.op, monkey.items.front(),
                                                    monkey.is_multiplied_by_self);
                monkey.test_result = doTest(monkey.mb.test_op, monkey.items.front());
                monkey.monkey_pos = getMonkeyPosition(monkey.mb.pos_op.first,
                                                        monkey.mb.pos_op.second, monkey.test_result);

                // increase count and move items from one monkey to the other
                monkey.cnt++;
                monkeys[monkey.monkey_pos].items.push(monkey.items.front());
                monkey.items.pop();
            }
        } 
    }
}

int getItemHandlingCountProduct(std::vector<monkey>& monkeys) {
    std::vector<int> counts;
    for(auto const& monkey : monkeys) {
        counts.push_back(monkey.cnt);
    }

    std::sort(counts.begin(), counts.end());
    return counts[6] * counts[7];
}


int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./input.txt", std::ifstream::in);

    std::string curLine;
    std::vector<monkey> monkeys;
    int cnt = 0;
    std::string testCondStr;
    monkey m;
    while(std::getline(ifs, curLine)) {
        // set up initial state
        if (cnt == 1) {
            m.items = getStartingItems(curLine);
        } else if (cnt == 2) {
            m.mb.op = getOperationOperand(curLine, m.is_multiplied_by_self);
        } else if (cnt == 3) {
            m.mb.test_op = getTestOperand(curLine);
        } else if (cnt == 4) {
            testCondStr = {curLine};
        } else if (cnt == 5) {
            m.mb.pos_op = getMonkeyPositionOperands(testCondStr, curLine);
        } else if (cnt == 6) {
            monkeys.push_back(m);
            m = {};
            cnt = -1;
        }
        cnt++;
    }
    // push last monkey's initial state to the monkey vector
    monkeys.push_back(m);
    
    // process the state 20 times for part 1
    processMonkeyState(monkeys, 20);

    // process the state 10,000 times for part 2
    // processMonkeyState(monkeys, 10000);

    // get the product of the two most
    // active monkeys' item handling count
    std::cout << getItemHandlingCountProduct(monkeys) << "\n";

    ifs.close();
    return 0;
}