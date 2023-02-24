#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <map>

#include "ThirdParty/SelbaWard/SelbaWard.hpp"
#include "logger.hpp"

namespace poly {

std::map<std::string, sf::Texture> textures_map;

void draw_poly_lines(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, sf::RenderWindow* window){
sf::ConvexShape convex;

// resize it to 5 points
convex.setPointCount(4);

// define the points
convex.setPoint(0, sf::Vector2f(x1, y1));
convex.setPoint(1, sf::Vector2f(x2, y2));
convex.setPoint(2, sf::Vector2f(x3, y3));
convex.setPoint(3, sf::Vector2f(x4, y4));

convex.setFillColor(sf::Color(0,0,0,0));
convex.setOutlineThickness(2);
convex.setOutlineColor(sf::Color(255,255,255,255));

window->draw(convex);

sf::Vertex line[] =
{
    sf::Vertex(sf::Vector2f(x2, y2)),
    sf::Vertex(sf::Vector2f(x4, y4))
};

window->draw(line, 5, sf::Lines);
}

void draw_poly(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, sf::Color col, sf::RenderWindow* window){
        sf::VertexArray tris{sf::PrimitiveType::Triangles, 6};
        tris[0].position = {x4, y4};
        tris[1].position = {x1, y1};
        tris[2].position = {x2, y2};
        tris[3].position = {x2, y2};
        tris[4].position = {x3, y3};
        tris[5].position = {x4, y4};
        tris[0].color = col;
        tris[1].color = col;
        tris[2].color = col;
        tris[3].color = col;
        tris[4].color = col;
        tris[5].color = col;
        window->draw(tris);
}

void draw_poly_txt_affine(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, std::string path, sf::RenderWindow* window){

    if(!textures_map.contains(path)){

        sf::Texture texture;
        if (!texture.loadFromFile(path))
        {
            if (!texture.loadFromFile("empty.png"))
            {
                stringLog("Fatal error!!! could not find EngineAssets folder",1);
            }
            stringLog("Failed to load texture from path!",1);
        }

        textures_map.insert({path, texture});
    }

        sf::VertexArray tris{sf::PrimitiveType::Triangles, 6};
        tris[0].position = {x4, y4};
        tris[1].position = {x1, y1};
        tris[2].position = {x2, y2};
        tris[3].position = {x2, y2};
        tris[4].position = {x3, y3};
        tris[5].position = {x4, y4};
        tris[0].texCoords = {0,                     0};
        tris[1].texCoords = {0,                     textures_map[path].getSize().y};
        tris[2].texCoords = {textures_map[path].getSize().x,   textures_map[path].getSize().y};
        tris[3].texCoords = {textures_map[path].getSize().x,   textures_map[path].getSize().y};
        tris[4].texCoords = {textures_map[path].getSize().x,   0};
        tris[5].texCoords = {0,                     0};
        window->draw(tris, &textures_map[path]);
}

void draw_poly_txt_correct(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, std::string path, sf::RenderWindow* window){

    if(!textures_map.contains(path)){

        sf::Texture texture;
        if (!texture.loadFromFile(path))
        {
            if (!texture.loadFromFile("EngineAssets/textures/empty.png"))
            {
                stringLog("Fatal error!!! could not find EngineAssets folder",1);
            }
            stringLog("Failed to load texture from path!",1);
        }

        textures_map.insert({path, texture});
    }

    int x = textures_map[path].getSize().x;//texture.getSize().x;
    int y = textures_map[path].getSize().y;

    //std::cout << "Texture size x: " << x << " | y: " << y <<"\n";
    sw::ElasticSprite sprite(textures_map[path]);

    sprite.setVertexOffset(0, { x1       , y4        });
    sprite.setVertexOffset(3, { x2-x     , y3        });
    sprite.setVertexOffset(2, { x3-x     , y2-y      });
    sprite.setVertexOffset(1, { x4       , y1-y      });

    sprite.activatePerspectiveInterpolation();
    //sprite.activateBilinearInterpolation();
    //sprite.setUseShader();

    //std::cout << x << std::endl;
    window->draw(sprite);
}
}