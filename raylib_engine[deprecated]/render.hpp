#pragma once

#include <raylib.h>
#include <math.h>
//#include "structures.hpp"

namespace render_class {
    
//#include "game.cpp"
void clip_behind_camera(float *x1,float *y1, float *z1, float x2,float y2,float z2){
    float da=*y1;
    float db=y2;
    //float d=da-db;
    //if (d==0){d=1;};
    float s = da / (da-db);
    *x1 = *x1 + s*(x2-(*x1));
    *y1 = *y1 + s*(y2-(*y1)); if(*y1<1){*y1=1;};
    *z1 = *z1 + s*(z2-(*z1)); //if(*z1<=0){*z1=1;};
} 

void wall_shading(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s, int t, int txt, int w){

    t = 0;
    txt = 0;

    int x,y;

    int dyb = b2-b1;
    int dyt = t2-t1;
    int dx = x2-x1;
    if(dx==0){
        dx=1;
    }
    int xs=x1;

    if(x1<1){x1=1;}
    if(x2<1){x2=1;}
    if(x1>(GetScreenWidth()-1)){x1=(GetScreenWidth()-1);}
    if(x2>(GetScreenWidth()-1)){x2=(GetScreenWidth()-1);}

    for(int i=x1;i<x2;i++){
        int y1 = dyb*(i-xs+0.5)/dx+b1;
        int y2 = dyt*(i-xs+0.5)/dx+t1;

        if(y1<1){y1=1;}
        if(y2<1){y2=1;}
        if(y1>(GetScreenHeight()-1)){y1=(GetScreenHeight()-1);}
        if(y2>(GetScreenHeight()-1)){y2=(GetScreenHeight()-1);}

        if((w%2)==0){

        DrawLine(i, y1, i, y2, Color{0,0,0,50});  // shading on walls
        }

    }
}

void render_fog(){
    //TODO
}

void draw_wall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s, int t, int txt, int w){
    int x,y;

    //DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color); 

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

    if(t==0){

        Color wall_color{ 255, 255, 255, 255 };
        
        wall_color = get_color_from_colormap(c);

        int sy1 = dyb*(x1-xs+0.5)/dx+b1;
        int sy2 = dyt*(x1-xs+0.5)/dx+t1;
        int ey1 = dyb*(x2-xs+0.5)/dx+b1;
        int ey2 = dyt*(x2-xs+0.5)/dx+t1;
        DrawTriangle(Vector2{x2,ey1}, Vector2{x1,sy2}, Vector2{x2,ey2},  wall_color); 
        DrawTriangle(Vector2{x1,sy1}, Vector2{x2,ey1}, Vector2{x2,ey2},  wall_color); 
        if(render_polys_lines == 1){
            DrawTriangleLines(Vector2{x1,sy1}, Vector2{x1,sy2}, Vector2{x2,ey2},  RED); 
            DrawTriangleLines(Vector2{x1,sy1}, Vector2{x2,ey1}, Vector2{x2,ey2},  RED); 
        }
    }

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
        
        top = get_color_from_colormap(S[s].c1);
        bottom = get_color_from_colormap(S[s].c2);

        if(S[s].surface == 1){S[s].surf[i]=y1; continue;}
        if(S[s].surface == 2){S[s].surf[i]=y2; continue;}

        Image tb = get_texture_from_texturemap(S[s].txtt);    //top and bottom texture (TO FIX)
        Image bb = get_texture_from_texturemap(S[s].txtb);

        if(S[s].surface == -1){
            if(S[s].t==0){
                DrawLine(i, S[s].surf[i], i, y1, bottom);                  //draw with color
            }else{
                for(int y=S[s].surf[i];y<y1;y++){

                    float ffy = by1 - S[s].surf[i];
                    float ffx = bx2 - bx1;
                    float ppy = (y-S[s].surf[i]) / ffy;
                    float ppx = (i-bx1) / ffx;
                    int iiy = floor(tb.height * ppy);
                    int iix = floor(tb.width * ppx);
                    Color bot = GetImageColor(tb, iix, iiy);

                    if(iiy<tb.height && iix <tb.width){                         //Draw with texture
                        DrawPixel(i,y,bot);
                    }else{
                        DrawPixel(i,y,RED);
                        if(render_debug == 1){
                            DrawText(TextFormat("! ERROR: Unable to load color from coordinates"), 5, 240, 10, RED);
                        }
                    }                                   //Draw with texture
                }
            }
            //DrawLine(i, y2, i, S[s].surf[i], WHITE);
        };

        if(S[s].surface == -2){
            if(S[s].t==0){
                DrawLine(i, y2, i, S[s].surf[i], top);                    //draw with color
            }else{
                for(int y=y2;y<S[s].surf[i];y++){

                    float ffy = S[s].surf[i] - by2;
                    float ffx = bx2 - bx1;
                    float ppy = (y-by2) / ffy;
                    float ppx = (i-bx1) / ffx;
                    int iiy = floor(bb.height * ppy);
                    int iix = floor(bb.width * ppx);
                    Color tob = GetImageColor(bb, iix, iiy);

                    if(iiy<bb.height && iix <bb.width){                         //Draw with texture
                        DrawPixel(i,y,tob);
                    }else{
                        DrawPixel(i,y,RED);
                        if(render_debug == 1){
                            DrawText(TextFormat("! ERROR: Unable to load color from coordinates"), 5, 240, 10, RED);
                        }
                    }                                
                }
            }
            //DrawLine(i, S[s].surf[i], i, y1, WHITE);
        };
            
            if(t!=0){
            Image working = get_texture_from_texturemap(txt);   ///wall texture


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
                    if(render_debug == 1){
                        DrawText(TextFormat("! ERROR: Unable to load color from coordinates"), 5, 240, 10, RED);
                    }
                }
            }
            }

        if((w%2)==0 && t!=0){
        DrawLine(i, y1, i, y2, Color{0,0,0,50});  // shading on textured walls

        }
        }
        

    }


