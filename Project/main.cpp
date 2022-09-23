#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <thread>

#include "events.hpp"

#include "../Engine/engine.hpp"

void start_event_tick(){
    while(true){
        EventTick();
    }
}

int main() {
    std::thread begin(BeginGame);

    orgy::Window window("OpenRetroGameYngine - test project");

    window.setResolution(1280, 720);

    render.printToScreen("Writed first");
    render.printToScreen("Writed second");

    render.showFps(true);

    orgy::Map level;

    level = orgy::loadMapFromFile("level.map");

    orgy::SaveMapToFile(level, "lvl_coruption_tester.map");

    render.LoadMap(level);

    std::thread tick(start_event_tick);

    render.renderGame(window.getWindow());        

    EndGame();
    
    std::cout << "Program closed succesfully.\n";

    return 0;
}
