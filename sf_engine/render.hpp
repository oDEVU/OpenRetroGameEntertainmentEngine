#pragma once

#include <math.h>
#include <SFML/Graphics.hpp>
#include "SelbaWard/ElasticSprite.hpp"
#include "poly.hpp"

double   pos_celing[8];
int     celing_counter=0;

namespace render_class {
    
//#include "game.cpp"
void clip_behind_camera(double *x1,double *y1, double *z1, double x2,double y2,double z2){
    double da=*y1;
    double db=y2;
    //double d=da-db;
    //if (d==0){d=1;};
    double s = da / (da-db);
    *x1 = *x1 + s*(x2-(*x1));
    *y1 = *y1 + s*(y2-(*y1)); if(*y1<1){*y1=1;};
    *z1 = *z1 + s*(z2-(*z1)); //if(*z1<=0){*z1=1;};
} 
void shade_wall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s, int t, int txt, int w, sf::RenderWindow* window, int l, int loop){
    if(w%2==0){
    if(x2 > 0 || x1 < window->getSize().x){
    int x,y;

    //if(x2 < 0 || x1 > window->getSize().x){

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
    if(x1>(window->getSize().x-1)){x1=(window->getSize().x-1);}
    if(x2>(window->getSize().x-1)){x2=(window->getSize().x-1);}


    if(loop==1){
        if(l==0){
        if(x2>x1){
            sf::Color wall_color{ 0, 0, 0, 55 };
        
            //wall_color = get_color_from_colormap(c);

            int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
            int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
            int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
            int ey2 = dyt*(bx2-xs+0.5)/dx+t1;
            poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wall_color, window);
        }
        }else{
        if(x2<x1){
            sf::Color wall_color{ 0, 0, 0, 55 };
        
            //wall_color = get_color_from_colormap(c);

            int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
            int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
            int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
            int ey2 = dyt*(bx2-xs+0.5)/dx+t1;
            poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wall_color, window);
        }
        }
    }}}
}

void draw_wall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s, int t, int txt, int w, sf::RenderWindow* window, int l, int loop){
    int x,y;

    if(x2 > 0 || x1 < window->getSize().x){

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
    if(x1>(window->getSize().x-1)){x1=(window->getSize().x-1);}
    if(x2>(window->getSize().x-1)){x2=(window->getSize().x-1);}


    //if(loop==0){
    if(loop==1){
    if(t==0){
        if(l==0){
        if(x2>x1){
            sf::Color wall_color{ 255, 255, 255 };
        
            wall_color = get_color_from_colormap(c);

            int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
            int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
            int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
            int ey2 = dyt*(bx2-xs+0.5)/dx+t1;
            poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wall_color, window);
            if(render_polys_lines == 1){
                poly::draw_poly_lines( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, window);
            }
        }
        }else{
        if(x2<x1){
            sf::Color wall_color{ 255, 255, 255 };
        
            wall_color = get_color_from_colormap(c);

            int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
            int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
            int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
            int ey2 = dyt*(bx2-xs+0.5)/dx+t1;
            poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wall_color, window);
            if(render_polys_lines == 1){
                poly::draw_poly_lines( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, window);
            }
        }
        }
    }else{
        if(l==0){
        if(x2>x1){
            int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
            int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
            int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
            int ey2 = dyt*(bx2-xs+0.5)/dx+t1;
            std::string txt_path = get_texture_from_texturemap(txt);
            poly::draw_poly_txt_correct( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, txt_path, window);
            if(render_polys_lines == 1){
                poly::draw_poly_lines( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, window);
            }
        }
        }else{
        if(x2<x1){
            int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
            int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
            int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
            int ey2 = dyt*(bx2-xs+0.5)/dx+t1;
            std::string txt_path = get_texture_from_texturemap(txt);
            poly::draw_poly_txt_correct( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, txt_path, window);
            if(render_polys_lines == 1){
                poly::draw_poly_lines( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, window);
            }
        }
        }
    
    }
    }
        for(int i = x1; i<x2; i++){
        int y1 = dyb*(i-xs+0.5)/dx+b1;
        int y2 = dyt*(i-xs+0.5)/dx+t1;

        int by1 = y1;
        int by2 = y2;

        if(y1<1){y1=1;}
        if(y2<1){y2=1;}
        if(y1>(window->getSize().y-1)){y1=(window->getSize().y-1);}
        if(y2>(window->getSize().y-1)){y2=(window->getSize().y-1);}

        if(S[s].surface == 1){S[s].surf[i]=y1; continue;}
        if(S[s].surface == 2){S[s].surf[i]=y2; continue;}

        if(S[s].surface == -1){
                //DrawLine(i, S[s].surf[i], i, y1, bottom);
       sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(i, S[s].surf[i])),
            sf::Vertex(sf::Vector2f(i, y1))
        };

        line[0].color = get_color_from_colormap(S[s].c2);
        line[1].color = get_color_from_colormap(S[s].c2);
        window->draw(line, 2, sf::Lines);
        };

        if(S[s].surface == -2){
                //DrawLine(i, y2, i, S[s].surf[i], top); 
       sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(i, y2)),
            sf::Vertex(sf::Vector2f(i, S[s].surf[i]))
        };

        line[0].color = get_color_from_colormap(S[s].c1);
        line[1].color = get_color_from_colormap(S[s].c1);
        window->draw(line, 2, sf::Lines);
        };
        }
   //}
    }
}


