#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <functional>
#include <map>
#include <vector>
#include <queue>
#include <memory>

class Event {
public:
    virtual ~Event() = default;

    int getType() const { return type; }
    virtual std::shared_ptr<Event> clone() const = 0;
    
protected:
    Event(int eventType) : type(eventType) {}

private:
    int type;

};


using EventListener = std::function<void(const Event&)>;
using ListenerID = std::size_t;
using EventListenerPair = std::pair<ListenerID, EventListener>; // Listeners have id for ease of removal 


class EventDispatcher {
public:
    ListenerID addListener(int eventType, EventListener listener);
    void removeListener(int eventType, ListenerID id);
    void queueEvent(const Event& e);
    void processEvents();
    void processEventsOfType(int eventType);

private:
    std::map<int, std::vector<EventListenerPair> > listeners; // There is a separate vector of listeners for each event type
    std::queue<std::shared_ptr<Event>> eventQueue;

};


class EventTypeGenerator {
public:
    static int getNextId() {
        static int nextID = 0;
        return nextID++;
    }
};

template <typename T>
class EventType {
public:
    static int getId() {
        static int id = EventTypeGenerator::getNextId();
        return id;
    }
};


#endif // EVENT_SYSTEM_H


