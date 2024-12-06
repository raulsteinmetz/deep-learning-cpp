#ifndef ACTIVATIONLAYER_H
#define ACTIVATIONLAYER_H

#include "Module.h"
#include <vector>
#include <functional>

/**
 * @class ActivationLayer
 * @brief A module that applies an activation function.
 */
class ActivationLayer : public Module {
private:
    std::function<std::vector<long double>(const std::vector<long double>&)> activation_func;
    std::function<std::vector<long double>(const std::vector<long double>&)> activation_derivative;
    std::vector<long double> inputs_cache;

public:
    /**
     * @brief Constructor for ActivationLayer.
     * @param func The activation function to apply.
     * @param derivative The derivative of the activation function.
     */
    ActivationLayer(
        std::function<std::vector<long double>(const std::vector<long double>&)> func,
        std::function<std::vector<long double>(const std::vector<long double>&)> derivative);

    /**
     * @brief Performs the forward pass.
     * @param inputs The input tensor.
     * @return The output tensor after applying the activation function.
     */
    std::vector<long double> forward(const std::vector<long double>& inputs) override;

    /**
     * @brief Performs the backward pass.
     * @param gradients The gradient of the loss with respect to the output.
     * @return The gradient of the loss with respect to the input.
     */
    std::vector<long double> backward(const std::vector<long double>& gradients) override;

    /**
     * @brief Updates parameters (does nothing for ActivationLayer).
     * @param learning_rate The learning rate for gradient descent.
     */
    void update_parameters(long double learning_rate) override {}
};

#endif // ACTIVATIONLAYER_H
