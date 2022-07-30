#include "player.hpp"

float player_walk_speed = 100;
float player_fly_speed = 100;
float player_rotation_speed = 100;

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
