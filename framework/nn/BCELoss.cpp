#include "BCELoss.h"
#include <stdexcept>
#include <cmath>

long double BinaryCrossEntropyLoss::compute_loss(
    const std::vector<long double>& predictions,
    const std::vector<long double>& targets
) const {
    if (predictions.size() != targets.size()) {
        throw std::invalid_argument("Predictions and targets must have the same size.");
    }

    long double loss = 0.0;
    for (size_t i = 0; i < predictions.size(); ++i) {
        long double p = std::max(std::min(predictions[i], 1.0L - 1e-15L), 1e-15L);
        long double t = targets[i];
        loss += -(t * std::log(p) + (1.0L - t) * std::log(1.0L - p));
    }
    return loss / predictions.size();
}
