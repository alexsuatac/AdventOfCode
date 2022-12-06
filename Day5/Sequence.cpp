#include "Sequence.h"

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