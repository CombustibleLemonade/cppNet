#include "randomsolver.h"
#include <iostream>

class SolverInfo
{
public:
    Network* network;
    double score;

    SolverInfo(Network* n, Scorer* s)
    {
        network = n;
        score = s->score(n);
    }
};

RandomSolver::RandomSolver(Network* n, Scorer* s) : Solver(n)
{
    scorer = s;
}

bool sortFunction(SolverInfo a, SolverInfo b)
{
    return a.score > b.score;
}

Network* RandomSolver::solve()
{
    std::vector<SolverInfo> infoList;

    // Create initial batch of networks
    for (int i = 0; i < generationSize; i++)
    {
        Network* n = new Network(original);

        for (int m = 0; m < generationSize; m++)
        {
            n->mutate();
        }

        infoList.push_back(SolverInfo(n, scorer));
    }

    for (int g = 0; g < maxIterations; g++)
    {
        std::sort(infoList.begin(), infoList.end(), sortFunction);
        std::vector<SolverInfo> survivors;

        for (int i = 0; i < survivorCount; i++)
        {
            survivors.push_back(infoList[i]);
        }


        infoList.erase(infoList.begin() + survivorCount, infoList.end());
        for (int i = 0; i < generationSize - survivorCount; i++)
        {
            int idx = rand() % survivors.size();
            Network* n = new Network(infoList[idx].network);

            for (int m = 0; m < 200; m++)
            {
                n->mutate();
            }

            infoList.push_back(SolverInfo(n, scorer));
        }
    }

    return infoList[0].network;
}

