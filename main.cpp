
#include "raylib.h"
#include "rlgl.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//#include <iostream>


    //Game things

    Image bricks = LoadImage("game/textures/bricks.png"); 
    Image grass = LoadImage("game/textures/grass.png"); 
    Image stone = LoadImage("game/textures/stone.png"); 

    int num_sec = 4;
    int num_wall = 16;  

    //--------------


char* unconstchar(const char* s) {
    if(!s)
      return NULL;
    int i;
    char* res = NULL;
    res = (char*) malloc(strlen(s)+1);
    if(!res){
        fprintf(stderr, "Memory Allocation Failed! Exiting...\n");
        exit(EXIT_FAILURE);
    } else{
        for (i = 0; s[i] != '\0'; i++) {
            res[i] = s[i];
        }
        res[i] = '\0';
        return res;
    }
}

float torad(float x){
    float rad = (x * M_PI) / 180;
    return rad;
}

typedef struct{
    float x,y,z;  //Position
    float a;      // angle l-r
    float l;      // angle u-d
}player; player P;

typedef struct{
    float x1,y1;
    float x2,y2;
    int c;
    bool t;
    int txt;
}walls; walls W[64];

typedef struct{
    float ws,we;
    float z1,z2;
    float x,y;
    float d;
    int c1,c2;
    bool t;
    int txtt;
    int txtb;
    int surf[32000];
    int surface;
}sectors; sectors S[64];

void clip_behind_camera(float *x1,float *y1, float *z1, float x2,float y2,float z2){
    float da=*y1;
    float db=y2;
    //float d=da-db;
    //if (d==0){d=1;};
    float s = da / (da-db);
    *x1 = *x1 + s*(x2-(*x1));
    *y1 = *y1 + s*(y2-(*y1)); if(*y1==0){*y1=1;};
    *z1 = *z1 + s*(z2-(*z1)); //if(*z1<=0){*z1=1;};
}

