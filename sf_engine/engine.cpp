
// compile with: g++ -o ../packaged/app engine.cpp SelbaWard/ElasticSprite.cpp -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system
// IF YOU COMPILE FROM TERMIANAL YOU NEED TO COPY ASSTETS YOURSELF.

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
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
#include <fstream>

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

    bool vsync = 0;
    bool debug = 0;

    std::fstream file;

    file.open("setting.cfg",std::ios::in);
    if(!file){
        std::cout<<"Error in opening file..";
        //return 0;
    }
    file>>vsync;
    file>>debug;
    file>>w_x;
    file>>w_y;
    file.close();

    for(int i=0;i<size_of_dirs;i++){
    const char* engine_path = path.c_str();
    const char* dir = dirs[i];

    std::string buf(engine_path);
    buf.append(dir);

    std::filesystem::create_directories(buf);
    }  

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
    //init_player();

    Cam.x = player_x; Cam.y = player_y; Cam.z = player_y; Cam.a = player_a; Cam.l = player_l;

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
    double lastTime = 0;


    while (window.isOpen()) {
        //frame_counter++;
        double currentTime = clock.restart().asSeconds();
        double fps = 1.f / currentTime;
        lastTime = currentTime;

        //GAmeloop

        tick(currentTime);
 
        file.open("setting.cfg",std::ios::out);
        if(!file)
        {
            std::cout<<"Error in creating file..\n"<<std::endl;
            //return 0;
        }else{
            file<<vsync<<" "<<debug<<" "<<w_x<<" "<<w_y<<std::endl;
            file.close();
        }


        sf::Event e;
        while (window.pollEvent(e)) {
            w_x = window.getSize().x;
            w_y = window.getSize().y;

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

            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::F2)){
                window.setVerticalSyncEnabled(vsync);
                vsync = !vsync;
            }

            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::F1)){
                //window.setVerticalSyncEnabled(vsync);
                debug = !debug;
            }

            event(&e);
        }
        //window.create(sf::VideoMode(e.size.width, e.size.height), "O.R.G.Y - SFML_REWRITE");

        window.clear(sf::Color(22,22,22));
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

        if(debug && render_debug == 1){
            sf::Color fps_col;
            if(fps>=240){
                fps_col = sf::Color(0,255,255);
            }else if(fps>=120){
                fps_col = sf::Color(0,255,100);
            }else if(fps>=60){
                fps_col = sf::Color(0,255,0);
            }else if(fps>=45){
                fps_col = sf::Color(100,255,0);
            }else if(fps>=30){
                fps_col = sf::Color(255,200,0);
            }else if(fps>=0){
                fps_col = sf::Color(255,0,0);
            }

            message.setString("OpenRetroGameYngine - SFML "+std::to_string(SFML_VERSION_MAJOR)+"."+std::to_string(SFML_VERSION_MINOR)+"."+std::to_string(SFML_VERSION_PATCH)+" [0.0.4]");
            //message.setColor(sf::Color(255,0,0));
            message.setPosition(8,8);
            message.setFillColor(sf::Color(255,255,0));
            message.setOutlineColor(sf::Color(0,0,0));
            message.setOutlineThickness(w_y/(70*2.5));
            message.setCharacterSize(w_y/70);
            window.draw(message);

            sf::Text messagea("", font);
            messagea.setString("FPS: "+std::to_string(fps)+"\n");
            //message.setColor(sf::Color(255,0,0));
            messagea.setPosition(8,8+((w_y/70)+8));
            messagea.setFillColor(fps_col);
            messagea.setOutlineColor(sf::Color(0,0,0));
            messagea.setOutlineThickness(w_y/(70*2.5));
            messagea.setCharacterSize(w_y/70);
            window.draw(messagea);

            sf::Text messageab("", font);
            messageab.setString("Delta: "+std::to_string(currentTime)+"\n");
            //message.setColor(sf::Color(255,0,0));
            messageab.setPosition(8,8+((w_y/70)+8)*2);
            messageab.setFillColor(fps_col);
            messageab.setOutlineColor(sf::Color(0,0,0));
            messageab.setOutlineThickness(w_y/(70*2.5));
            messageab.setCharacterSize(w_y/70);
            window.draw(messageab);

            sf::Text messageabc("", font);
            messageabc.setString("Camera pos / X: "+std::to_string(Cam.x)+" | Y: "+std::to_string(Cam.y)+" | Z: "+std::to_string(Cam.z)+" |");
            //message.setColor(sf::Color(255,0,0));
            messageabc.setPosition(8,8+((w_y/70)+8)*3);
            messageabc.setFillColor(sf::Color(255,255,255));
            messageabc.setOutlineColor(sf::Color(0,0,0));
            messageabc.setOutlineThickness(w_y/(70*2.5));
            messageabc.setCharacterSize(w_y/70);
            window.draw(messageabc);
        }
        window.display();
    }
    return 0;
}