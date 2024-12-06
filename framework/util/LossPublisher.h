#ifndef LOSSPUBLISHER_H
#define LOSSPUBLISHER_H

#include <vector>
#include "EventManager.h"

/**
 * @class LossPublisher
 * @brief Publisher for tracking and notifying about loss updates.
 */
class LossPublisher {
private:
    EventManager event_manager;
    std::vector<std::pair<double, size_t>> epoch_losses;

public:
    /**
     * @brief Adds a new loss value and notifies subscribers.
     * @param loss The loss value to add.
     * @param epoch The epoch number associated with the loss.
     */
    void publish_loss(double loss, size_t epoch);

    /**
     * @brief Gets all the recorded loss values.
     * @return A const reference to the vector of loss values and epochs.
     */
    const std::vector<std::pair<double, size_t>>& get_losses() const;

    /**
     * @brief Gets the event manager for managing subscriptions.
     * @return Reference to the event manager.
     */
    EventManager& get_event_manager();
};

#endif // LOSSPUBLISHER_H
