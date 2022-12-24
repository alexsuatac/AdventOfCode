#include <algorithm>
#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

// encapsulate monkey behaviour
struct monkey {
    int cnt = 1;
    std::queue<int> items;
    int operation_result;
    bool test_result;
    size_t monkey_pos;
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

int doOperation(const std::string& operationStr, int item) {
    int operand;
    if (std::isdigit(operationStr[25])) {
        std::string numStr({operationStr.begin()+25, operationStr.end()}); 
        operand = std::stoi(numStr);
    } else {
        operand = item;
    }

    std::string op ({operationStr[23]});
    if(op == "+") {
        return (item + operand) / 3;
    }
    
    return (item * operand) / 3;
}

bool doTest(const std::string& testStr, int item) {
    std::string testVal({testStr.begin()+21, testStr.end()});
    int val = std::stoi(testVal);
    return (item % val) == 0;
}

size_t getMonkeyPosition(const std::string& m1, const std::string& m2, bool cond) {
    std::string monkey1({m1.begin()+29, m1.end()});
    std::string monkey2({m2.begin()+30, m2.end()});

    if(cond) {
        return static_cast<size_t> (std::stoi(monkey1));
    }

    return static_cast<size_t> (std::stoi(monkey2));
}

void processMonkeyState(std::vector<monkey>& monkeys, const int N = 20) {
    for(size_t i = 0; i < N; ++i) {
        // increase count and move items from one monkey to the other
        for(auto & monkey : monkeys) {
            monkey.cnt++;
            monkeys[monkey.monkey_pos].items.push(monkey.items.front());
            monkey.items.pop(); 
        }

        // process the next state
        for(auto & monkey : monkeys) {
            tmp.operation_result = doOperation(curLine, tmp.items.front());
            tmp.items.pop();
            tmp.test_result = doTest(curLine, tmp.operation_result);
            tmp.monkey_pos = getMonkeyPosition(testCondStr, curLine, tmp.test_result);
        } 

    }

}

int main() {
    std::ifstream ifs;

    // requires input.txt to be in same directory
    // that is application is being run from
    ifs.open("./test.txt", std::ifstream::in);

    // getStartingItems("Starting items: 54, 65, 75, 74");
    // doOperation("Operation: new = old + 223", 2);
    // testConditionTrue("Test: divisible by 13", 2);
    // getMonkeyPosition("If true: throw to monkey 11", "If false: throw to monkey 323", false);
    std::string curLine;
    std::vector<monkey> monkeys;
    int cnt = 0;
    std::string testCondStr;
    monkey tmp;
    while(std::getline(ifs, curLine)) {
        // set up initial state
        if (cnt == 1) {
            tmp.items = getStartingItems(curLine);
        } else if (cnt == 2) {
            tmp.operation_result = doOperation(curLine, tmp.items.front());
            tmp.items.pop();
        } else if (cnt == 3) {
            tmp.test_result = doTest(curLine, tmp.operation_result);
        } else if (cnt == 4) {
            testCondStr = {curLine};
        } else if (cnt == 5) {
            tmp.monkey_pos = getMonkeyPosition(testCondStr, curLine, tmp.test_result);
        } else if (cnt == 6) {
            monkeys.push_back(tmp);
            tmp = {};
            cnt = -1;
        }
        cnt++;
    }
    // push last monkey's initial state to the monkey vector
    monkeys.push_back(tmp);
    
    // process the state N times


    ifs.close();
    return 0;
}