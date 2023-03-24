#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>

 namespace orgee
 {
    class Camera{
        public:
            double x=0,y=0,z=0;  //Position
            double a=0;      // angle left-right
            double l=0;      // angle up-down
    };
 } // namespace orgee
 