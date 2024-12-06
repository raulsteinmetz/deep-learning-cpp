#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include "Module.h"
#include <vector>
#include <memory>

/**
 * @class Sequential
 * @brief A composite module that contains a sequence of other modules.
 */
class Sequential : public Module {
private:
    std::vector<std::shared_ptr<Module>> modules;

public:
    /**
     * @brief Adds a module to the sequence.
     * @param module A shared pointer to the module to add.
     */
    void add_module(const std::shared_ptr<Module>& module);

    /**
     * @brief Performs the forward pass through all modules in sequence.
     * @param inputs The input tensor.
     * @return The output tensor after passing through all modules.
     */
    std::vector<long double> forward(const std::vector<long double>& inputs) override;

    /**
     * @brief Performs the backward pass through all modules in reverse sequence.
     * @param gradients The gradient of the loss with respect to the output.
     * @return The gradient of the loss with respect to the input.
     */
    std::vector<long double> backward(const std::vector<long double>& gradients) override;

    /**
     * @brief Updates the parameters of all modules in the sequence.
     * @param learning_rate The learning rate for gradient descent.
     */
    void update_parameters(long double learning_rate) override;
};

#endif // SEQUENTIAL_H
