#include <raylib.h>

#include "player.cpp"

#define render_debug 1    // replace 1 with 0 to completly hide any debug info (engine name.fps,errors,etc)
#define render_polys_lines 0  //to visualize polys rendered by render.hpp [GLITCHED A LITTLE BIT]
#define window_title "O.R.G.Y - test demo"


const int size_of_dirs = 3;      //This is that way because of const char* :(, You must specify how many folders you will be working with.

const char* dirs[size_of_dirs] {   
    "/screenshots",
    "/configs",                                      //You add here all directores you are working with (start path = engine path)
    "/game/textures"            
};


    
    //Textures --------------------------------------------------

    Image bricks    = LoadImage("game/textures/bricks.png"); 
    Image grass     = LoadImage("game/textures/grass.png"); 
    Image stone     = LoadImage("game/textures/stone.png"); 
    Image icon      = LoadImage("engine/textures/tux.png");         //load window icon here
    //for placeholder textures you can use temp

    void Unload(){
        UnloadImage(bricks);            //This function is called at the end of program. You can unload your textures here or earlier.
        UnloadImage(grass); 
        UnloadImage(stone); 
    }

    //Texture Map ----------------------------------------------


    Image get_texture_from_texturemap(int txt) {

        Image texture;

            if(txt == 1){
                texture = bricks;
            }else if(txt == 2){
                texture = grass;
            }else if(txt == 3){
                texture = stone;
            }else{
                texture = temp;
            }

        return texture;
    }

    // map loader -----------------------------------------------

    int num_sec = 4;
    int num_wall = 16; 


    int load_sectors[] =
    { //ws,we,z1,z2,c1,c2,t,txtt,txtb
        0,4,0,40,0,0,0,0,0,       //sector 1
        4,8,0,40,2,2,0,0,0,       //sector 2
        8,12,0,40,99,99,0,0,0,    //sector 3
        12,16,0,40,99,99,1,2,3,   //sector 4
    };

    int load_walls[] =
    {  //x1,y1,x2,y2,color,is textured,texture,
        0,0,32,0,0,0,0,     //sector 1 * 4 walls
        32,0,32,32,0,0,0,
        32,32,0,32,0,0,0,
        0,32,0,0,0,0,0,

        64,0,96,0,2,0,0,    //sector 2 * 4 walls
        96,0,96,32,2,0,0,
        96,32,64,32,2,0,0,
        64,32,64,0,2,0,0,

        64,64,96,64,99,0,0,  //sector 3 * 4 walls
        96,64,96,96,99,0,0,
        96,96,64,96,99,0,0,
        64,96,64,64,99,0,0,

        0,64,32,64,69,1,1,   //sector 4 * 4 walls
        32,64,32,96,69,1,1,
        32,96,0,96,69,1,1,
        0,96,0,64,69,1,1,
    }; 

    //Color Map ----------------------------------------------


    Color get_color_from_colormap(int c) {

        Color top{ 255, 255, 255, 255 };
        
        if (c == 0){
             top = Color{ 255, 0, 0, 255 };
        }else if (c== 1){
             top = Color{ 155, 0, 0, 255 };
        }else if (c == 2){
             top = Color{ 0, 255, 0, 255 };
        }else if (c == 3){
             top = Color{ 0, 155, 0, 255 };
        }else if (c == 4){
             top = Color{ 0, 0, 255, 255 };
        }else if (c == 5){
             top = Color{ 0, 0, 155, 255 };
        }else if (c == 6){
             top = Color{ 255, 255, 0, 255 };
        }else if (c == 7){
             top = Color{ 155, 155, 0, 255 };
        }else{
             top = Color{ 255, 255, 255, 100 };
        }//You can add new colors here :)

        return top;
    }

    //Init stuff

    void init() {           // this function is called at start of the program

    }

    //Player spawn position

    int player_x = 0;     //Statick info
    int player_y = 0;
    int player_z = 0;
    int player_a = 0;
    int player_l = 0;

    void init_player() {   //Updates static info at init (for example load pos from file)
        player_x = 0;
        player_y = 0;
        player_z = 10;
        player_a = 0;
        player_l = 0;
    }

    //Every frame stuff

    int scrn_num_testing = 0;   //You need to use local variables not this in main

    void tick() {           // this function is called every frame (dont over use it)
        if (IsKeyPressed(KEY_F3)){
            printf("F3 pressed!");
        }

        handle_player_input();      //hadles player input from player.cpp
    }

    void draw_game() {      // this function is called every draw call (dont over use it) (you can use all raylib.h draw functions here)
        //DrawPixel(69,69,WHITE);
    }
