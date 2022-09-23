#pragma oncemap->

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>
#include "map.hpp"
#include "poly.hpp"
#include "static.hpp"
#include "engine_math.hpp"
#include "camera.hpp"

namespace orgy
{
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

    //Do stuff
    double dist(double x1,double y1, double x2, double y2){
        double distance = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
        return distance;
    }

    void draw_wall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s, int t, wall wll, int w, sf::RenderWindow* window, int l, int loop, static_object S){
    srand(time(0));

    t = 0;

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


    if(true){
    if(t==0){
        //if(l==0){
        if(x2>x1){
            sf::Color wall_color{ wll.r, wll.g, wll.b };
        
            //wall_color = get_color_from_colormap(c);

            int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
            int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
            int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
            int ey2 = dyt*(bx2-xs+0.5)/dx+t1;
            poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wall_color, window);

            //if(render_polys_lines == 1){
            //    poly::draw_poly_lines( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, window);
            //}
        }
        //}else{
        if(x2<x1){
            sf::Color wall_color{ wll.r, wll.g, wll.b };

            //wall_color = get_color_from_colormap(c);

            int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
            int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
            int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
            int ey2 = dyt*(bx2-xs+0.5)/dx+t1;
            poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wall_color, window);
            
            //if(render_polys_lines == 1){
            //    poly::draw_poly_lines( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, window);
            //}
        }
        //}
    }
    }
        for(int i = x1; i<x2; i++){
        int y1 = dyb*(i-xs+0.5)/dx+b1;
        int y2 = dyt*(i-xs+0.5)/dx+t1;

        int by1 = y1;
        int by2 = y2;

        if(y1<0){y1=0;}
        if(y2<0){y2=0;}
        if(y1>(window->getSize().y)){y1=(window->getSize().y);}
        if(y2>(window->getSize().y)){y2=(window->getSize().y);}
        }
   //}
    }
}

    void static_draw(sf::RenderWindow *window, Camera &cam, Map *map) {
        //poly::draw_poly_txt_correct(0,0,250,50,250,300,0,250,"../Engine/EngineAssets/textures/empty.png",window);
        //poly::draw_poly_txt_affine(0,300,250,350,250,600,0,550,"../Engine/EngineAssets/textures/empty.png",window);
            //sf::Color wall_color{ 255, 255, 255 };
            //poly::draw_poly( 0,300,250,350,250,600,0,550, wall_color, window);

    double wx[4],wy[4],wz[4];
    int s,w;
    double CS=cos(d_to_rad(cam.a)), SN=sin(d_to_rad(cam.a));

    for(s=0;s<map->getObjCount()-1;s++){
        for(w=0;w<map->getObjCount()-s-1;w++){
            if(map->getObjAt(w).distance<map->getObjAt(w+1).distance){
                static_object st=map->getObjAt(w);
                map->getObjAt(w)=map->getObjAt(w+1);
                map->getObjAt(w+1)=st;
            }
        }
    }
     //sectors
     
     for(s=0;s<map->getObjCount();s++){
        map->objs.at(s).distance=0;

        if(map->objs.at(s).flip == 0){
        if(cam.z<map->objs.at(s).floor){map->objs.at(s).surface=1;}
        else if (cam.z>(map->objs.at(s).celing+map->objs.at(s).floor)){map->objs.at(s).surface=2;}  //Why this isnt fucking working !!!!!!!!!
        else {map->objs.at(s).surface=0;}
        }else{
        if(cam.z<map->objs.at(s).floor){map->objs.at(s).surface=2;}
        else if (cam.z>map->objs.at(s).celing){map->objs.at(s).surface=1;}
        else {map->objs.at(s).surface=0;}
        }

        for(int loop=0; loop < 2; loop++){
            for(w=0;w<map->objs.at(s).walls.size();w++){

                 double x1=map->objs.at(s).walls.at(w).sx-cam.x, y1=map->objs.at(s).walls.at(w).sy-cam.y;
                 double x2=map->objs.at(s).walls.at(w).ex-cam.x, y2=map->objs.at(s).walls.at(w).ey-cam.y;

                 if(loop==0){double swp=x1; x1=x2;x2=swp;swp=y1;y1=y2;y2=swp;}

                wx[0]=x1*CS-y1*SN;
                wx[1]=x2*CS-y2*SN;
                wx[2]=wx[0];
                wx[3]=wx[1];

                double shx1 = map->objs.at(s).walls.at(w).sx;
                double shx2 = map->objs.at(s).walls.at(w).ex;

                wy[0]=y1*CS+x1*SN;
                wy[1]=y2*CS+x2*SN;
                wy[2]=wy[0];
                wy[3]=wy[1];

                double shy1 = map->objs.at(s).walls.at(w).sy;
                double shy2 = map->objs.at(s).walls.at(w).ey;

                wz[0]=map->objs.at(s).floor-cam.z+((cam.l*wy[0])/32.0);
                wz[1]=map->objs.at(s).floor-cam.z+((cam.l*wy[1])/32.0);
                wz[2]=wz[0]+map->objs.at(s).celing;
                wz[3]=wz[1]+map->objs.at(s).celing;
                map->objs.at(s).distance+=dist(0,0,(wx[0]+wx[1])/2,(wy[0]+wy[1])/2);

                if(wy[0]<=0 && wy[1]<=0){continue;};

                if(wy[0]<=0){
                    clip_behind_camera(&wx[0],&wy[0],&wz[0],wx[1],wy[1],wz[1]);
                    clip_behind_camera(&wx[2],&wy[2],&wz[2],wx[3],wy[3],wz[3]);
                }

                if(wy[1]<=0){
                    clip_behind_camera(&wx[1],&wy[1],&wz[1],wx[0],wy[0],wz[0]);
                    clip_behind_camera(&wx[3],&wy[3],&wz[3],wx[2],wy[2],wz[2]);
                }

                wx[0]=wx[0]*222/wy[0]+(window->getSize().x/2); wy[0]=wz[0]*222/wy[0]+(window->getSize().y/2); 
                wx[1]=wx[1]*222/wy[1]+(window->getSize().x/2); wy[1]=wz[1]*222/wy[1]+(window->getSize().y/2);  
                wx[2]=wx[2]*222/wy[2]+(window->getSize().x/2); wy[2]=wz[2]*222/wy[2]+(window->getSize().y/2); 
                wx[3]=wx[3]*222/wy[3]+(window->getSize().x/2); wy[3]=wz[3]*222/wy[3]+(window->getSize().y/2); 

                float angle = ((atan2(shy1 - shy2, shx1 - shx2))*180/M_PI)+180;

                angle /= 360;
                double anglen = angle;
                angle = pow((18*angle-9),2);//+160;
                angle *= -1;
                angle += 80;
                if(angle > 80 || angle < 0){
                    angle = 0;
                }
                
                sf::Color shadow = sf::Color(0,0,0,angle);

                draw_wall(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],1, s , 0, map->objs.at(s).walls.at(w), w, window, map->objs.at(s).flip,loop, map->objs.at(s));
                //shade_wall(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],shadow, s , W[w].t, W[w].txt, w, window, map->objs.at(s).flip,loop,W[w].c);
            }
            map->objs.at(s).distance/=(map->objs.at(s).walls.size());
            map->objs.at(s).surface*=-1;
        }
    }
    }

} // namespace orgy
