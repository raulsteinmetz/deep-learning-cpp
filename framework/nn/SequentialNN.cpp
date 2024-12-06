#include "SequentialNN.h"

void Sequential::add_module(const std::shared_ptr<Module>& module) {
    modules.push_back(module);
}

std::vector<long double> Sequential::forward(const std::vector<long double>& inputs) {
    std::vector<long double> output = inputs;
    for (const auto& module : modules) {
        output = module->forward(output);
    }
    return output;
}

std::vector<long double> Sequential::backward(const std::vector<long double>& gradients) {
    std::vector<long double> output_gradients = gradients;
    for (auto it = modules.rbegin(); it != modules.rend(); ++it) {
        output_gradients = (*it)->backward(output_gradients);
    }
    return output_gradients;
}

void Sequential::update_parameters(long double learning_rate) {
    for (auto& module : modules) {
        module->update_parameters(learning_rate);
    }
}
