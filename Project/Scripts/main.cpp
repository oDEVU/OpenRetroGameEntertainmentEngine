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

    std::string path = orgee::getExecutablePath().substr(0, orgee::getExecutablePath().find_last_of("\\/")+1);

    orgee::Window window("OpenRetroGameEntertainmentEngine - test project");

    window.setResolution(1280, 720);

    //render.printToScreen("Writed first");         //Un comment to see how printtoscreen function works
    //render.printToScreen("Writed second");

    render.showFps(true);

    orgee::Map level;

    level = orgee::loadMapFromFile("GameAssets/maps/level.omap" );

    //orgee::SaveMapToFile(level, "level_backup.map");       // function to save level file

    render.LoadMap(level);

    std::thread tick(start_event_tick);

    render.renderGame(&window);        

    EndGame();
    
    consoleLog("Program closed succesfully. ",0);

    return 0;
}
