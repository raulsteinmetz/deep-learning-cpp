#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <utility>

/**
 * @class EventManager
 * @brief Base class for managing event subscriptions and notifications.
 */
class EventManager {
private:
    std::unordered_map<std::string, std::vector<std::function<void(double, size_t)>>> listeners;

public:
    /**
     * @brief Subscribes a listener to a specific event type.
     * @param event_type The event type to subscribe to.
     * @param listener The listener callback to add.
     */
    void subscribe(const std::string& event_type, const std::function<void(double, size_t)>& listener);

    /**
     * @brief Unsubscribes all listeners from a specific event type.
     * @param event_type The event type to unsubscribe from.
     */
    void unsubscribe(const std::string& event_type);

    /**
     * @brief Notifies all listeners of a specific event type with the provided data.
     * @param event_type The event type to notify.
     * @param loss The loss value to pass to the listeners.
     * @param epoch The epoch value to pass to the listeners.
     */
    void notify(const std::string& event_type, double loss, size_t epoch);
};

#endif // EVENTMANAGER_H