#ifndef SOLVER_H
#define SOLVER_H

#include "scorer.h"

class Solver
{
protected:
    Network* original;
public:
    Solver(Network* n);
    virtual Network* solve() = 0;
};

#endif // SOLVER_H
