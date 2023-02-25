#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include "static.hpp"

 namespace orgy
 {
    class Map{
        public:
            void addObj(static_object obj){
                objs.push_back(obj);
            }

            int getObjCount() {
                return objs.size();
            }

            static_object getObjAt(int i) {
                return objs.at(i);
            }
            
            std::vector<static_object> objs;
            std::map<std::string, bool> arguments;
    };
 } // namespace orgy
 