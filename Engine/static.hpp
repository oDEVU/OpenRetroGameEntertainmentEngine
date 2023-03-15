#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>

namespace orgy
{
    struct material
    {
        bool txt = 0;
        std::string txt_path = "[none]";

        // later add emisive

        int r = 0;
        int g = 0;
        int b = 0;
        int a = 0;
    };

    /*class Wall{
        private:
            double sx = 0;
            double sy = 0;
            double ex = 0;
            double ey = 0;

            double mx = 0;
            double my = 0;

            material mat = new material;
        public:
            void setPos(double i_sx, double i_sy, double i_ex, double i_ey){
                sx = i_sx;
                sy = i_sy;
                ex = i_ex;
                ey = i_ey;
            }

            void setZAxis(double i_mx, double i_my){
                mx = i_mx;
                my = i_my;
            }

            void setMaterial(material i_mat){
                mat = i_mat;
                newMaterial = 1; 
            }

            double dist = 0;
            bool newMaterial = 1;
    };*/

    // YOU NEED TO FINISH REWRITING THIS YOU DUMB FUCK !!!!

    struct wall
    {
        double sx = 0;
        double sy = 0;
        double ex = 0;
        double ey = 0;

        double mx = 0;
        double my = 0;

        double dist = 0;

        material mat;
    };
        
    struct static_object
    {
        std::string type = "static";

        double floor = 0;
        double celing = 0;

        material celling_mat;
        material floor_mat;

        double distance = 0;
        bool flip = 0;
        int surface = 0;
        int surf[32000];
        std::vector<wall> walls;

        // text vars

        sf::Text text;
        int w = 0;
        int h = 0;
    };
    
} // namespace orgy
