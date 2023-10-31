#include "player.h"


Player::Player(EventDispatcher& dispatcher) 
    : x(0), y(0), isJumpingFlag(false), attackDirection(0), dispatcher(dispatcher) 
{

    listeners.push_back({EventType<PlayerInputEvent>::getId(),
        dispatcher.addListener(EventType<PlayerInputEvent>::getId(),
            [this](const Event& e) {
                onPlayerInput(static_cast<const PlayerInputEvent&>(e));
            }
        )
    });

    listeners.push_back({EventType<GameStateChangeEvent>::getId(),
        dispatcher.addListener(EventType<GameStateChangeEvent>::getId(),
            [this](const Event& e) {
                onGameStateChange(static_cast<const GameStateChangeEvent&>(e));
            }
        )
    });

    listeners.push_back({EventType<EntityInteractionEvent>::getId(),
        dispatcher.addListener(EventType<EntityInteractionEvent>::getId(),
            [this](const Event& e) {
                onEntityInteraction(static_cast<const EntityInteractionEvent&>(e));
            }
        )
    });
    

}

Player::~Player() {
    for (const auto& pair : listeners) {
        dispatcher.removeListener(pair.first, pair.second);
    }
}


void Player::onPlayerInput(const PlayerInputEvent& inputEvent) {

    switch (inputEvent.action) {
    case PlayerInputEvent::Action::MOVE:

        x += inputEvent.dx;
        y += inputEvent.dy;
        break;

    case PlayerInputEvent::Action::JUMP:
        isJumpingFlag = true; 
        break;

    case PlayerInputEvent::Action::ATTACK:
        attackDirection = inputEvent.attackDirection;
        break;
    }
}


void Player::onGameStateChange(const GameStateChangeEvent& event) {
    // Handle game state changes (if required by the player)
}

void Player::onEntityInteraction(const EntityInteractionEvent& event) {
    // Handle entity interactions (if required by the player)
}

float Player::getX() const {
    return x;
}

float Player::getY() const {
    return y;
}

bool Player::isJumping() const {
    return isJumpingFlag;
}

int Player::getAttackDirection() const {
    return attackDirection;
}
