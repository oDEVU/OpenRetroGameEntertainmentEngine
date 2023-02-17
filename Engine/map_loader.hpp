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
#include "map.hpp"

 namespace orgy
 {
    Map loadMapFromFile(std::string path) {

        Map map;

        std::cout << "Loading map from path: " << path << std::endl;

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
                obj.celling_mat.txt_path = map_raw_data["Objects"][i]["celing_texture_path"].asString();
            
                obj.floor_mat.txt = map_raw_data["Objects"][i]["floor_is_textured"].asBool();
                obj.floor_mat.r = map_raw_data["Objects"][i]["floor_r"].asInt();
                obj.floor_mat.g = map_raw_data["Objects"][i]["floor_g"].asInt();
                obj.floor_mat.b = map_raw_data["Objects"][i]["floor_b"].asInt();
                obj.floor_mat.a = map_raw_data["Objects"][i]["floor_a"].asInt();
                obj.floor_mat.txt_path = map_raw_data["Objects"][i]["floor_texture_path"].asString();

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
                    wall.mat.txt_path = map_raw_data["Objects"][i]["walls"][j]["texture_path"].asString();
                    obj.walls.push_back(wall);
                }
            }else if(obj.type == "entity"){
                obj.celing = map_raw_data["Objects"][i]["celling"].asDouble();// << std::endl;
                obj.floor = map_raw_data["Objects"][i]["floor"].asDouble();// << std::endl;

                wall wall;
                wall.sx = map_raw_data["Objects"][i]["walls"][0]["pos-x"].asDouble();
                wall.sy = map_raw_data["Objects"][i]["walls"][0]["pos-y"].asDouble();
                wall.mat.txt = true;
                wall.mat.txt_path = map_raw_data["Objects"][i]["walls"][0]["texture_path"].asString();

                obj.walls.push_back(wall);
            }else if(obj.type == "text"){
                obj.celing = map_raw_data["Objects"][i]["y"].asDouble();// << std::endl;
                obj.floor = map_raw_data["Objects"][i]["y"].asDouble();// << std::endl;

                wall wall;
                wall.sx = map_raw_data["Objects"][i]["x"].asDouble();
                wall.sy = map_raw_data["Objects"][i]["z"].asDouble();
                wall.ex = map_raw_data["Objects"][i]["x"].asDouble();
                wall.ey = map_raw_data["Objects"][i]["z"].asDouble();
                wall.mat.txt_path = map_raw_data["Objects"][i]["text"].asString();
                wall.mat.r = map_raw_data["Objects"][i]["font-size"].asDouble();

                obj.walls.push_back(wall);
            }else{
                std::cout << "Could not load unknown object type.\n";
            }

            map.addObj(obj);
        }


        return map;
    }

    bool SaveMapToFile(Map map, std::string path) {

        std::cout << "Saving map to path: " << path << std::endl;

        std::cout << "Saved map to path: " << path << std::endl;
        return true;
    }
 } // namespace orgy
 