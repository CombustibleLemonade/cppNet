#ifndef RANDOMSOLVER_H
#define RANDOMSOLVER_H

#include "solver.h"
#include "scorer.h"

class RandomSolver : public Solver
{
    std::vector<Network*> nets;

public:
    int generationSize = 150;
    double maxScore = 100;
    int maxIterations = 150;
    int survivorCount = 5;

    Scorer* scorer;

    RandomSolver(Network* n, Scorer* s);
    Network* solve();
};

#endif // RANDOMSOLVER_H
