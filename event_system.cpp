#include "event_system.h"

ListenerID nextListenerID = 0;

ListenerID EventDispatcher::addListener(int eventType, EventListener listener) {
    listeners[eventType].emplace_back(nextListenerID, listener);
    return nextListenerID++;
}

void EventDispatcher::removeListener(int eventType, ListenerID id) {
    auto& listenersForEvent = listeners[eventType];
    listenersForEvent.erase(
        std::remove_if(listenersForEvent.begin(), 
                       listenersForEvent.end(),
                       [id](const EventListenerPair& pair) { return pair.first == id; }),
        listenersForEvent.end()
    );
}

void EventDispatcher::queueEvent(const Event& e) {
    eventQueue.push(e.clone());  // Without cloning the event, the event would be destroyed when it goes out of scope
}


void EventDispatcher::processEvents() {
    while (!eventQueue.empty()) {
        std::shared_ptr<Event> e = eventQueue.front();
        eventQueue.pop();
        int eventType = e->getType();
        for (const auto& pair : listeners[eventType]) {
            pair.second(*e); // Call the listener
        }
    }
}

void EventDispatcher::processEventsOfType(int eventType) {
    std::queue<std::shared_ptr<Event>> remainingEvents;

    while (!eventQueue.empty()) {
        std::shared_ptr<Event> e = eventQueue.front();
        eventQueue.pop();

        if (e->getType() == eventType) {
            for (const auto& pair : listeners[eventType]) {
                pair.second(*e);
            }
        } else {
            remainingEvents.push(e);
        }
    }

    // Swap the queues to retain unprocessed events
    eventQueue.swap(remainingEvents);
}

