#include "network.h"
#include <iostream>

Network::Network(std::vector<int> s)
{
    sizes = s;
    for (int i = 0; i < sizes.size() - 1; i++)
    {
        Layer l = Layer(sizes[i+1], sizes[i]);
        l.add_unit();
        layers.push_back(l);
    }
}

Network::Network(Network *n)
{
    layers = n->layers;
}

void Network::mutate()
{
    int layerIdx = rand() % layers.size();
    layers[layerIdx].mutate();
}

Eigen::MatrixXd Network::execute(Eigen::MatrixXd data)
{
    Eigen::MatrixXd d = data;

    for (int i = 0; i < layers.size(); i++)
    {
        d = layers[i].apply(d);
    }
    return d;
}
