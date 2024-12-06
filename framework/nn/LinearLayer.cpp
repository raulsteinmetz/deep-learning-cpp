#include "LinearLayer.h"
#include <stdexcept>
#include <numeric>
#include <ctime>
#include <random>

LinearLayer::LinearLayer(size_t input_size, size_t output_size)
    : input_size(input_size), output_size(output_size) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::normal_distribution<long double> he_dist(0.0L, std::sqrt(2.0L / input_size));

    weights.resize(output_size, std::vector<long double>(input_size));
    biases.resize(output_size);
    gradients_weights.resize(output_size, std::vector<long double>(input_size, 0.0L));
    gradients_biases.resize(output_size, 0.0L);

    for (auto& row : weights) {
        for (auto& weight : row) {
            weight = he_dist(generator);
        }
    }

    for (auto& bias : biases) {
        bias = 0.0L;
    }
}


std::vector<long double> LinearLayer::forward(const std::vector<long double>& inputs) {
    if (inputs.size() != input_size) {
        throw std::invalid_argument("Input size does not match the layer's input size.");
    }

    inputs_cache = inputs;
    std::vector<long double> outputs(output_size, 0.0L);

    for (size_t i = 0; i < output_size; ++i) {
        outputs[i] = std::inner_product(inputs.begin(), inputs.end(), weights[i].begin(), biases[i]);
    }

    return outputs;
}

std::vector<long double> LinearLayer::backward(const std::vector<long double>& gradients) {
    std::vector<long double> input_gradients(input_size, 0.0L);

    for (size_t i = 0; i < output_size; ++i) {
        for (size_t j = 0; j < input_size; ++j) {
            input_gradients[j] += gradients[i] * weights[i][j];
            gradients_weights[i][j] += gradients[i] * inputs_cache[j];
        }
        gradients_biases[i] += gradients[i];
    }

    return input_gradients;
}

void LinearLayer::update_parameters(long double learning_rate) {
    for (size_t i = 0; i < output_size; ++i) {
        for (size_t j = 0; j < input_size; ++j) {
            weights[i][j] -= learning_rate * gradients_weights[i][j];
            gradients_weights[i][j] = 0.0L;
        }
        biases[i] -= learning_rate * gradients_biases[i];
        gradients_biases[i] = 0.0L;
    }
}
