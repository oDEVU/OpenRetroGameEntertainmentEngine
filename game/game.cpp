//hi and hello C:
#include "player.hpp"

#define render_debug 1    // replace 1 with 0 to completly hide any debug info (engine name.fps,errors,etc)     // not ported yet
#define render_polys_lines 0  //to visualize polys rendered by render.hpp [GLITCHED A LITTLE BIT]               // not ported yet
#define window_title "O.R.G.Y - SFML_REWRITE"


const int size_of_dirs = 3;      //This is that way because of const char* :(, You must specify how many folders you will be working with.      // not ported yet

const char* dirs[size_of_dirs] {   
    "/screenshots",
    "/configs",                                      //You add here all directores you are working with (start path = engine path)      // not ported yet
    "/game/textures"            
};


    
    //Textures --------------------------------------------------

    std::string bricks    = "game/textures/bricks.png"; 
    std::string grass     = "game/textures/grass.png"; 
    std::string stone     = "game/textures/stone.png"; 
    std::string icon      = "sf_engine/textures/tux.png";      

    //Texture Map ----------------------------------------------


    std::string get_texture_from_texturemap(int txt) {

        std::string texture;

            if(txt == 1){
                texture = bricks;
            }else if(txt == 2){
                texture = grass;
            }else if(txt == 3){
                texture = stone;
            }else{
                //texture = temp;
            }

        return texture;
    }

    // map loader -----------------------------------------------

    int num_sec = 6;
    int num_wall = 24; 


    int load_sectors[] =
    { //ws,we,z1,z2,c1,c2,t,txtt,txtb,flip
        0,4,0,40,0,0,1,       //sector 1
        4,8,0,40,2,2,0,       //sector 2
        8,12,0,40,8,8,0,    //sector 3
        12,16,0,40,6,3,0,   //sector 4
        16,21,0,40,9,9,0,     //sector 5
        21,24,0,40,5,5,0,     //sector 6
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

        64,64,96,64,99,3,3,  //sector 3 * 4 walls
        96,64,96,96,99,3,3,
        96,96,64,96,99,3,3,
        64,96,64,64,99,3,3,

        0,64,32,64,69,1,1,   //sector 4 * 4 walls
        32,64,32,96,69,1,1,
        32,96,0,96,69,1,1,
        0,96,0,64,69,1,1,

        0,128,32,128,9,0,0,   //sector 5 * 5 walls
        32,128,32,160,9,0,0,
        32,160,0,160,9,0,0,
        0,160,-16,144,9,0,0,
        -16,144,0,128,9,0,0,

        64,128,96,128,5,0,0,  //sector 6 * 3 walls
        96,128,96,160,5,0,0,
        96,160,64,128,5,0,0,
    }; 

    //Color Map ----------------------------------------------


    sf::Color get_color_from_colormap(int c) {

        sf::Color top{ 255, 255, 255};
        
        if (c == 0){
             top = sf::Color{ 255, 0, 0};
        }else if (c== 1){
             top = sf::Color{ 155, 0, 0 };
        }else if (c == 2){
             top = sf::Color{ 0, 255, 0 };
        }else if (c == 3){
             top = sf::Color{ 0, 100, 0 };
        }else if (c == 4){
             top = sf::Color{ 0, 0, 255};
        }else if (c == 5){
             top = sf::Color{ 0, 0, 155};
        }else if (c == 6){
             top = sf::Color{ 255, 255, 0 };
        }else if (c == 7){
             top = sf::Color{ 155, 155, 0};
        }else if (c == 8){
             top = sf::Color{ 155, 155, 140};
        }else{
             top = sf::Color{ 255, 255, 255, 100 };
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
        player_z = 0;
        player_a = 0;
        player_l = 0;
    }

    //Every frame stuff  

    void tick(float currentTime) {     

        player_class::handle_player_input(currentTime);      //hadles player input from player.cpp
    }

    void draw_game(sf::RenderWindow* window) {      // this function is called every draw call (dont over use it) (you can use all sfml (use [->] instead of [.] after window variable) draw functions here)

        //for example:

        /* uncomment to draw 3 color triangle at specified position
        sf::VertexArray tris{sf::PrimitiveType::Triangles, 3};
        tris[0].position = {100,100};
        tris[1].position = {200,100};
        tris[2].position = {150,175};
        tris[0].color = sf::Color(255,0,0);
        tris[1].color = sf::Color(0,255,0);
        tris[2].color = sf::Color(0,0,255);
        window->draw(tris);
        */
    }
                   