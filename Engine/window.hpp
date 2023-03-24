#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>

 namespace orgee
 {
    class Window{
        public:
            Window(std::string name) {
                settings.antialiasingLevel = 8.0;
                title = name;
            }

            void setResolution(int x, int y) {
                sf::Vector2u viewSize{ x / pixelSize, y / pixelSize };
                sf::View view(sf::Vector2f(viewSize/2u),sf::Vector2f(viewSize));

                view.setSize( x / pixelSize, y / pixelSize );
                view.setCenter( x / pixelSize / 2u, y / pixelSize / 2u );

                win.create(sf::VideoMode(x, y), title);
                win.setView(view);
            }

            void reloadWindow(){
                int x = win.getSize().x;
                int y = win.getSize().y;

                sf::Vector2u viewSize{ x / pixelSize, y / pixelSize };
                sf::View view(sf::Vector2f(viewSize/2u),sf::Vector2f(viewSize));

                view.setSize( x / pixelSize, y / pixelSize );
                view.setCenter( x / pixelSize / 2u, y / pixelSize / 2u );

                win.setView(view);
            }

            sf::RenderWindow *getWindow() {
                return &win;
            }

            int getScale(){
                return pixelSize;
            }

        private:
            sf::ContextSettings settings;
            std::string title;
            sf::RenderWindow win;//(sf::VideoMode(800, 600), "SFML window");
            const unsigned int pixelSize{1u};  // temponary scaling method, dont recomended to use
    };
 } // namespace orgee
 