#include "Activations.h"
#include <algorithm>

std::vector<long double> Activations::relu(const std::vector<long double>& inputs) {
    std::vector<long double> outputs(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        outputs[i] = std::max(0.0L, inputs[i]);
    }
    return outputs;
}

std::vector<long double> Activations::relu_derivative(const std::vector<long double>& inputs) {
    std::vector<long double> outputs(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        outputs[i] = (inputs[i] > 0.0L) ? 1.0L : 0.0L;
    }
    return outputs;
}

std::vector<long double> Activations::sigmoid(const std::vector<long double>& inputs) {
    std::vector<long double> outputs(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        outputs[i] = 1.0L / (1.0L + std::exp(-inputs[i]));
    }
    return outputs;
}

std::vector<long double> Activations::sigmoid_derivative(const std::vector<long double>& inputs) {
    auto sig = sigmoid(inputs);
    std::vector<long double> outputs(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        outputs[i] = sig[i] * (1.0L - sig[i]);
    }
    return outputs;
}

std::vector<long double> Activations::tanh(const std::vector<long double>& inputs) {
    std::vector<long double> outputs(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        outputs[i] = std::tanh(inputs[i]);
    }
    return outputs;
}

std::vector<long double> Activations::tanh_derivative(const std::vector<long double>& inputs) {
    auto tanh_vals = tanh(inputs);
    std::vector<long double> outputs(inputs.size());
    for (size_t i = 0; i < inputs.size(); ++i) {
        outputs[i] = 1.0L - tanh_vals[i] * tanh_vals[i];
    }
    return outputs;
}
