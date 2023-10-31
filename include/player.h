#ifndef PLAYER_H
#define PLAYER_H

#include "event_system.h"
#include "event_types.h"
#include <vector>

class Player {
public:
    Player(EventDispatcher& dispatcher);
    ~Player();

    float getX() const;
    float getY() const;
    bool isJumping() const;
    int getAttackDirection() const;

private:
    float x, y;
    bool isJumpingFlag;
    int attackDirection;
    
    EventDispatcher& dispatcher;
    std::vector<std::pair<int, ListenerID>> listeners;

    void onPlayerInput(const PlayerInputEvent& event);
    void onGameStateChange(const GameStateChangeEvent& event);
    void onEntityInteraction(const EntityInteractionEvent& event);
};

#endif // PLAYER_H
