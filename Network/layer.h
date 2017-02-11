#ifndef LAYER_H
#define LAYER_H
#include <eigen3/Eigen/Core>

class Layer
{
    Eigen::MatrixXd m;
public:
    Layer(int x, int y);
    void add_unit();
    void mutate();
    Eigen::MatrixXd apply(Eigen::MatrixXd on);
};

#endif // LAYER_H
