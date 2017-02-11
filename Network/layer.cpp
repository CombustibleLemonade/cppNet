#include "layer.h"
#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(-0.1, 0.1);

Layer::Layer(int x, int y)
{
    m = Eigen::MatrixXd(x, y);
}

void Layer::add_unit()
{
    Eigen::MatrixXd s = Eigen::MatrixXd::Identity(m.cols(), m.rows());
    m += s;
}

void Layer::mutate()
{
    int x = rand() % m.rows();
    int y = rand() % m.cols();
    m(x, y) += distribution(generator);
}

Eigen::MatrixXd Layer::apply(Eigen::MatrixXd on)
{
    // Do matrix multiplication
    Eigen::MatrixXd mult = on * m;

    // Apply sigmoid approximation
    for (int x = 0; x < mult.rows(); x++)
    {
        for (int y = 0; y < mult.cols(); y++)
        {
            mult(x, y) = erf(mult(x, y));
        }
    }

    return mult.array().matrix();
}

