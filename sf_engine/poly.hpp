#pragma once

namespace poly {

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
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        if (!texture.loadFromFile("sf_engine/sf_engine_src/textures/temp.png"))
        {
            std::cout << "Fatal error!!! could not find sf_engine path\n";
        }
        std::cout << "Failed to load texture from path!\n";
    }
        sf::VertexArray tris{sf::PrimitiveType::Triangles, 6};
        tris[0].position = {x4, y4};
        tris[1].position = {x1, y1};
        tris[2].position = {x2, y2};
        tris[3].position = {x2, y2};
        tris[4].position = {x3, y3};
        tris[5].position = {x4, y4};
        tris[0].texCoords = {0,                     0};
        tris[1].texCoords = {0,                     texture.getSize().y};
        tris[2].texCoords = {texture.getSize().x,   texture.getSize().y};
        tris[3].texCoords = {texture.getSize().x,   texture.getSize().y};
        tris[4].texCoords = {texture.getSize().x,   0};
        tris[5].texCoords = {0,                     0};
        window->draw(tris, &texture);
}

void draw_poly_txt_correct(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, std::string path, sf::RenderWindow* window){
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        if (!texture.loadFromFile("sf_engine/sf_engine_src/textures/temp.png"))
        {
            std::cout << "Fatal error!!! could not find sf_engine path\n";
        }
        std::cout << "Failed to load texture from path!\n";
    }
    int x = texture.getSize().x;
    int y = texture.getSize().y;
    sw::ElasticSprite sprite(texture);
    sprite.setVertexOffset(0, { x1       , y1        });
    sprite.setVertexOffset(3, { x2-x     , y2        });
    sprite.setVertexOffset(2, { x3-x     , y3-y      });
    sprite.setVertexOffset(1, { x4       , y4-y      });

    sprite.activatePerspectiveInterpolation();
    //sprite.setUseShader();

    //std::cout << x << std::endl;
    window->draw(sprite);
}
}