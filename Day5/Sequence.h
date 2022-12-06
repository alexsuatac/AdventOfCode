#pragma once

#include <stack>
#include <vector>

class Sequence {
public:
    Sequence () = default;
    ~Sequence() = default;
    
    Sequence& move(unsigned moveCmd);
    Sequence& to(unsigned toCmd);
    Sequence& from(unsigned fromCmd);

    std::vector<unsigned> seq;
};