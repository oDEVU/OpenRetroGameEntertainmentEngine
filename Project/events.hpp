 
#pragma once

#include "../Engine/engine.hpp"

#include "player.hpp"

#include <iostream>

double count = 0;

void EventTick() {
    //std::cout << "test\n";
    double dt = 1/render.getFps();
    handle_player_input(dt);

    count += dt;

    if(count > 1){
        //std::string text = "player pos : " + std::to_string(render.cam.x) + "," + std::to_string(render.cam.y) + "," + std::to_string(render.cam.z) + " ";
        //render.printToScreen(text);
        count = 0;
    }
}

void BeginGame() {

}

void EndGame() {

}