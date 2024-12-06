#ifndef LOSS_FUNCTION_H
#define LOSS_FUNCTION_H

#include <vector>

/**
 * @class LossFunction
 * @brief Abstract interface for loss functions.
 */
class LossFunction {
public:
    virtual ~LossFunction() = default;

    /**
     * @brief Computes the loss given predictions and targets.
     * @param predictions The predicted values.
     * @param targets The ground truth values.
     * @return The computed loss value.
     */
    virtual long double compute_loss(const std::vector<long double>& predictions, const std::vector<long double>& targets) const = 0;
};

#endif // LOSS_FUNCTION_H
