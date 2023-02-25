#pragma once

//#include "structures.hpp"
#include "../../Engine/engine.hpp"
#include <iostream>

double player_walk_speed = 60;
double player_fly_speed = 60;
double player_rotation_speed = 60;

//player funtions

void move_player_forward(int speed, double delta) {
    int dx=sin(orgy::d_to_rad(render.getCamera().a))*speed;
    int dy=cos(orgy::d_to_rad(render.getCamera().a))*speed;
    render.cam.x+=dx*delta; 
    render.cam.y+=dy*delta; 

    //std::cout << "w\n";
} 

void move_player_back(int speed , double delta) {
    int dx=sin(orgy::d_to_rad(render.getCamera().a))*speed;
    int dy=cos(orgy::d_to_rad(render.getCamera().a))*speed;
    render.cam.x-=dx*delta; 
    render.cam.y-=dy*delta; 

    //std::cout << "s\n";
} 

void move_player_left(int speed , double delta) {
    int dx=sin(orgy::d_to_rad(render.getCamera().a))*speed;
    int dy=cos(orgy::d_to_rad(render.getCamera().a))*speed;
    render.cam.x-=dy*delta; 
    render.cam.y+=dx*delta; 

    //std::cout << "a\n";
} 

void move_player_right(int speed , double delta) {
    int dx=sin(orgy::d_to_rad(render.getCamera().a))*speed;
    int dy=cos(orgy::d_to_rad(render.getCamera().a))*speed;
    render.cam.x+=dy*delta; 
    render.cam.y-=dx*delta;

    //std::cout << "d\n";
} 

void move_player_up(int speed , double delta) {
            render.cam.z -= speed*delta;
} 

void move_player_down(int speed , double delta) {
            render.cam.z += speed*delta;
} 

void rotate_player_left(int speed , double delta) {
    render.cam.a -= speed*(delta);
    if (render.cam.a < 0){
        render.cam.a += 360;
    }
} 

void rotate_player_right(int speed , double delta) {
    render.cam.a += speed*(delta);
    if (render.cam.a > 359){
        render.cam.a -= 360;
    }
} 

void rotate_player_up(int speed , double delta) {
    render.cam.l += speed*delta;
} 

void rotate_player_down(int speed , double delta) {
    render.cam.l -= speed*delta;
} 

void handle_player_input(double time) {
    //player moving

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rotate_player_right(player_rotation_speed,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rotate_player_left(player_rotation_speed,time);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            move_player_forward(player_walk_speed,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            move_player_back(player_walk_speed,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            move_player_right(player_walk_speed,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            move_player_left(player_walk_speed,time);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            move_player_up(player_fly_speed,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
            move_player_down(player_fly_speed,time);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rotate_player_up(player_rotation_speed,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rotate_player_down(player_rotation_speed,time);
        }
} 
               