void draw_wall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s, int t, int txt){
    int x,y;

    int dyb = b2-b1;
    int dyt = t2-t1;
    int dx = x2-x1;
    if(dx==0){
        dx=1;
    }
    int xs=x1;

    int bx1 = x1;
    int bx2 = x2;

    if(x1<1){x1=1;}
    if(x2<1){x2=1;}
    if(x1>(GetScreenWidth()-1)){x1=(GetScreenWidth()-1);}
    if(x2>(GetScreenWidth()-1)){x2=(GetScreenWidth()-1);}

    for(int i=x1;i<x2;i++){
        int y1 = dyb*(i-xs+0.5)/dx+b1;
        int y2 = dyt*(i-xs+0.5)/dx+t1;

        int by1 = y1;
        int by2 = y2;

        if(y1<1){y1=1;}
        if(y2<1){y2=1;}
        if(y1>(GetScreenHeight()-1)){y1=(GetScreenHeight()-1);}
        if(y2>(GetScreenHeight()-1)){y2=(GetScreenHeight()-1);}

        //DrawPixel(i,y1,WHITE);
        //DrawPixel(i,y2,WHITE);
        //for(int y=y1;y<y2;y++){
        //    DrawPixel(i,y,WHITE);
        //}

        Color top{ 255, 255, 255, 255 };
        Color bottom{ 255, 255, 255, 255 };
        
        if (S[s].c1 == 0){
             top = Color{ 255, 0, 0, 255 };
        }else if (S[s].c1 == 1){
             top = Color{ 155, 0, 0, 255 };
        }else if (S[s].c1 == 2){
             top = Color{ 0, 255, 0, 255 };
        }else if (S[s].c1== 3){
             top = Color{ 0, 155, 0, 255 };
        }else if (S[s].c1 == 4){
             top = Color{ 0, 0, 255, 255 };
        }else if (S[s].c1 == 5){
             top = Color{ 0, 0, 155, 255 };
        }else if (S[s].c1 == 6){
             top = Color{ 255, 255, 0, 255 };
        }else if (S[s].c1 == 7){
             top = Color{ 155, 155, 0, 255 };
        }else{
             top = Color{ 255, 255, 255, 100 };
        }
        
        if (S[s].c2 == 0){
             bottom = Color{ 255, 0, 0, 255 };
        }else if (S[s].c2 == 1){
             bottom = Color{ 155, 0, 0, 255 };
        }else if (S[s].c2 == 2){
             bottom = Color{ 0, 255, 0, 255 };
        }else if (S[s].c2 == 3){
             bottom = Color{ 0, 155, 0, 255 };
        }else if (S[s].c2 == 4){
             bottom = Color{ 0, 0, 255, 255 };
        }else if (S[s].c2 == 5){
             bottom = Color{ 0, 0, 155, 255 };
        }else if (S[s].c2 == 6){
             bottom = Color{ 255, 255, 0, 255 };
        }else if (S[s].c2 == 7){
             bottom = Color{ 155, 155, 0, 255 };
        }else{
             bottom = Color{ 255, 255, 255, 100 };
        }

        if(S[s].surface == 1){S[s].surf[i]=y1; continue;}
        if(S[s].surface == 2){S[s].surf[i]=y2; continue;}



        Image tb = bricks;

        if(S[s].txtt == 1){
            tb = bricks;
        }else if(S[s].txtt == 2){
            tb = grass;
        }else if(S[s].txtt == 3){
            tb = stone;
        }

        Image bb = bricks;

        if(S[s].txtb == 1){
            bb = bricks;
        }else if(S[s].txtb == 2){
            bb = grass;
        }else if(S[s].txtb == 3){
            bb = stone;
        }

        if(S[s].surface == -1){
            if(S[s].t==0){
                DrawLine(i, S[s].surf[i], i, y1, bottom);
            }else{
                for(int y=S[s].surf[i];y<y1;y++){

                    float ffy = by1 - S[s].surf[i];
                    float ffx = bx2 - bx1;
                    float ppy = (y-S[s].surf[i]) / ffy;
                    float ppx = (i-bx1) / ffx;
                    int iiy = floor(tb.height * ppy);
                    int iix = floor(tb.width * ppx);
                    Color bot = GetImageColor(tb, iix, iiy);

                    DrawPixel(i,y,bot);
                }
            }
        };

        if(S[s].surface == -2){
            if(S[s].t==0){
                DrawLine(i, y2, i, S[s].surf[i], top);
            }else{
                for(int y=y2;y<S[s].surf[i];y++){

                    float ffy = S[s].surf[i] - by2;
                    float ffx = bx2 - bx1;
                    float ppy = (y-by2) / ffy;
                    float ppx = (i-bx1) / ffx;
                    int iiy = floor(bb.height * ppy);
                    int iix = floor(bb.width * ppx);
                    Color tob = GetImageColor(bb, iix, iiy);

                    DrawPixel(i,y,tob);
                }
            }
        };

        if(t==0){

        Color wall_color{ 255, 255, 255, 255 };
        
        if (c == 0){
             wall_color = Color{ 255, 0, 0, 255 };
        }else if (c == 1){
             wall_color = Color{ 155, 0, 0, 255 };
        }else if (c == 2){
             wall_color = Color{ 0, 255, 0, 255 };
        }else if (c == 3){
             wall_color = Color{ 0, 155, 0, 255 };
        }else if (c == 4){
             wall_color = Color{ 0, 0, 255, 255 };
        }else if (c == 5){
             wall_color = Color{ 0, 0, 155, 255 };
        }else if (c == 6){
             wall_color = Color{ 255, 255, 0, 255 };
        }else if (c == 7){
             wall_color = Color{ 155, 155, 0, 255 };
        }else{
             wall_color = Color{ 255, 255, 255, 100 };
        }

        DrawLine(i, y1, i, y2, wall_color);

        }else if(t==1){

            Image working = bricks;

            if(txt == 1){
                working = bricks;
            }else if(txt == 2){
                working = grass;
            }else if(txt == 3){
                working = stone;
            }

        for(int y=y1;y<y2;y++){

            float fy = by2 - by1;
            float fx = bx2 - bx1;
            float py = (y-by1) / fy;
            float px = (i-bx1) / fx;
            int iy = floor(working.height * py);
            int ix = floor(working.width * px);
            if(iy<working.height && ix <working.width){
                Color col = GetImageColor(working, ix, iy);
                DrawPixel(i,y,col);
            }else{
                DrawPixel(i,y,RED);
                DrawText(TextFormat("! ERROR: Unable to load color from coordinates"), 5, 240, 10, RED);
            }
        }
        //DrawLine(i, y1, i, y2, WHITE);
        }

    }
}

float dist(float x1,float y1, float x2, float y2){
    float distance = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return distance;
}

