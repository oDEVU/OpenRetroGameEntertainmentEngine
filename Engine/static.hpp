#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>

namespace orgy
{
    struct wall
    {
        double sx = 0;
        double sy = 0;
        double ex = 0;
        double ey = 0;

        bool mat = true;

        int r = 255;
        int g = 255;
        int b = 255;
        std::string texture_path = "EngineAssets/textures/empty.png";
    };
        
    struct static_object
    {
        double floor = 0;
        double celing = 0;
        double distance = 0;
        bool flip = 0;
        int surface = 0;
        int surf[32000];
        std::vector<wall> walls;
    };
    
} // namespace orgy
