#ifndef BINARY_CROSS_ENTROPY_LOSS_H
#define BINARY_CROSS_ENTROPY_LOSS_H

#include "LossFunction.h"
#include <vector>
#include <cmath>

/**
 * @class BinaryCrossEntropyLoss
 * @brief Implementation of the Binary Cross-Entropy loss function.
 */
class BinaryCrossEntropyLoss : public LossFunction {
public:
    /**
     * @brief Computes the Binary Cross-Entropy loss for predictions and targets.
     * @param predictions The predicted probabilities (0 <= p <= 1).
     * @param targets The ground truth binary labels (0 or 1).
     * @return The computed loss value.
     */
    long double compute_loss(const std::vector<long double>& predictions, const std::vector<long double>& targets) const override;
};

#endif // BINARY_CROSS_ENTROPY_LOSS_H
