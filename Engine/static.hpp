#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>

namespace orgy
{
    struct material
    {
        bool txt = 0;
        std::string txt_path = "[none]";

        // later add emisive

        int r = 0;
        int g = 0;
        int b = 0;
        int a = 0;
    };

    struct wall
    {
        double sx = 0;
        double sy = 0;
        double ex = 0;
        double ey = 0;

        double mx = 0;
        double my = 0;

        double dist = 0;

        material mat;
    };
        
    struct static_object
    {
        std::string type = "static";

        double floor = 0;
        double celing = 0;

        material celling_mat;
        material floor_mat;

        double distance = 0;
        bool flip = 0;
        int surface = 0;
        int surf[32000];
        std::vector<wall> walls;
    };
    
} // namespace orgy
