#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>
#include <boost/compute.hpp>

#include "map.hpp"
#include "poly.hpp"
//#include "static.hpp"
#include "engine_math.hpp"
//#include "camera.hpp"
#include "pathhandler.hpp"
#include "functions.hpp"
#include "logger.hpp"
#include "window.hpp"
#include "layout.hpp"

namespace orgee
{
    void layout_draw(sf::RenderWindow *window, Map *map, sf::Font font, Window *win){
        for(int i = 0; i < map->layouts.size(); i++){
            for(int j = 0; j < map->layouts.at(i).ElementArr.size(); j++){

                if(map->layouts.at(i).ElementArr.at(j).type() == typeid(Empty)){
                    // pass
                }else if(map->layouts.at(i).ElementArr.at(j).type() == typeid(Rect)){
                    //std::any_cast<Rect>(map->layouts.at(i).ElementArr.at(j)).test();
                    Rect temp = std::any_cast<Rect>(map->layouts.at(i).ElementArr.at(j));

                    int heigth = 0;
                    int width = 0;

                    int find = temp.size.x.find("px");

                    if(find != std::string::npos){
                        width = stoi(temp.size.x.substr(0,find));
                    }else{
                       find = temp.size.x.find("%"); 

                       float t = stoi(temp.size.x.substr(0,find));

                       width = window->getSize().x * (float)(t/100);
                    }

                    find = temp.size.y.find("px");

                    if(find != std::string::npos){
                        heigth = stoi(temp.size.y.substr(0,find));
                    }else{
                       find = temp.size.x.find("%"); 

                       float t = stoi(temp.size.y.substr(0,find));

                       heigth = window->getSize().y * (float)(t/100);
                    }

                    int pos_x = 0;
                    int pos_y = 0;

                    if(temp.position.x != ""){

                    int at = temp.position.x.find("px");

                    //pos x
                    if(at != std::string::npos){
                        pos_x = stoi(temp.position.x.substr(0,at));
                    }else{
                       at = temp.position.x.find("%"); 

                       float t = stoi(temp.position.x.substr(0,at));

                       pos_x = window->getSize().x * (float)(t/100);
                    }

                    at = temp.position.y.find("px");

                    //pos y
                    if(at != std::string::npos){
                        pos_y = stoi(temp.position.y.substr(0,at));
                    }else{
                       at = temp.position.x.find("%"); 

                       float t = stoi(temp.position.y.substr(0,at));

                       pos_y = window->getSize().y * (float)(t/100);
                    }
                    }

                        int x = pos_x, y = pos_y;

                        switch(temp.align) {
                            case Bottom:
                                pos_y = (window->getSize().y - heigth)-y;
                                pos_x = ((window->getSize().x/2) - (width/2))+x;
                                break;
                            case BottomLeft:
                                pos_y = window->getSize().y - heigth-y;
                                pos_x = 0+x;
                                break;
                            case BottomRight:
                                pos_y = window->getSize().y - heigth-y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Top:
                                pos_y = 0+y;
                                pos_x = (window->getSize().x/2) - (width/2)+x;
                                break;
                            case TopLeft:
                                pos_y = 0+y;
                                pos_x = 0+x;
                                break;
                            case TopRight:
                                pos_y = 0+y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Right:
                                pos_y = (window->getSize().y/2) - (heigth/2)+y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Left:
                                pos_y = (window->getSize().y/2) - (heigth/2)+y;
                                pos_x = 0+x;
                                break;
                            default:
                                break;
                        }


                    sf::RectangleShape rectangle(sf::Vector2f(width,heigth));
                    rectangle.setPosition(pos_x,pos_y);

                    rectangle.setFillColor(temp.color);

                    window->draw(rectangle);
                }
            }
        }
    }
}