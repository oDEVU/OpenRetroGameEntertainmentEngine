#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <fstream>
#include <bits/stdc++.h> 

#include "static.hpp"
#include "map.hpp"

 namespace orgy
 {
    Map loadMapFromFile(std::string path) {

        Map map;

        std::cout << "Loading map from path: " << path << std::endl;
        
        std::fstream file;

        file.open(path, std::ios::in);
        if(!file)
        {
            std::cout<<"Error in creating file..\n"<<std::endl;
            //return 0;
        }else{
            int l = 0;
            file >> l;

            std::cout << "Loaded " << l << " objects." << std::endl;

            for(int i = 0; i < l; i++){
                static_object obj;// = map.getObjAt(i);
                file >> obj.celing;
                file >> obj.floor;
                file >> obj.distance;
                file >> obj.flip;

                int l2 = 0;

                file >> l2;

                std::cout << "Object " << (i+1) << " has " << l2 << " walls." << std::endl;

                for(int i = 0; i < l2; i++){
                    wall wall;// = obj.walls.at(i);
                    file >> wall.sx;
                    file >> wall.sy;
                    file >> wall.ex;
                    file >> wall.ey;
                    file >> wall.mat;
                    file >> wall.r;
                    file >> wall.g;
                    file >> wall.b;
                    file >> wall.texture_path;

                    obj.walls.push_back(wall);
                }

                map.addObj(obj);
            }
            file.close();
        }

        return map;

        std::cout << "Loaded map from path: " << path << std::endl;
    }

    bool SaveMapToFile(Map map, std::string path) {

        std::cout << "Saving map to path: " << path << std::endl;

        std::fstream file;

        file.open(path, std::ios::out);
        if(!file)
        {
            std::cout<<"Error in creating file..\n"<<std::endl;
            //return 0;
        }else{
            file << map.getObjCount() << " ";

            std::cout << "Object count: " << map.getObjCount() << std::endl;

            for(int i = 0; i < map.getObjCount(); i++){
                static_object obj = map.getObjAt(i);
                file << obj.celing << " ";
                file << obj.floor << " ";
                file << obj.distance << " ";
                file << obj.flip << " ";

                file << obj.walls.size() << " ";

                std::cout << "walls count: " << obj.walls.size() << std::endl;

                for(int i = 0; i < obj.walls.size(); i++){
                    wall wall = obj.walls.at(i);
                    file << wall.sx << " ";
                    file << wall.sy << " ";
                    file << wall.ex << " ";
                    file << wall.ey << " ";
                    file << wall.mat << " ";
                    file << wall.r << " ";
                    file << wall.g << " ";
                    file << wall.b << " ";
                    file << wall.texture_path << " ";
                }
            }
            file.close();
        }

        std::cout << "Saved map to path: " << path << std::endl;
    }
 } // namespace orgy
 