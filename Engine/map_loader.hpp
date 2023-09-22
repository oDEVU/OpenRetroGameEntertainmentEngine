#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <fstream>
#include <bits/stdc++.h> 
#include <json/json.h>

#include "static.hpp"
#include "layout.hpp"
#include "map.hpp"
#include "pathhandler.hpp"
#include "logger.hpp"

 namespace orgee
 {
    std::string exe_dir = orgee::getExecutablePath().substr(0, orgee::getExecutablePath().find_last_of("\\/")+1);

    Map loadMapFromFile(std::string path) {

        path = exe_dir + path;

        Map map;

        consoleLog("Loading map from path: " + path,0);

        std::ifstream map_file(path, std::ifstream::binary);
        Json::Reader reader;
        Json::Value map_raw_data;
        reader.parse(map_file, map_raw_data);

        for(Json::Value::ArrayIndex i = 0; i < map_raw_data["Objects"].size(); i++){
            static_object obj;

            obj.type = map_raw_data["Objects"][i]["type"].asString();

            if(obj.type == "static"){
                obj.celing = map_raw_data["Objects"][i]["celling"].asDouble();// << std::endl;
                obj.floor = map_raw_data["Objects"][i]["floor"].asDouble();// << std::endl;

                obj.celling_mat.txt = map_raw_data["Objects"][i]["celing_is_textured"].asBool();
                obj.celling_mat.r = map_raw_data["Objects"][i]["celing_r"].asInt();
                obj.celling_mat.g = map_raw_data["Objects"][i]["celing_g"].asInt();
                obj.celling_mat.b = map_raw_data["Objects"][i]["celing_b"].asInt();
                obj.celling_mat.a = map_raw_data["Objects"][i]["celing_a"].asInt();
                obj.celling_mat.txt_path = exe_dir + map_raw_data["Objects"][i]["celing_texture_path"].asString();
            
                obj.floor_mat.txt = map_raw_data["Objects"][i]["floor_is_textured"].asBool();
                obj.floor_mat.r = map_raw_data["Objects"][i]["floor_r"].asInt();
                obj.floor_mat.g = map_raw_data["Objects"][i]["floor_g"].asInt();
                obj.floor_mat.b = map_raw_data["Objects"][i]["floor_b"].asInt();
                obj.floor_mat.a = map_raw_data["Objects"][i]["floor_a"].asInt();
                obj.floor_mat.txt_path = exe_dir + map_raw_data["Objects"][i]["floor_texture_path"].asString();

                for(Json::Value::ArrayIndex j = 0; j < map_raw_data["Objects"][i]["walls"].size(); j++){
                    wall wall;

                    wall.sx = map_raw_data["Objects"][i]["walls"][j]["sx"].asDouble();
                    wall.sy = map_raw_data["Objects"][i]["walls"][j]["sy"].asDouble();
                    wall.ex = map_raw_data["Objects"][i]["walls"][j]["ex"].asDouble();
                    wall.ey = map_raw_data["Objects"][i]["walls"][j]["ey"].asDouble();
                    wall.mat.txt = map_raw_data["Objects"][i]["walls"][j]["is_textured"].asBool();
                    wall.mat.r = map_raw_data["Objects"][i]["walls"][j]["r"].asInt();
                    wall.mat.g = map_raw_data["Objects"][i]["walls"][j]["g"].asInt();
                    wall.mat.b = map_raw_data["Objects"][i]["walls"][j]["b"].asInt();
                    wall.mat.a = map_raw_data["Objects"][i]["walls"][j]["a"].asInt();
                    wall.mat.txt_path = exe_dir + map_raw_data["Objects"][i]["walls"][j]["texture_path"].asString();

                    obj.walls.push_back(wall);
                }
            }else if(obj.type == "entity"){
                obj.celing = map_raw_data["Objects"][i]["celling"].asDouble();// << std::endl;
                obj.floor = map_raw_data["Objects"][i]["floor"].asDouble();// << std::endl;

                wall wall;
                wall.sx = map_raw_data["Objects"][i]["walls"][0]["pos-x"].asDouble();
                wall.sy = map_raw_data["Objects"][i]["walls"][0]["pos-y"].asDouble();
                wall.mat.txt = true;
                wall.mat.txt_path = exe_dir + map_raw_data["Objects"][i]["walls"][0]["texture_path"].asString();

                obj.walls.push_back(wall);
            }else if(obj.type == "text"){

                obj.celing = map_raw_data["Objects"][i]["y"].asDouble();// << std::endl;
                obj.floor = map_raw_data["Objects"][i]["y"].asDouble();// << std::endl;

                wall wall;
                wall.sx = map_raw_data["Objects"][i]["x"].asDouble();
                wall.sy = map_raw_data["Objects"][i]["z"].asDouble();
                wall.ex = map_raw_data["Objects"][i]["x"].asDouble();
                wall.ey = map_raw_data["Objects"][i]["z"].asDouble();

                obj.text.setString(map_raw_data["Objects"][i]["text"].asString());
                obj.text.setCharacterSize(map_raw_data["Objects"][i]["font-size"].asDouble());
                obj.text.setColor(sf::Color(map_raw_data["Objects"][i]["r"].asInt(),map_raw_data["Objects"][i]["g"].asInt(),map_raw_data["Objects"][i]["b"].asInt(),map_raw_data["Objects"][i]["a"].asInt()));

                obj.walls.push_back(wall);
            }else{
                consoleLog("Could not load unknown object type.",0);
            }

            map.addObj(obj);
            consoleLog("Objects loaded succesfully",0);
        }

        for(Json::Value::ArrayIndex i = 0; i < map_raw_data["Layouts"].size(); i++){
            Layout layout( map_raw_data["Layouts"][i]["LayoutZIndex"].asInt());

            for(int j = 0; j < map_raw_data["Layouts"][i]["LayoutElements"].size(); j++){

            std::cout << "\n" << map_raw_data["Layouts"][i]["LayoutElements"].size() << " " << j << "\n";

            std::string type = map_raw_data["Layouts"][i]["LayoutElements"][j]["type"].asString();

            if(type == "rect"){

                vec2dyn position;
                vec2dyn size;
                alignment align;
                sf::Color color;
                int zindex;

                zindex = map_raw_data["Layouts"][i]["LayoutElements"][j]["zindex"].asInt();

                //auto zindex = map_raw_data["Layouts"][i]["LayoutElements"][j]["zindex"];//.asInt();

                //std::cout << zindex << std::endl;

                if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "none"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = None;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "topleft"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = TopLeft;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "top"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Top;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "topright"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = TopRight;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "right"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Right;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottomright"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = BottomRight;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottom"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Bottom;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottomleft"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = BottomLeft;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "left"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Left;
                }else{
                    consoleLog("Layout isnt valid",1);
                    exit(0);
                }

                size.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["width"].asString();
                size.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["height"].asString();

                color =  sf::Color(map_raw_data["Layouts"][i]["LayoutElements"][j]["r"].asInt()
                                       , map_raw_data["Layouts"][i]["LayoutElements"][j]["g"].asInt()
                                       , map_raw_data["Layouts"][i]["LayoutElements"][j]["b"].asInt()
                                       , map_raw_data["Layouts"][i]["LayoutElements"][j]["a"].asInt());

                layout.ElementArr.push_back(new Rect(position,size,align,color,zindex));
                //layout.ElementArr.back() = &elem;
            }else if(type == "image"){
                //Image elem;
                vec2dyn position;
                vec2dyn size;
                alignment align;
                std::string texture_path;
                int zindex;

                zindex = map_raw_data["Layouts"][i]["LayoutElements"][j]["zindex"].asInt();

                //auto zindex = map_raw_data["Layouts"][i]["LayoutElements"][j]["zindex"];//.asInt();

                //std::cout << zindex << std::endl;

                if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "none"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = None;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "topleft"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = TopLeft;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "top"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Top;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "topright"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = TopRight;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "right"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Right;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottomright"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = BottomRight;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottom"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Bottom;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottomleft"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = BottomLeft;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "left"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Left;
                }else{
                    consoleLog("Layout isnt valid",1);
                    exit(0);
                }

                size.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["width"].asString();
                size.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["height"].asString();

                texture_path = map_raw_data["Layouts"][i]["LayoutElements"][j]["texture_path"].asString();

                layout.ElementArr.push_back(new Image(position,size,align,texture_path,zindex));
                //layout.ElementArr.back() = &elem;
            }else if(type == "text"){
                //Text elem;std::string text;
            std::string text;
            vec2dyn position;
            int size;
            alignment align;
            std::string font_path;
            int zindex;

                zindex = map_raw_data["Layouts"][i]["LayoutElements"][j]["zindex"].asInt();

                //auto zindex = map_raw_data["Layouts"][i]["LayoutElements"][j]["zindex"];//.asInt();

                //std::cout << zindex << std::endl;

                if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "none"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = None;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "topleft"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = TopLeft;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "top"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Top;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "topright"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = TopRight;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "right"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Right;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottomright"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = BottomRight;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottom"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Bottom;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "bottomleft"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = BottomLeft;
                }else if(map_raw_data["Layouts"][i]["LayoutElements"][j]["align"].asString() == "left"){
                    position.x = map_raw_data["Layouts"][i]["LayoutElements"][j]["x"].asString();
                    position.y = map_raw_data["Layouts"][i]["LayoutElements"][j]["y"].asString();
                    align = Left;
                }else{
                    consoleLog("Layout isnt valid",1);
                    exit(0);
                }

                size = map_raw_data["Layouts"][i]["LayoutElements"][j]["font_size"].asInt();
                text = map_raw_data["Layouts"][i]["LayoutElements"][j]["text"].asString();

                font_path = map_raw_data["Layouts"][i]["LayoutElements"][j]["font_path"].asString();


                layout.ElementArr.push_back(new Text(position,size,align,font_path,text,zindex));
                //layout.ElementArr.back() = &elem;
            }else{
                Empty elem;
                layout.ElementArr.push_back(new Empty);
                //layout.ElementArr.back() = &elem;
            }
            consoleLog("loaded element",1);

            //std::cout << "\n" << map_raw_data["Layouts"][i]["LayoutElements"].size() << " " << j << "\n";
            }

            consoleLog("Layouts loaded succesfully",1);

            map.layouts.push_back(layout);
        }

        return map;
    }

    bool SaveMapToFile(Map map, std::string path) {

        path = exe_dir + path;

        consoleLog("Saving map to path: "+path,0);
        consoleLog("Saved map to path: "+path,0);

        return true;
    }
 } // namespace orgee
 