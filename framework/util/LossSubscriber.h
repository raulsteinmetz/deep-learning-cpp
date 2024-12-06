#ifndef LOSSSUBSCRIBER_H
#define LOSSSUBSCRIBER_H

#include <string>

/**
 * @class LossSubscriber
 * @brief Subscriber interface for receiving loss updates.
 */
class LossSubscriber {
public:
    virtual ~LossSubscriber() = default;

    /**
     * @brief Updates the subscriber with a new loss value.
     * @param loss The updated loss value.
     */
    virtual void update(double loss, size_t epoch) = 0;
};

#endif // LOSSSUBSCRIBER_H
