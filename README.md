# Event System for a 2D Game Engine in C++11

A basic data-oriented event system. The focus is on making the addition of new event types and listeners as simple as possible. The dipatcher has functionality for processing the events of only a particular type. 

## Overview

- **Event**: Represents a specific occurrence or change in state that might be of interest. There are some built-in types of events and new ones can be added.
  
- **EventListener**: A callback function that responds to specific Events.

- **EventDispatcher**: Manages event-listeners relationships and dispatches events to the relevant listeners.

- **EventType**: Allows for generating unique IDs for each type of Event.

## Event Class

All events should inherit from the base `Event` class. It ensures that each event can provide its type and can be cloned.

### Key Functions

- `getType()`: Returns the type ID of the event.
  
- `clone()`: Creates a new instance of the event, enabling safe copying.

## Event Dispatcher

The Event Dispatcher is responsible for managing listeners and dispatching events to them.

### Key Functions

- `addListener(int eventType, EventListener listener)`: Registers a listener to a specific event type and returns an ID for the listener.

- `removeListener(int eventType, ListenerID id)`: Unregisters a listener based on its type and ID.

- `queueEvent(const Event& e)`: Adds an event to the queue for future processing.

- `processEvents()`: Processes all events in the queue, calling the associated listeners.

- `processEventsOfType(int eventType)`: Processes all events in the queue that are of a prticular type.

## Event Types

For a new event to be recognized by the system, it should inherit from `Event` and implement the `clone` method.

### Examples

1. **PlayerInputEvent**: Represents player-related actions like movement, jump, or attack.
  
2. **GameStateChangeEvent**: Reflects changes in game states like start, pause, or game over.
  
3. **EntityInteractionEvent**: Represents interactions between different game entities, e.g., collision or pickup.

## Player Class

This class demonstrates the practical application of the Event System, as a player responds to various events.

### Key Functions

- `onPlayerInput(const PlayerInputEvent& event)`: Handles player input events.

- `onGameStateChange(const GameStateChangeEvent& event)`: Handles changes in the game state.

- `onEntityInteraction(const EntityInteractionEvent& event)`: Manages interactions between game entities.

## Steps to Add a New Event Type

1. Create a new struct/class inheriting from the `Event` class.

2. Implement the `clone` method as in the example:
```cpp
class YourEvent : public Event {
public:
    // ...
    virtual std::shared_ptr<Event> clone() const override {
        return std::make_shared<YourEvent>(*this);
    }
};
```

3. Define any data members or behaviors specific to your new event.

4. Register listeners for this new event in the relevant parts of your codebase using the `EventDispatcher::addListener` method.

## Steps to Register and Unregister Listeners

1. **Register**: Use `EventDispatcher::addListener` specifying the event type and the callback.
  
```cpp
   dispatcher.addListener(EventType<YourEvent>::getId(), [this](const Event& e) {
       // Handle event here
   });
```


2. **Unregister**: Use `EventDispatcher::removeListener`, providing the event type and listener ID.

```cpp
dispatcher.removeListener(EventType<YourEvent>::getId(), listenerId);
```

## Credits

This Event System was refined and documented with the help of ChatGPT, a language model by OpenAI.


