#include "EventManager.h"

void EventManager::subscribe(const std::string& event_type, const std::function<void(double, size_t)>& listener) {
    listeners[event_type].push_back(listener);
}

void EventManager::unsubscribe(const std::string& event_type) {
    if (listeners.find(event_type) != listeners.end()) {
        listeners[event_type].clear();
    }
}

void EventManager::notify(const std::string& event_type, double loss, size_t epoch) {
    if (listeners.find(event_type) != listeners.end()) {
        for (const auto& listener : listeners[event_type]) {
            listener(loss, epoch);
        }
    }
}