#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "event_system.h"
#include "event_types.h"
#include "player.h"

TEST_CASE("Event type IDs are unique", "[EventType]") {
    REQUIRE(EventType<PlayerInputEvent>::getId() != EventType<GameStateChangeEvent>::getId());
    REQUIRE(EventType<GameStateChangeEvent>::getId() != EventType<EntityInteractionEvent>::getId());
    REQUIRE(EventType<PlayerInputEvent>::getId() != EventType<EntityInteractionEvent>::getId());
}

TEST_CASE("Events can be queued and processed", "[EventDispatcher]") {
    EventDispatcher dispatcher;

    int callCount = 0;
    dispatcher.addListener(EventType<PlayerInputEvent>::getId(), [&](const Event&) {
        ++callCount;
    });

    PlayerInputEvent event;
    dispatcher.queueEvent(event);
    REQUIRE(callCount == 0);

    dispatcher.processEvents();
    REQUIRE(callCount == 1);
}

TEST_CASE("Listeners can be removed", "[EventDispatcher]") {
    EventDispatcher dispatcher;

    int callCount = 0;
    ListenerID id = dispatcher.addListener(EventType<PlayerInputEvent>::getId(), [&](const Event&) {
        ++callCount;
    });

    PlayerInputEvent event;
    dispatcher.queueEvent(event);
    dispatcher.processEvents();
    REQUIRE(callCount == 1);

    dispatcher.removeListener(EventType<PlayerInputEvent>::getId(), id);
    dispatcher.queueEvent(event);
    dispatcher.processEvents();
    REQUIRE(callCount == 1);
}

TEST_CASE("Player responds to input event", "[Player]") {
    
    EventDispatcher dispatcher;
    Player player(dispatcher);

    REQUIRE(player.getX() == 0);
    REQUIRE(player.getY() == 0);
    REQUIRE(!player.isJumping());
    REQUIRE(player.getAttackDirection() == 0);

    PlayerInputEvent jumpEvent{PlayerInputEvent::Action::JUMP, 0, 0, 0};
    dispatcher.queueEvent(jumpEvent);
    dispatcher.processEvents();
    REQUIRE(player.isJumping());

    PlayerInputEvent moveEvent{PlayerInputEvent::Action::MOVE, 5, 5, 0};
    dispatcher.queueEvent(moveEvent);
    dispatcher.processEvents();

    REQUIRE(player.getX() == 5);
    REQUIRE(player.getY() == 5);

    PlayerInputEvent attackEvent{PlayerInputEvent::Action::ATTACK, 0, 0, 90};
    dispatcher.queueEvent(attackEvent);
    dispatcher.processEvents();

    REQUIRE(player.getAttackDirection() == 90);
}

TEST_CASE("Multiple listeners can respond to the same event", "[EventDispatcher]") {
    EventDispatcher dispatcher;

    int callCount1 = 0;
    int callCount2 = 0;

    dispatcher.addListener(EventType<PlayerInputEvent>::getId(), [&](const Event&) {
        ++callCount1;
    });
    dispatcher.addListener(EventType<PlayerInputEvent>::getId(), [&](const Event&) {
        ++callCount2;
    });

    PlayerInputEvent event;
    dispatcher.queueEvent(event);
    dispatcher.processEvents();

    REQUIRE(callCount1 == 1);
    REQUIRE(callCount2 == 1);
}

TEST_CASE("EventDispatcher processes only specific type of events", "[EventDispatcher]") {
    EventDispatcher dispatcher;

    // A flag to track if our event listener was called
    bool playerInputEventCalled = false;
    bool gameStateChangeEventCalled = false;

    dispatcher.addListener(EventType<PlayerInputEvent>::getId(), 
                           [&playerInputEventCalled](const Event& e) {
                               playerInputEventCalled = true;
                           });

    dispatcher.addListener(EventType<GameStateChangeEvent>::getId(),
                           [&gameStateChangeEventCalled](const Event& e) {
                               gameStateChangeEventCalled = true;
                           });

    PlayerInputEvent playerInputEvent;
    GameStateChangeEvent gameStateChangeEvent;

    dispatcher.queueEvent(playerInputEvent);
    dispatcher.queueEvent(gameStateChangeEvent);

    // Process only PlayerInputEvent
    dispatcher.processEventsOfType(EventType<PlayerInputEvent>::getId());

    REQUIRE(playerInputEventCalled == true);
    REQUIRE(gameStateChangeEventCalled == false);

    // Let's process all events to ensure the GameStateChangeEvent is still in the queue
    dispatcher.processEvents();

    REQUIRE(gameStateChangeEventCalled == true);
}



   
