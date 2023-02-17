#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>

#include "map.hpp"
#include "static.hpp"
#include "object_rendering.hpp"
#include "engine_math.hpp"
#include "camera.hpp"
#include "debug_screen.hpp"

 namespace orgy
 {
    class Renderer{
        public:

            bool affine_rendering = false;
            bool debug_lines = false;

            Renderer() {
                font.loadFromFile("EngineAssets/fonts/font.ttf");

                std::cout << "Renderer object created!" << std::endl;
            }

            void renderGame(sf::RenderWindow *window) {
                sf::Clock clock;
                double lastTime = 0;

                while (window->isOpen())
                {
                    frame_count++;

                    int w_x = window->getSize().x;
                    int w_y = window->getSize().y;

                    double currentTime = clock.restart().asSeconds();
                    fps = 1.f / currentTime;
                    delta = currentTime;
                    lastTime = currentTime;

                    // Event processing
                    sf::Event event;
                    while (window->pollEvent(event))
                    {
                        switch (event.type) {
                        case sf::Event::EventType::Closed:
                            window->close();
                            break;
                        case sf::Event::EventType::Resized:
                            std::cout << "Window resized! \nNew size   x:" << event.size.width <<"   y:"<< event.size.height << "\n";
                            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                            window->setView(sf::View(visibleArea));
                        }
                        if (event.type == sf::Event::KeyReleased)
                        {
                            if (event.key.code == sf::Keyboard::F1)
                            {
                                affine_rendering = !affine_rendering;
                            }
                            if (event.key.code == sf::Keyboard::F2)
                            {
                                debug_lines = !debug_lines;
                            }
                        }
                    }

                    window->clear(sf::Color(25,25,25));

                    Camera temp_cam = cam;

                    if(loaded_map){
                        //render map

                        static_draw(window, temp_cam, &map, debug_lines, affine_rendering, font);
                    }

                    if(show_fps){
                    //fps
                    sf::Text txt("Hello, World !", font);
                    txt.setString("FPS: "+std::to_string(fps)+"\n");
                    txt.setCharacterSize(w_y/70);
                    window->draw(txt);
                    }

                    print_debug(window, font, w_y, debug_lines, affine_rendering);

                    if(texts.size()>0){
                        for(int i = texts.size()-1; i >= 0; i--){
                            int pos = texts.size() - i;

                            texts.at(i).setCharacterSize(w_y/70);
                            texts.at(i).setPosition(0, (((w_y/70)*pos)+(w_y/70)));
                            window->draw(texts.at(i));
                        }
                    }

                    // End the current frame and display its contents on screen
                    // Activate the window for OpenGL rendering
                    //window->setActive();

                    // OpenGL drawing commands go here...

                    window->display();
                }
            }

            double getFps() {
                return fps;
            }

            double getDelta() {
                return delta;
            }

            void printToScreen(std::string text) {
                sf::Text txt("Hello, World !", font);
                txt.setString(text);
                texts.push_back(txt);
            }

            void LoadMap(Map mapp) {
                map = mapp;
                loaded_map = 1;
            }

            void showFps(bool b){
                show_fps = b;
            }

            Map getMap() {
                return map;
            }

            void setCamera(Camera &camera){
                cam = camera;
            }

            int get_current_frame(){
                return frame_count;
            }

            Camera getCamera() {
                return cam;
            }

            Camera cam;

        private:
            sf::Font font;
            double fps = 0; 
            double delta = 0;
            bool show_fps = 0;

            int frame_count = 0;

            bool loaded_map = 0;

            std::vector<sf::Text> texts;
            Map map;

    };
 } // namespace orgy
  
