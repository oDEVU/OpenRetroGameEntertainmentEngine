
// compile with: g++ -o ../packaged/app engine.cpp SelbaWard/ElasticSprite.cpp -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system
// IF YOU COMPILE FROM TERMIANAL YOU NEED TO COPY ASSTETS YOURSELF.

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <string>
#include "SelbaWard/ElasticSprite.hpp"
#include "poly.hpp"
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>

    #include "functions.hpp" 
    #include "../game/structures.hpp"
    #include "../editor/pathhandler.hpp"

    //Game things

    #include "../game/game.cpp"

    //Engine things        --------------------    Used only in  engine

    #include "render.hpp"
    //#include "debug.hpp"

int main() {

    std::string path = MyPaths::getExecutablePath().substr(0, MyPaths::getExecutablePath().find_last_of("\\/"));
    const char* dir = path.c_str();
    bool succes = chdir(dir);

    int w_x = 800;
    int w_y = 600;


    int frame_counter = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;

    sf::RenderWindow window(sf::VideoMode(w_x, w_y), window_title, sf::Style::Default, settings);
    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile(/*
                           Put the filename that identify the font file you want to load*/"sf_engine/sf_engine_src/fonts/font.ttf")) {
        return -1;
    }
    sf::Text message("Hello, World !", font);

    //init

    init();
    init_player();

    P.x = player_x; P.y = player_y; P.z = player_y; P.a = player_a; P.l = player_l;

    int s,w,v1=0,v2=0;

    for(s=0;s<num_sec;s++){
        S[s].ws=load_sectors[v1+0];
        S[s].we=load_sectors[v1+1];
        S[s].z1=load_sectors[v1+2];
        S[s].z2=load_sectors[v1+3]-load_sectors[v1+2];
        S[s].c1=load_sectors[v1+4];
        S[s].c2=load_sectors[v1+5];
        S[s].flip=load_sectors[v1+6];
        v1+=7;
        for(w=S[s].ws;w<S[s].we;w++){
            W[w].x1=load_walls[v2+0];
            W[w].y1=load_walls[v2+1];
            W[w].x2=load_walls[v2+2];
            W[w].y2=load_walls[v2+3];
            W[w].c=load_walls[v2+4];
            W[w].t=load_walls[v2+5];
            W[w].txt=load_walls[v2+6];
            v2+=7;
        }
    }


    sf::Clock clock;
    float lastTime = 0;


    while (window.isOpen()) {
        //frame_counter++;
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / currentTime;
        lastTime = currentTime;

        //GAmeloop

        tick(currentTime);

        sf::Event e;
        while (window.pollEvent(e)) {
            w_x = e.size.width;
            w_y = e.size.height;

            switch (e.type) {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            case sf::Event::EventType::Resized:
                std::cout << "Window resized! \nNew size   x:" << e.size.width <<"   y:"<< e.size.height << "\n";
                message.setString("Window size   x:"+std::to_string(e.size.width)+"   y:"+std::to_string(e.size.height)+"\n");
                sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
        //window.create(sf::VideoMode(e.size.width, e.size.height), "O.R.G.Y - SFML_REWRITE");

        window.clear();
        //draw call

        /*rectangle
        sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));
        rectangle.setSize(sf::Vector2f(100.f, 100.f));
        window.draw(rectangle);
        */

        /*poly
        sf::ConvexShape convex;
        convex.setPointCount(5);
        convex.setPoint(0, sf::Vector2f(0.f, 0.f));
        convex.setPoint(1, sf::Vector2f(150.f, 10.f));
        convex.setPoint(2, sf::Vector2f(120.f, 90.f));
        convex.setPoint(3, sf::Vector2f(30.f, 100.f));
        convex.setPoint(4, sf::Vector2f(0.f, 50.f));
        convex.setFillColor(sf::Color(255, 0, 0));
        window.draw(convex);
        */

       /*line
       sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(10.f, 10.f)),
            sf::Vertex(sf::Vector2f(150.f, 150.f))
        };
        window.draw(line, 2, sf::Lines);
        *//*
        poly::draw_poly(100, 0+50, 200, 0+50, 300, 100+50, 0, 100+50, sf::Color(255, 0, 0), &window);

        sf::Text message1("-Collored Poly", font);
        message1.setPosition(300,50);
        window.draw(message1);

        poly::draw_poly_txt_affine(100, 0+200, 200, 0+200, 300, 100+200, 0, 100+200, "../game/textures/bricks.png", &window);
        sf::Text message2("-Textured Poly [affine]", font);
        message2.setPosition(300,200);
        window.draw(message2);

        poly::draw_poly_txt_correct(100, 0+350, 200, 0+350, 300, 100+350, 0, 100+350, "../game/textures/bricks.png", &window);
        sf::Text message3("-Textured Poly [correct]", font);
        message3.setPosition(300,350);
        window.draw(message3);*/

        render_class::draw_3d(&window);

        draw_game(&window);

        message.setString("FPS: "+std::to_string(fps)+"\n");
        window.draw(message);
        window.display();
    }
    return 0;
}