double dist(double x1,double y1, double x2, double y2){
    double distance = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    return distance;
}

void draw_3d(sf::RenderWindow* window){
     double wx[4],wy[4],wz[4];
     int s,w;
     double CS=cos(glogal_functions::torad(Cam.a)), SN=sin(glogal_functions::torad(Cam.a));

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

        if(S[s].flip == 0){
        if(Cam.z<S[s].z1){S[s].surface=1;}
        else if (Cam.z>S[s].z2){S[s].surface=2;}  //Why this isnt fucking working !!!!!!!!!
        else {S[s].surface=0;}
        }else{
        if(Cam.z<S[s].z1){S[s].surface=2;}
        else if (Cam.z>S[s].z2){S[s].surface=1;}
        else {S[s].surface=0;}
        }

        for(int loop=0; loop < 2; loop++){
            for(w=S[s].ws;w<S[s].we;w++){

                 int x1=W[w].x1-Cam.x, y1=W[w].y1-Cam.y;
                 int x2=W[w].x2-Cam.x, y2=W[w].y2-Cam.y;

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

                wz[0]=S[s].z1-Cam.z+((Cam.l*wy[0])/32.0);
                wz[1]=S[s].z1-Cam.z+((Cam.l*wy[1])/32.0);
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
                wx[0]=wx[0]*222/wy[0]+(window->getSize().x/2); wy[0]=wz[0]*222/wy[0]+(window->getSize().y/2); 
                wx[1]=wx[1]*222/wy[1]+(window->getSize().x/2); wy[1]=wz[1]*222/wy[1]+(window->getSize().y/2);  
                wx[2]=wx[2]*222/wy[2]+(window->getSize().x/2); wy[2]=wz[2]*222/wy[2]+(window->getSize().y/2); 
                wx[3]=wx[3]*222/wy[3]+(window->getSize().x/2); wy[3]=wz[3]*222/wy[3]+(window->getSize().y/2); 

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

                draw_wall(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],W[w].c, s , W[w].t, W[w].txt, w, window, S[s].flip,loop);
                shade_wall(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],W[w].c, s , W[w].t, W[w].txt, w, window, S[s].flip,loop);
                
            
            }
            S[s].d/=(S[s].we-S[s].ws);
            S[s].surface*=-1;
        }
    }
    }
}



