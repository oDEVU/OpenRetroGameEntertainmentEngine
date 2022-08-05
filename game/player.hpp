#pragma once

//#include "structures.hpp"

namespace player_class{

double player_walk_speed = 100;
double player_fly_speed = 100;
double player_rotation_speed = 100;

//player funtions

void move_player_forward(int speed,camera* P , double delta) {
    int dx=sin(glogal_functions::torad(P->a))*speed;
    int dy=cos(glogal_functions::torad(P->a))*speed;
    P->x+=dx*delta; P->y+=dy*delta;
} 

void move_player_back(int speed,camera* P , double delta) {
    int dx=sin(glogal_functions::torad(P->a))*speed;
    int dy=cos(glogal_functions::torad(P->a))*speed;
    P->x-=dx*delta; P->y-=dy*delta;
} 

void move_player_left(int speed,camera* P , double delta) {
    int dx=sin(glogal_functions::torad(P->a))*speed;
    int dy=cos(glogal_functions::torad(P->a))*speed;
    P->x-=dy*delta; P->y+=dx*delta;
} 

void move_player_right(int speed,camera* P , double delta) {
    int dx=sin(glogal_functions::torad(P->a))*speed;
    int dy=cos(glogal_functions::torad(P->a))*speed;
    P->x+=dy*delta; P->y-=dx*delta;
} 

void move_player_up(int speed,camera* P , double delta) {
            P->z -= speed*delta;
} 

void move_player_down(int speed,camera* P , double delta) {
            P->z += speed*delta;
} 

void rotate_player_left(int speed,camera* P , double delta) {
    P->a -= speed*(delta);
    if (P->a < 0){
        P->a += 360;
    }
} 

void rotate_player_right(int speed,camera* P , double delta) {
    P->a += speed*(delta);
    if (P->a > 359){
        P->a -= 360;
    }
} 

void rotate_player_up(int speed,camera* P , double delta) {
    P->l += speed*delta;
} 

void rotate_player_down(int speed,camera* P , double delta) {
    P->l -= speed*delta;
} 

void handle_player_input(double time) {
    //player moving

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            rotate_player_right(player_rotation_speed,&Cam,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            rotate_player_left(player_rotation_speed,&Cam,time);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            move_player_forward(player_walk_speed,&Cam,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            move_player_back(player_walk_speed,&Cam,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            move_player_right(player_walk_speed,&Cam,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            move_player_left(player_walk_speed,&Cam,time);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
            move_player_up(player_fly_speed,&Cam,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
            move_player_down(player_fly_speed,&Cam,time);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            rotate_player_up(player_rotation_speed,&Cam,time);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            rotate_player_down(player_rotation_speed,&Cam,time);
        }
} 

}
                           