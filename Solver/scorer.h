#ifndef SCORER_H
#define SCORER_H

#include "../Network/network.h"

class Scorer
{
public:
    Scorer();
    virtual double score(Network* n) = 0;
};

#endif // SCORER_H
