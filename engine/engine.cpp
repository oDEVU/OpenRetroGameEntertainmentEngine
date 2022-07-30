// This is engine the main rendering and logig part. You compile it with the game to run it.


#include <raylib.h>
#include <rlgl.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <stdio.h>                      // BLOAT    (  but i dont want to clear it C:  ) 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"                 // Required for GUI controls
//#include "functions.hpp"
//#include <iostream>

    //Multi used things    --------------------    Used in game.cpp and engine
    
    Image temp      = LoadImage("enigne/textures/temp.png"); 
    #include "functions.hpp" 
    #include "../game/structures.hpp"

    //Game things

    #include "../game/game.cpp"

    //Engine things        --------------------    Used only in  engine

    #include "render.hpp"
    #include "debug.hpp"

    //--------------

int main()
{
    //SetWindowIcon(icon);

    for(int i=0;i<size_of_dirs;i++){
    const char* engine_path = GetWorkingDirectory();
    const char* dir = dirs[i];

    std::string buf(engine_path);
    buf.append(dir);

    std::filesystem::create_directories(buf);
    }  


    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    int screenWidth = 800;
    int screenHeight = 600;

    bool show_debug = true;
    bool vsync = false;

    int screens_num = 0;

    if (FileExists("screenshots/num.cfg")){
        screens_num = atoi(LoadFileText("screenshots/num.cfg"));
    }

    if (FileExists("configs/resolutionx.cfg") && FileExists("configs/resolutiony.cfg")){
    char* resolutin_x = LoadFileText("configs/resolutionx.cfg");
    char* resolutin_y = LoadFileText("configs/resolutiony.cfg");

    screenWidth = atoi(resolutin_x);
    screenHeight = atoi(resolutin_y);
    }

    if (LoadFileText("configs/debug.cfg") != NULL){
        show_debug = true;
    }else{
        show_debug = false;
    }

    if (LoadFileText("configs/vsync.cfg") != NULL){
        vsync = true;
    }else{
        vsync = false;
    }


    // INIT -----------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, window_title);

    SetWindowIcon(icon);

    init();

            //create player

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
        S[s].t=load_sectors[v1+6];
        S[s].txtt=load_sectors[v1+7];
        S[s].txtb=load_sectors[v1+8];
        v1+=9;
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

    // Game loop    ------------------------------------------------------------------------

    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        tick();

            //KeyInputs
        if (IsKeyPressed(KEY_TAB)){
            TakeScreenshot(unconstchar(TextFormat("screenshots/screen%i.png", screens_num)));
            screens_num++;
            SaveFileText("screenshots/num.cfg", unconstchar(TextFormat("%i", screens_num)));
        }


        if (IsKeyPressed(KEY_F1)){
            show_debug = !show_debug;

            if (show_debug == true){
                SaveFileText("configs/debug.cfg", unconstchar(TextFormat("debug")));
            }else{
               SaveFileText("configs/debug.cfg", unconstchar(TextFormat("")));
            }
        }

        if (IsKeyPressed(KEY_F2)){
            vsync = !vsync;

            if (vsync == true){
                SaveFileText("configs/vsync.cfg", unconstchar(TextFormat("on")));
            }else{
                SaveFileText("configs/vsync.cfg", unconstchar(TextFormat("")));
            }
        }

            //Window state
        if (IsWindowResized()){
            int new_screen_x = GetScreenWidth();
            int new_screen_y = GetScreenHeight();

            SaveFileText("configs/resolutionx.cfg", unconstchar(TextFormat("%i", new_screen_x)));
            SaveFileText("configs/resolutiony.cfg", unconstchar(TextFormat("%i", new_screen_y)));
        }

        if (vsync == true){
            SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
        }else{
            SetTargetFPS(0);
        }

        //----------------------------------------------------------------------------------

        // DrawCall
        //----------------------------------------------------------------------------------
        BeginDrawing();

            //Rendering

            ClearBackground(BLACK);

            draw_3d();

            //Debug

            if(render_debug == 1){
                draw_debug(show_debug,vsync);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Destruction of window
    Unload(); 
    UnloadImage(temp); 
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
