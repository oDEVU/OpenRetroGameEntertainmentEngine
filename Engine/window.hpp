#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>

 namespace orgy
 {
    class Window{
        public:
            Window(std::string name) {
                settings.antialiasingLevel = 8.0;
                title = name;
            }

            void setResolution(int x, int y) {
                win.create(sf::VideoMode(x, y), title);
            }

            sf::RenderWindow *getWindow() {
                return &win;
            }

        private:
            sf::ContextSettings settings;
            std::string title;
            sf::RenderWindow win;//(sf::VideoMode(800, 600), "SFML window");
    };
 } // namespace orgy
 