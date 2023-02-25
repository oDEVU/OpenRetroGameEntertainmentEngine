#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "engine.hpp"

namespace orgy{
    class screenDebuger{
        private:
            bool isInitialized = false;
            int start = 55;
            std::string gpu = " ";
            std::string ver = " ";
            std::vector<std::string> info = {"Open-Retro-Game-Yngine [O-R-G-Y] -Rewrited", " ", " ", "Current frame: ", "Debug lines: ", "Affine texture rendering: "};
        public:
            screenDebuger(){
                glfwInit();

                //gpu = "Using device: " + std::string( reinterpret_cast< const char* >(glGetString(GL_RENDERER)));
                ver = "Using liblary: SFML "+std::to_string(SFML_VERSION_MAJOR)+"."+std::to_string(SFML_VERSION_MINOR)+"."+std::to_string(SFML_VERSION_PATCH);

                //info.at(1) = gpu;
                info.at(2) = ver;
            }

    void print_debug(sf::RenderWindow *window, sf::Font font, int w_y, bool debug_lines, bool affine_rendering, int frames){
        //glfwInit(); /* create opengl context */
        if(!isInitialized){
            glfwInit();
                
            gpu = "Using device: " + std::string( reinterpret_cast< const char* >(glGetString(GL_RENDERER)));
                //ver = "Using liblary: SFML "+std::to_string(SFML_VERSION_MAJOR)+"."+std::to_string(SFML_VERSION_MINOR)+"."+std::to_string(SFML_VERSION_PATCH)
            info.at(1) = gpu;

            isInitialized = true;
        }
                //info.at(2) = ver;

        //std::string ver = "Using liblary: SFML "+std::to_string(SFML_VERSION_MAJOR)+"."+std::to_string(SFML_VERSION_MINOR)+"."+std::to_string(SFML_VERSION_PATCH);

       //info = {"Open-Retro-Game-Yngine [O-R-G-Y] -Rewrited", gpu, ver, "Current frame: "+std::to_string(frames), "Debug lines: "+std::to_string(debug_lines), "Affine texture rendering: "+std::to_string(affine_rendering)};

        info.at(3) = "Curent frame: " + std::to_string(frames);
        info.at(4) = "Debug lines: " + std::to_string(debug_lines);
        info.at(5) = "Affine texture rendering: " + std::to_string(affine_rendering);

        for(int i = 0; i < info.size(); i++){
            sf::Text txt(info.at(i), font);
            txt.setCharacterSize((w_y/70));
            txt.setPosition(0, start+(((w_y/70)+5)*i));
            window->draw(txt);
        }
    }
    };

}