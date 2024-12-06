#include "ActivationLayer.h"

ActivationLayer::ActivationLayer(
    std::function<std::vector<long double>(const std::vector<long double>&)> func,
    std::function<std::vector<long double>(const std::vector<long double>&)> derivative)
    : activation_func(std::move(func)), activation_derivative(std::move(derivative)) {}

std::vector<long double> ActivationLayer::forward(const std::vector<long double>& inputs) {
    inputs_cache = inputs;
    return activation_func(inputs);
}

std::vector<long double> ActivationLayer::backward(const std::vector<long double>& gradients) {
    auto derivatives = activation_derivative(inputs_cache);
    std::vector<long double> input_gradients(gradients.size());

    for (size_t i = 0; i < gradients.size(); ++i) {
        input_gradients[i] = gradients[i] * derivatives[i];
    }

    return input_gradients;
}
