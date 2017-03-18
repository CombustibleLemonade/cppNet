#include <iostream>

#include "mnist/include/mnist/mnist_reader.hpp"
#include "mnist/include/mnist/mnist_utils.hpp"

#include "Solver/randomsolver.h"
#include <eigen3/Eigen/Core>

using namespace std;

auto dataset = mnist::read_dataset();


class RScorer : public Scorer
{
    int generation = 0;
public:
    std::vector< std::vector<double> > images;
    std::vector< int > labels;
    int test_size = 100;
    static double max_value;

    void nextGen()
    {
        images.clear();
        labels.clear();

        for (int i = 0; i < test_size; i++)
        {
            int idx = rand() % dataset.test_labels.size();
            labels.push_back(dataset.test_labels[idx]);

            std::vector<unsigned char> imageChar = dataset.test_images[idx];
            std::vector<double> image = std::vector<double>();

            for (int j = 0; j < 784; j++)
            {
                image.push_back(double(imageChar[j]) * (1.0/256.0));
            }

            images.push_back(image);
        }

        std::cout << "Generation " << generation++ << " with max value " << max_value << std::endl;
        max_value = 0.0;
    }

    double score(Network *n)
    {
        double value = 0.0;

        for (int i = 0; i < test_size; i++)
        {
            Eigen::Matrix<double, 1, 784> img( images[i].data() );
            auto v = n->execute(img);
            vector<double> stdv(v.data(), v.data() + v.rows() * v.cols());

            int dist = std::distance(stdv.begin(), std::max_element(stdv.begin(), stdv.end()));
            if (dist == labels[i])
            {
                value += 0.1;
            }
        }

        if (max_value < value) max_value = value;

        return value;
    }
};

double RScorer::max_value = 0;

int main()
{
    srand (time(NULL));

    Network n = Network({784, 10});
    RScorer s = RScorer();

    Eigen::MatrixXd m = Eigen::MatrixXd(1, 10);

    RandomSolver solv = RandomSolver(&n, &s);
    Network* solution = solv.solve();

    auto dataset = mnist::read_dataset(20, 20);
    mnist::binarize_dataset(dataset);
}
