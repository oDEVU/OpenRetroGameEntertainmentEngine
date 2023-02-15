#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>
#include <boost/compute.hpp>

#include "engine.hpp"

//#define CL_TARGET_OPENCL_VERSION 120

namespace compute = boost::compute;

compute::device ice = compute::system::default_device();
std::string gpu = "Using device: "+ice.name();

namespace orgy{
    int count_locally = 0;

    void print_debug(sf::RenderWindow *window, sf::Font font, int w_y, bool debug_lines, bool affine_rendering){
        count_locally++;

        std::string ver = "Using liblary: SFML "+std::to_string(SFML_VERSION_MAJOR)+"."+std::to_string(SFML_VERSION_MINOR)+"."+std::to_string(SFML_VERSION_PATCH);

        std::vector<std::string> info = {"Open-Retro-Game-Yngine [O-R-G-Y] -Rewrited", gpu, ver, "Current frame: "+std::to_string(count_locally), "Debug lines: "+std::to_string(debug_lines), "Affine texture rendering: "+std::to_string(affine_rendering)};

        int start = 55;

        for(int i = 0; i < info.size(); i++){
            sf::Text txt(info.at(i), font);
            txt.setCharacterSize((w_y/70));
            txt.setPosition(0, start+(((w_y/70)+5)*i));
            window->draw(txt);
        }
    }
}