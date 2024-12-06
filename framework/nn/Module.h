#ifndef MODULE_H
#define MODULE_H

#include <vector>

/**
 * @class Module
 * @brief Abstract base class for all neural network components.
 */
class Module {
public:
    virtual ~Module() = default;

    /**
     * @brief Forward pass for the module.
     * @param inputs The input tensor.
     * @return The output tensor.
     */
    virtual std::vector<long double> forward(const std::vector<long double>& inputs) = 0;

    /**
     * @brief Backward pass for the module.
     * @param gradients The gradient of the loss with respect to the output.
     * @return The gradient of the loss with respect to the input.
     */
    virtual std::vector<long double> backward(const std::vector<long double>& gradients) = 0;

    /**
     * @brief Updates the module's parameters using gradients.
     * @param learning_rate The learning rate for gradient descent.
     */
    virtual void update_parameters(long double learning_rate) = 0;
};

#endif // MODULE_H
