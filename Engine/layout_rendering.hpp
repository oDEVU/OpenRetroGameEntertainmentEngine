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
#include <variant>

namespace orgee
{
    //std::string global_path = orgee::getExecutablePath().substr(0, orgee::getExecutablePath().find_last_of("\\/")+1);

    void layout_draw(sf::RenderWindow *window, Map *map, sf::Font font, Window *win){
        for(int i = 0; i < map->layouts.size(); i++){
            for(int j = 0; j < map->layouts.at(i).ElementArr.size(); j++){

                //auto object = std::any_cast<LayoutElement*>(&map->layouts.at(i).ElementArr.at(j));

                //object->Update(0);

                auto object = map->layouts.at(i).ElementArr.at(j);
                object->Draw(window);
                

                /*if(map->layouts.at(i).ElementArr.at(j).type() == typeid(Empty)){
                    // pass
                }else if(map->layouts.at(i).ElementArr.at(j).type() == typeid(Rect)){
                    Rect temp = std::any_cast<Rect>(map->layouts.at(i).ElementArr.at(j));
                    temp.Draw(window);
                }else if(map->layouts.at(i).ElementArr.at(j).type() == typeid(Image)){
                    //std::any_cast<Rect>(map->layouts.at(i).ElementArr.at(j)).test();
                    Image temp = std::any_cast<Image>(map->layouts.at(i).ElementArr.at(j));
                    temp.Draw(window);
                }else if(map->layouts.at(i).ElementArr.at(j).type() == typeid(Text)){
                    //std::any_cast<Rect>(map->layouts.at(i).ElementArr.at(j)).test();
                    Text temp = std::any_cast<Text>(map->layouts.at(i).ElementArr.at(j));
                    temp.Draw(window);
                    //poly::draw_poly_txt_correct(pos_x, pos_y+height, pos_x+width, pos_y+height, pos_x+width, pos_y, pos_x, pos_y, global_path + temp.texture_path, window);
                }*/
            }
        }
    }
}