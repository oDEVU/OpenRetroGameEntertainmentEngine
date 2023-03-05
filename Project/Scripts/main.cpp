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
#include <filesystem>

#include "events.hpp"

#include "../../Engine/engine.hpp"

void start_event_tick(){
    while(true){
        EventTick();
    }
}

int main() {
    std::thread begin(BeginGame);

    std::string path = orgy::getExecutablePath().substr(0, orgy::getExecutablePath().find_last_of("\\/")+1);

    orgy::Window window("OpenRetroGameYngine - test project");

    window.setResolution(1280, 720);

    //render.printToScreen("Writed first");         //Un comment to see how printtoscreen function works
    //render.printToScreen("Writed second");

    render.showFps(true);

    orgy::Map level;

    level = orgy::loadMapFromFile("GameAssets/maps/level.omap" );

    //orgy::SaveMapToFile(level, "level_backup.map");       // function to save level file

    render.LoadMap(level);

    std::thread tick(start_event_tick);

    render.renderGame(window.getWindow());        

    EndGame();
    
    consoleLog("Program closed succesfully. ",0);

    return 0;
}
