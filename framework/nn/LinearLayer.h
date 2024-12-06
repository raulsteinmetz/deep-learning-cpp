#ifndef LINEARLAYER_H
#define LINEARLAYER_H

#include "Module.h"
#include <vector>

/**
 * @class LinearLayer
 * @brief Fully connected layer implementation.
 */
class LinearLayer : public Module {
private:
    size_t input_size;
    size_t output_size;

    std::vector<std::vector<long double>> weights;
    std::vector<long double> biases;
    std::vector<std::vector<long double>> gradients_weights;
    std::vector<long double> gradients_biases;
    std::vector<long double> inputs_cache;

public:
    /**
     * @brief Constructor for LinearLayer.
     * @param input_size Number of input features.
     * @param output_size Number of output features.
     */
    LinearLayer(size_t input_size, size_t output_size);

    /**
     * @brief Performs the forward pass.
     * @param inputs The input tensor.
     * @return The output tensor.
     */
    std::vector<long double> forward(const std::vector<long double>& inputs) override;

    /**
     * @brief Performs the backward pass.
     * @param gradients The gradient of the loss with respect to the output.
     * @return The gradient of the loss with respect to the input.
     */
    std::vector<long double> backward(const std::vector<long double>& gradients) override;

    /**
     * @brief Updates the weights and biases using the computed gradients.
     * @param learning_rate The learning rate for gradient descent.
     */
    void update_parameters(long double learning_rate) override;
};

#endif // LINEARLAYER_H
