#include <iostream>

#include "Solver/randomsolver.h"
#include <eigen3/Eigen/Core>

using namespace std;

class RScorer : public Scorer
{
public:
    double score(Network *n)
    {
        Eigen::Vector2d v(1, 2);
        Eigen::MatrixXd m = n->execute(v.transpose());

        double x = tan(m(0, 0)) - 1;
        return -abs(pow(x, 5) - x + 1);
    }
};

int main()
{
    srand (time(NULL));

    Network n = Network({2, 3, 4});
    RScorer s = RScorer();

    RandomSolver solv = RandomSolver(&n, &s);
    Network* solution = solv.solve();

    Eigen::Vector2d v(1, 2);
    Eigen::MatrixXd m = solution->execute(v.transpose());

    std::cout << tan(m(0, 0)) << std::endl;
}
