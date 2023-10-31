#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include "event_system.h"

struct PlayerInputEvent : public Event {
    enum class Action {
        MOVE,
        JUMP,
        ATTACK
    };

    Action action;
    float dx, dy; // Used for Move
    int attackDirection; // Used for Attack

    PlayerInputEvent(Action action = Action::MOVE, float dx = 0, float dy = 0, int attackDirection = 0)
        : Event(EventType<PlayerInputEvent>::getId()), 
        action(action), dx(dx), dy(dy), attackDirection(attackDirection) {}

    
    virtual std::shared_ptr<Event> clone() const override {
        return std::make_shared<PlayerInputEvent>(*this);
    }

};

struct GameStateChangeEvent : public Event {
    enum class State {
        START,
        PAUSE,
        GAMEOVER
    };

    State newState;

    GameStateChangeEvent(State state = State::START) 
        : Event(EventType<GameStateChangeEvent>::getId()), 
          newState(state) {}

    
    virtual std::shared_ptr<Event> clone() const override {
        return std::make_shared<GameStateChangeEvent>(*this);
    }

    
};

struct EntityInteractionEvent : public Event {
    enum class InteractionType {
        COLLISION,
        PICKUP,
        TRIGGER
    };

    InteractionType type;
    int entityId1;
    int entityId2;

    EntityInteractionEvent(InteractionType t = InteractionType::COLLISION, int id1 = -1, int id2 = -1)
        : Event(EventType<EntityInteractionEvent>::getId()), 
        type(t), entityId1(id1), entityId2(id2) {}

    virtual std::shared_ptr<Event> clone() const override {
        return std::make_shared<EntityInteractionEvent>(*this);
    }

    
};

#endif // EVENT_TYPES_H
