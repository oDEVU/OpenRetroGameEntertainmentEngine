#pragma once

#include <raylib.h>
//#include "structures.hpp"

namespace player_class{

float player_walk_speed = 100;
float player_fly_speed = 100;
float player_rotation_speed = 100;

//player funtions

void move_player_forward(int speed,player* P ) {
    int dx=sin(glogal_functions::torad(P->a))*speed;
    int dy=cos(glogal_functions::torad(P->a))*speed;
    P->x+=dx*GetFrameTime(); P->y+=dy*GetFrameTime();
} 

void move_player_back(int speed,player* P ) {
    int dx=sin(glogal_functions::torad(P->a))*speed;
    int dy=cos(glogal_functions::torad(P->a))*speed;
    P->x-=dx*GetFrameTime(); P->y-=dy*GetFrameTime();
} 

void move_player_left(int speed,player* P ) {
    int dx=sin(glogal_functions::torad(P->a))*speed;
    int dy=cos(glogal_functions::torad(P->a))*speed;
    P->x-=dy*GetFrameTime(); P->y+=dx*GetFrameTime();
} 

void move_player_right(int speed,player* P ) {
    int dx=sin(glogal_functions::torad(P->a))*speed;
    int dy=cos(glogal_functions::torad(P->a))*speed;
    P->x+=dy*GetFrameTime(); P->y-=dx*GetFrameTime();
} 

void move_player_up(int speed,player* P ) {
            P->z -= speed*GetFrameTime();
} 

void move_player_down(int speed,player* P ) {
            P->z += speed*GetFrameTime();
} 

void rotate_player_left(int speed,player* P ) {
    P->a -= speed*(GetFrameTime());
    if (P->a < 0){
        P->a += 360;
    }
} 

void rotate_player_right(int speed,player* P ) {
    P->a += speed*(GetFrameTime());
    if (P->a > 359){
        P->a -= 360;
    }
} 

void rotate_player_up(int speed,player* P ) {
    P->l += speed*GetFrameTime();
} 

void rotate_player_down(int speed,player* P ) {
    P->l -= speed*GetFrameTime();
} 

void handle_player_input() {
    //player moving

        if (IsKeyDown(KEY_RIGHT)){
            rotate_player_right(player_rotation_speed,&P);
        }
        if (IsKeyDown(KEY_LEFT)){
            rotate_player_left(player_rotation_speed,&P);
        }

        if (IsKeyDown(KEY_W)){
            move_player_forward(player_walk_speed,&P);
        }
        if (IsKeyDown(KEY_S)){
            move_player_back(player_walk_speed,&P);
        }
        if (IsKeyDown(KEY_D)){
            move_player_right(player_walk_speed,&P);
        }
        if (IsKeyDown(KEY_A)){
            move_player_left(player_walk_speed,&P);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT)){
            move_player_up(player_fly_speed,&P);
        }
        if (IsKeyDown(KEY_LEFT_CONTROL)){
            move_player_down(player_fly_speed,&P);
        }

        if (IsKeyDown(KEY_UP)){
            rotate_player_up(player_rotation_speed,&P);
        }
        if (IsKeyDown(KEY_DOWN)){
            rotate_player_down(player_rotation_speed,&P);
        }
} 

}
