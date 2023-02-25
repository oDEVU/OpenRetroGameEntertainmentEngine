 
#pragma once

#include "../../Engine/engine.hpp"

#include "player.hpp"

#include <iostream>

double count = 0;

sf::Clock deltaClock;

void EventTick() {
    //std::cout << "test\n";

    sf::Time dt = deltaClock.restart();
    handle_player_input(dt.asSeconds());
}

void BeginGame() {

}

void EndGame() {

}