float dist(float x1,float y1, float x2, float y2){
    float distance = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return distance;
}

void draw_3d(Camera3D camera){
     float wx[4],wy[4],wz[4];
     int s,w;
     float CS=cos(glogal_functions::torad(P.a)), SN=sin(glogal_functions::torad(P.a));

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

        for(int loop=0;loop<3;loop++){
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
                wx[0]=wx[0]*222/wy[0]+(GetScreenWidth()/2); wy[0]=wz[0]*222/wy[0]+(GetScreenHeight()/2); 
                wx[1]=wx[1]*222/wy[1]+(GetScreenWidth()/2); wy[1]=wz[1]*222/wy[1]+(GetScreenHeight()/2);  
                wx[2]=wx[2]*222/wy[2]+(GetScreenWidth()/2); wy[2]=wz[2]*222/wy[2]+(GetScreenHeight()/2); 
                wx[1]=wx[3]*222/wy[3]+(GetScreenWidth()/2); wy[3]=wz[3]*222/wy[3]+(GetScreenHeight()/2); 

                /*

                Color wall_color = get_color_from_colormap(W[w].c);

                BeginMode3D(camera);

                    //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                    //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                    //DrawGrid(10, 1.0f);
                    DrawTriangle3D((Vector3){(wx[0]/1000), (wz[0]/1000), (wy[0]/1000)}, (Vector3){(wx[1]/1000), (wz[1]/1000), (wy[1]/1000)}, (Vector3){(wx[2]/1000), (wz[2]/1000), (wy[2]/1000)}, wall_color); 
                    //DrawTriangle3D((Vector3){(wx[0]/1000), (wz[0]/1000), (wy[0]/1000)}, (Vector3){(wx[3]/1000), (wz[3]/1000), (wy[3]/1000)}, (Vector3){(wx[2]/1000), (wz[2]/1000), (wy[2]/1000)}, wall_color); 
                    //DrawTriangleStrip3D ((Vector3){wx[0], wy[0], wz[0]}, (Vector3){wx[1], wy[1], wz[1]}, (Vector3){wx[2], wy[2], wz[2]}, WHITE); 
                    

                    //DrawCube((Vector3){(wx[0]/1000), (wz[0]/1000), (wy[0]/1000)}, 2.0f, 2.0f, 2.0f, RED);

                EndMode3D();

                */

                //ClearBackground(BLACK);

                //DrawText(TextFormat("Cube pos: x:%f y:%f z:%f",(wx[0]/1000), (wz[0]/1000), (wy[0]/1000)), 5, GetScreenHeight()-35, 25, WHITE);  

    //draw to screen
    //if(wx[0]>0 && wx[0]<GetScreenWidth() && wy[0]>0 && wy[0]<GetScreenHeight()){
    //DrawPixel(wx[0],wy[0],WHITE);
    //}
    //if(wx[1]>0 && wx[1]<GetScreenWidth() && wy[1]>0 && wy[1]<GetScreenHeight()){
    //DrawPixel(wx[1],wy[1],WHITE);
    //}

                
                if(loop==2){
                    wall_shading(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],W[w].c, s , W[w].t, W[w].txt, w);
                }else{
                    draw_wall(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],W[w].c, s , W[w].t, W[w].txt, w);
                }
                
            
            }
            S[s].d/=(S[s].we-S[s].ws);
            S[s].surface*=-1;
        }
    }
}

}