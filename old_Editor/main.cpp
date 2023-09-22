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

#include "../Engine/engine.hpp"

int main() {

    std::string path = orgee::getExecutablePath().substr(0, orgee::getExecutablePath().find_last_of("\\/")+1);

    orgee::Window window("OpenRetroGameEntertainmentEngine - Project Creator");

    window.setResolution(1280, 720);

    //render.printToScreen("Writed first");         //Un comment to see how printtoscreen function works
    //render.printToScreen("Writed second");

    orgee::Map layout;

    layout = orgee::loadMapFromFile("Data/layout/test.omap" );

    render.LoadMap(layout);

    render.showFps(false);
    render.osd = false;

    render.renderGame(&window);

    return 0;
}