void Draw3D(){
     float wx[4],wy[4],wz[4];
     int s,w;
     float CS=cos(torad(P.a)), SN=sin(torad(P.a));

    for(s=0;s<num_sec-1;s++){
        for(w=0;w<num_sec-s-1;w++){
            if(S[w].d<S[w+1].d){
                sectors st=S[w];
                S[w]=S[w+1];
                S[w+1]=st;
            }
        }
    }

     //sectors
     
     for(s=0;s<num_sec;s++){
        S[s].d=0;

        if(P.z<S[s].z1){S[s].surface=1;}
        else if (P.z>S[s].z2){S[s].surface=2;}
        else {S[s].surface=0;}

        for(int loop=0;loop<2;loop++){
            for(w=S[s].ws;w<S[s].we;w++){

                 int x1=W[w].x1-P.x, y1=W[w].y1-P.y;
                 int x2=W[w].x2-P.x, y2=W[w].y2-P.y;

                 if(loop==0){int swp=x1; x1=x2;x2=swp;swp=y1;y1=y2;y2=swp;}

    // if(x1 == 0){x1=1;};
    // if(x2 == 0){x2=1;};
    // if(y1 == 0){y1=1;};
    // if(y2 == 0){y2=1;};

                wx[0]=x1*CS-y1*SN;
                wx[1]=x2*CS-y2*SN;
                wx[2]=wx[0];
                wx[3]=wx[1];

                wy[0]=y1*CS+x1*SN;
                wy[1]=y2*CS+x2*SN;
                wy[2]=wy[0];
                wy[3]=wy[1];

                wz[0]=S[s].z1-P.z+((P.l*wy[0])/32.0);
                wz[1]=S[s].z1-P.z+((P.l*wy[1])/32.0);
                wz[2]=wz[0]+S[s].z2;
                wz[3]=wz[1]+S[s].z2;
                S[s].d+=dist(0,0,(wx[0]+wx[1])/2,(wy[0]+wy[1])/2);

                if(wy[0]<=0 && wy[1]<=0){continue;};

                if(wy[0]<=0){
                    clip_behind_camera(&wx[0],&wy[0],&wz[0],wx[1],wy[1],wz[1]);
                    clip_behind_camera(&wx[2],&wy[2],&wz[2],wx[3],wy[3],wz[3]);
                }

                if(wy[1]<=0){
                    clip_behind_camera(&wx[1],&wy[1],&wz[1],wx[0],wy[0],wz[0]);
                    clip_behind_camera(&wx[3],&wy[3],&wz[3],wx[2],wy[2],wz[2]);
                }

    //screen perspective stuff
                wx[0]=wx[0]*200/wy[0]+(GetScreenWidth()/2); wy[0]=wz[0]*200/wy[0]+(GetScreenHeight()/2); 
                wx[1]=wx[1]*200/wy[1]+(GetScreenWidth()/2); wy[1]=wz[1]*200/wy[1]+(GetScreenHeight()/2);  
                wx[2]=wx[2]*200/wy[2]+(GetScreenWidth()/2); wy[2]=wz[2]*200/wy[2]+(GetScreenHeight()/2); 
                wx[1]=wx[3]*200/wy[3]+(GetScreenWidth()/2); wy[3]=wz[3]*200/wy[3]+(GetScreenHeight()/2); 

    //draw to screen
    //if(wx[0]>0 && wx[0]<GetScreenWidth() && wy[0]>0 && wy[0]<GetScreenHeight()){
    //DrawPixel(wx[0],wy[0],WHITE);
    //}
    //if(wx[1]>0 && wx[1]<GetScreenWidth() && wy[1]>0 && wy[1]<GetScreenHeight()){
    //DrawPixel(wx[1],wy[1],WHITE);
    //}

                draw_wall(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],W[w].c, s , W[w].t, W[w].txt);
            
            }
            S[s].d/=(S[s].we-S[s].ws);
            S[s].surface*=-1;
        }
    }
}

int main()
{
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

    // map loader

    int load_sectors[] =
    { //ws,we,z1,z2,c1,c2,t,txtt,txtb
        0,4,0,40,1,0,0,0,0,       //sector 1
        4,8,0,40,3,2,0,0,0,       //sector 2
        8,12,0,40,99,99,0,0,0,    //sector 3
        12,16,0,40,99,99,1,2,3,   //sector 4
    };

    int load_walls[] =
    {  //x1,y1,x2,y2,color,is textured,texture,
        0,0,32,0,0,0,0,     //sector 1 * 4 walls
        32,0,32,32,1,0,0,
        32,32,0,32,0,0,0,
        0,32,0,0,1,0,0,

        64,0,96,0,2,0,0,    //sector 2 * 4 walls
        96,0,96,32,3,0,0,
        96,32,64,32,2,0,0,
        64,32,64,0,3,0,0,

        64,64,96,64,99,0,0,  //sector 3 * 4 walls
        96,64,96,96,99,0,0,
        96,96,64,96,99,0,0,
        64,96,64,64,99,0,0,

        0,64,32,64,69,1,1,   //sector 4 * 4 walls
        32,64,32,96,69,1,1,
        32,96,0,96,69,1,1,
        0,96,0,64,69,1,1,
    };


    // INIT -----------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "O.R.G.Y");

            //create player
        
    P.x = 0; P.y = 0; P.z = 10; P.a = 0; P.l = 0;

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
            SaveFileText("configs/vsync.cfg", unconstchar(TextFormat("on")));
        }else{
            SetTargetFPS(0);
            SaveFileText("configs/vsync.cfg", unconstchar(TextFormat("")));
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

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // Destruction of window
    UnloadImage(bricks);   
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
