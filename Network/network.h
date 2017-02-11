#ifndef NETWORK_H
#define NETWORK_H

#include "layer.h"
#include <vector>

class Network
{
    std::vector<Layer> layers;
public:
    std::vector<int> sizes;

    Network(std::vector<int> s);
    Network(Network* n);
    void mutate();
    Eigen::MatrixXd execute(Eigen::MatrixXd data);
};

#endif // NETWORK_H
