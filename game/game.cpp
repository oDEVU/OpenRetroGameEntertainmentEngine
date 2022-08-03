//hi and hello C:
#include "player.hpp"

#define render_debug 1    // replace 1 with 0 to completly hide any debug info (engine name.fps,errors,etc) 
#define render_polys_lines 0  //to visualize polys rendered by render.hpp [GLITCHY BUT USEFULL]
#define window_title "O.R.G.Y - DEMO_GAME"


const int size_of_dirs = 2;      //Specify how many folder you will be creating

const char* dirs[size_of_dirs] {   
    "/screenshots",                                 //Add here any dir you are wirking with (start path is executable path)
    "/game/textures"            
};


     //Color Map ----------------------------------------------
    sf::Color color_map[]{
        sf::Color(255,255,255,100),
        sf::Color(255,255,255),
        sf::Color(255,0,0),
        sf::Color(100,0,0),
        sf::Color(0,255,0),
        sf::Color(0,100,0),
        sf::Color(0,0,255),
        sf::Color(0,0,100),
        sf::Color(0,255,255),
        sf::Color(0,100,100),
        sf::Color(255,255,0),
        sf::Color(100,100,0),
        sf::Color(255,0,255),
        sf::Color(100,0,100),
        sf::Color(155,155,140),
        sf::Color(22,22,22),
    };

    sf::Color get_color_from_colormap(int c) {                      //This function must be here !!! dont delete it !!!

        sf::Color top{ 255, 255, 255};
        int len = sizeof(color_map)/sizeof(color_map[0]);

        if(c <= len){
        top = color_map[c];
        }else{
        top = color_map[0];
        }

        return top;
    }

    //Textures --------------------------------------------------
    std::string textures[]{
        "game/textures/bricks.png",
        "game/textures/grass.png",
        "game/textures/stone.png",
        "sf_engine/textures/tux.png"
    };  

    //Texture Map ----------------------------------------------  This function must be here !!! dont delete it !!!


    std::string get_texture_from_texturemap(int txt) {
        int len = sizeof(textures)/sizeof(textures[0]);
        std::string texture;

        if(txt-1 <= len){
        texture = textures[txt-1];
        }

        return texture;
    }

    // map loader -----------------------------------------------

    int num_sec = 6;
    int num_wall = 24; 


    int load_sectors[] =
    { //ws,we,z1,z2,c1,c2,t,txtt,txtb,flip
        0,4,0,40,2,2,1,       //sector 1
        4,8,0,40,4,4,0,       //sector 2
        8,12,-20,20,14,14,0,    //sector 3
        12,16,20,60,10,5,0,   //sector 4
        16,21,10,30,0,0,0,     //sector 5
        21,24,-10,50,12,12,0,     //sector 6
    };

    int load_walls[] =
    {  //x1,y1,x2,y2,color,is textured,texture,     //Count textures from 1 (to use textures[0] use 1)
        0,0,32,0,2,0,0,     //sector 1 * 4 walls
        32,0,32,32,2,0,0,
        32,32,0,32,2,0,0,
        0,32,0,0,2,0,0,

        64,0,96,0,4,0,0,    //sector 2 * 4 walls
        96,0,96,32,4,0,0,
        96,32,64,32,4,0,0,
        64,32,64,0,4,0,0,

        64,64,96,64,99,3,3,  //sector 3 * 4 walls
        96,64,96,96,99,3,3,
        96,96,64,96,99,3,3,
        64,96,64,64,99,3,3,

        0,64,32,64,69,1,1,   //sector 4 * 4 walls
        32,64,32,96,69,1,1,
        32,96,0,96,69,1,1,
        0,96,0,64,69,1,1,

        0,128,32,128,0,0,0,   //sector 5 * 5 walls
        32,128,32,160,0,0,0,
        32,160,0,160,0,0,0,
        0,160,-16,144,0,0,0,
        -16,144,0,128,0,0,0,

        64,144,96,128,12,0,0,  //sector 6 * 3 walls
        96,128,96,160,12,0,0,
        96,160,64,144,12,0,0,
    }; 

    //Init stuff

    void init() {           // this function is called at start of the program

    }

    //Player spawn position
        int player_x = -16;     //Statick info
        int player_y = 0;
        int player_z = -50;
        int player_a = 0;
        int player_l = 0;

    //Every frame stuff  

    void tick(double currentTime) {     

        player_class::handle_player_input(currentTime);      //hadles player input from player.cpp
    }

    void event(sf::Event* e){                           //Used to handle single clicks (look sfml website)

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
                   