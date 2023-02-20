 
#pragma once

#include "../../Engine/engine.hpp"

#include "player.hpp"

#include <iostream>

double count = 0;

void EventTick() {
    //std::cout << "test\n";
    handle_player_input(0.001);
}

void BeginGame() {

}

void EndGame() {

}