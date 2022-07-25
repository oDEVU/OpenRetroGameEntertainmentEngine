#include <raylib.h>
#include <rlgl.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <stdio.h>                      // BLOAT    (    but i dont want to clear it :)    )
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
//#include "functions.hpp"
//#include <iostream>


    //Game things

    #include "game.cpp"

    //Engine things

    #include "engine/render.hpp"

    //--------------

int main()
{
    //int result = mkdir("/home/test.txt", 0777);

    //SaveFileText("result.txt", unconstchar(TextFormat("%i",result)));  

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

    InitWindow(screenWidth, screenHeight, "O.R.G.Y");

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

    // Game loop

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

            //player moving

        if (IsKeyDown(KEY_RIGHT)){
            P.a += 50*(GetFrameTime());
            if (P.a > 359){
                P.a -= 360;
            }
        }
        if (IsKeyDown(KEY_LEFT)){
            P.a -= 50*(GetFrameTime());
            if (P.a < 0){
                P.a += 360;
            }
        }

        int dx=sin(torad(P.a))*100;
        int dy=cos(torad(P.a))*100;

        if (IsKeyDown(KEY_W)){
            P.x+=dx*GetFrameTime(); P.y+=dy*GetFrameTime();
        }
        if (IsKeyDown(KEY_S)){
            P.x-=dx*GetFrameTime(); P.y-=dy*GetFrameTime();
        }
        if (IsKeyDown(KEY_D)){
            P.x+=dy*GetFrameTime(); P.y-=dx*GetFrameTime();
        }
        if (IsKeyDown(KEY_A)){
            P.x-=dy*GetFrameTime(); P.y+=dx*GetFrameTime();
        }

        if (IsKeyDown(KEY_LEFT_SHIFT)){
            P.z -= 100*GetFrameTime();
        }
        if (IsKeyDown(KEY_LEFT_CONTROL)){
            P.z += 100*GetFrameTime();
        }

        if (IsKeyDown(KEY_UP)){
            P.l += 100*GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN)){
            P.l -= 100*GetFrameTime();
        }

            //Fps related

        Color fps_color{ 255, 255, 255, 255 };
        
        if (GetFPS() < 15){
             fps_color = Color{ 155, 0, 0, 255 };
        }else if (GetFPS() < 30){
             fps_color = Color{ 255, 0, 0, 255 };
        }else if (GetFPS() < 60){
             fps_color = Color{ 255, 255, 0, 255 };
        }else if (GetFPS() < 120){
             fps_color = Color{ 0, 255, 0, 255 };
        }else if (GetFPS() >= 120){
             fps_color = Color{ 0, 255, 200, 255 };
        }

            //Window state
        if (IsWindowResized()){
            int new_screen_x = GetScreenWidth();
            int new_screen_y = GetScreenHeight();

            //char* sett(TextFormat("%i/%i", new_screen_x, new_screen_y))
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

            ClearBackground(BLACK);

            Draw3D();

            //Debug

            if (show_debug == true){
                DrawText("Open Retro Game Yngine - Test build", 5, 5, 10, YELLOW);
                DrawText("Using:", 5, 35, 10, WHITE);
                DrawText(TextFormat("OpenGL %s", glGetString( GL_VERSION )), 5, 50, 10, LIGHTGRAY);
                DrawText(TextFormat("GLSL %s", glGetString( GL_SHADING_LANGUAGE_VERSION )), 5, 65, 10, LIGHTGRAY);
                DrawText(TextFormat("%s", glGetString(GL_RENDERER)), 5, 80, 10, LIGHTGRAY);
                DrawText("Player:", 5, 110, 10, WHITE);
                DrawText(TextFormat("player position: %f, %f, %f", P.x, P.z, P.y), 5, 125, 10, LIGHTGRAY);
                //DrawText(TextFormat("dx and dy: %f, %f", dx, dy), 5, 130, 10, LIGHTGRAY);
                if (vsync == true){
                    DrawText(TextFormat("FPS: %i [VSYNC]", GetFPS()), 5, 155, 10, fps_color);
                }else{
                    DrawText(TextFormat("FPS: %i", GetFPS()), 5, 155, 10, fps_color);
                }
            }else {
                DrawText("Open Retro Game Yngine - Test build", 5, 5, 10, YELLOW);
                if (vsync == true){
                    DrawText(TextFormat("FPS: %i [VSYNC]", GetFPS()), 5, 20, 10, fps_color);
                }else{
                    DrawText(TextFormat("FPS: %i", GetFPS()), 5, 20, 10, fps_color);
                }
            }

            //DrawTextureQuad(bricks, Vector2{7,5}, Vector2{66,9}, Rectangle{40,150,60,90}, Color{255,255,255,255});
            //DrawTexturePoly(bricks, (Vector2){ 200,200 },positions, texcoords, MAX_POINTS, WHITE);
            //DrawTexture(bricks, 99, 99, WHITE);
            
            //DrawFPS(5, 17);
            //GetFPS(void)

            //Draw3D();

            // void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);  
            // void DrawPixel(x,y,color); 

            draw_game();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Destruction of window
    Unload();
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
