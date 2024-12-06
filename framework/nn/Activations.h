#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include <vector>
#include <cmath>
#include <functional>

/**
 * @namespace Activations
 * @brief Namespace containing common activation functions and their derivatives.
 */
namespace Activations {
    std::vector<long double> relu(const std::vector<long double>& inputs);
    std::vector<long double> relu_derivative(const std::vector<long double>& inputs);

    std::vector<long double> sigmoid(const std::vector<long double>& inputs);
    std::vector<long double> sigmoid_derivative(const std::vector<long double>& inputs);

    std::vector<long double> tanh(const std::vector<long double>& inputs);
    std::vector<long double> tanh_derivative(const std::vector<long double>& inputs);
}

#endif // ACTIVATIONS_H
