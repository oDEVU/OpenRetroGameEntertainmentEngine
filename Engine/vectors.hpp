#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>

namespace orgee
{
    struct vec2{
        int x=0;
        int y=0;
    }; 
    struct vec3{
        int x=0;
        int y=0;
        int z=0;
    }; 
    struct vec4{
        int x=0;
        int y=0;
        int z=0;
        int w=0;
    }; 
    struct vec2dyn{
        std::string x="0px";
        std::string y="0px";
    }; 
}