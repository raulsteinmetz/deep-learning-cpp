#include "LossPublisher.h"

void LossPublisher::publish_loss(double loss, size_t epoch) {
    epoch_losses.emplace_back(loss, epoch);
    event_manager.notify("loss_updated", loss, epoch);
}

const std::vector<std::pair<double, size_t>>& LossPublisher::get_losses() const {
    return epoch_losses;
}

EventManager& LossPublisher::get_event_manager() {
    return event_manager;
}