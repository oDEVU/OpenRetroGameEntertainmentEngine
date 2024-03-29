#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>
#include <boost/compute.hpp>

#include "map.hpp"
#include "poly.hpp"
#include "static.hpp"
#include "engine_math.hpp"
#include "camera.hpp"
#include "pathhandler.hpp"
#include "functions.hpp"
#include "logger.hpp"

namespace orgee
{
    std::string global_path = orgee::getExecutablePath().substr(0, orgee::getExecutablePath().find_last_of("\\/")+1);

    int global_window_x = 1920;
    int global_window_y = 1080;

    void clip_behind_camera(double *x1,double *y1, double *z1, double x2,double y2,double z2){
        double da=*y1;
        double db=y2;
        double d=da-db;
        if (d==0){d=1;};
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

    void draw_plane(sf::RenderWindow* window, double caml, double cama, double camx , double camy, double camz){
        int x=0,y=0;
        int xo = global_window_x / 2;
        int yo = global_window_y / 2;
        double lookUp=-caml*8; if(lookUp>global_window_y){lookUp=global_window_y;}
        double moveUp=camz/16; if(moveUp==0){moveUp=0.0001;}

        for(y=-lookUp;y<yo+lookUp;y++){
            for(x=-xo;x<xo;x++){ 
                double z = y + lookUp; if(z==0){z=0.0001;}
                double fx = x/z*moveUp;
                double fy = 222.0/z*moveUp;
                double rx = fx*sin(d_to_rad(cama))-fy*cos(d_to_rad(cama))+camy/30;
                double ry = fx*cos(d_to_rad(cama))+fy*sin(d_to_rad(cama))-camx/30;
                if(rx<0){rx=-rx+1;}
                if(ry<0){ry=-ry+1;}
                if(rx<=0 || ry <= 0 || rx > 5 || ry > 5){continue;}
                if((int)rx%2==(int)ry%2){
                    //sf::RectangleShape rectangle;
                    //rectangle.setSize(sf::Vector2f(1, 1));
                    //rectangle.setFillColor(sf::Color::Red);
                    //rectangle.setPosition(x+xo, y+yo);
                    //window->draw(rectangle);
                }else{
                    //sf::RectangleShape rectangle;
                    //rectangle.setSize(sf::Vector2f(1, 1));
                    //rectangle.setFillColor(sf::Color::Green);
                    //rectangle.setPosition(x+xo, y+yo);
                    //window->draw(rectangle);
                }
            }
        }
    }

    void draw_wall(int x1, int x2, int b1, int b2, int t1, int t2, int c, int s, int t, wall wll, int w, sf::RenderWindow* window, int l, int loop, static_object S, bool debug_lines, bool affine_rendering){
    srand(time(0));

        t = 0;

        int x,y;

        if(x2 > 0 || x1 < global_window_x){


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
        if(x1>(global_window_x-1)){x1=(global_window_x-1);}
        if(x2>(global_window_x-1)){x2=(global_window_x-1);}

        int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
        int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
        int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
        int ey2 = dyt*(bx2-xs+0.5)/dx+t1;

        if(wll.mat.txt == 0){
            sf::Color wall_color{ wll.mat.r, wll.mat.g, wll.mat.b, wll.mat.a};
            poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wall_color, window);  //draws colored poly.
        }else{
            if(affine_rendering == true){
                poly::draw_poly_txt_affine( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wll.mat.txt_path, window);  //draws textured poly.
            }else{
                poly::draw_poly_txt_correct( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wll.mat.txt_path, window);  //draws textured poly.
            }
        }
            
        if(debug_lines == true){     // if debug lines are turned on it will render them
             poly::draw_poly_lines( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, window);
        }
    }
}
    void shade_wall(int x1, int x2, int b1, int b2, int t1, int t2, sf::Color color, sf::RenderWindow* window, wall wll, bool affine_rendering){

        if(x2 > 0 || x1 < global_window_x){


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
        if(x1>(global_window_x-1)){x1=(global_window_x-1);}
        if(x2>(global_window_x-1)){x2=(global_window_x-1);}

        int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
        int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
        int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
        int ey2 = dyt*(bx2-xs+0.5)/dx+t1;

        if(wll.mat.txt == 0){
            if(affine_rendering == true){
                // pass
            }else{
                poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, color, window);  //draws colored poly.
            }
        }else{
            if(affine_rendering == true){
                // pass
            }else{
                poly::draw_poly_txt_correct_shade( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, wll.mat.txt_path, window, color.a);  //draws textured poly.
            }
        }
    }
}
    void draw_text_3d(int x1, int x2, int b1, int b2, int t1, int t2, sf::RenderWindow* window, sf::Text txt, sf::Font font){

        if(x2 > 0 || x1 < global_window_x){


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
        if(x1>(global_window_x-1)){x1=(global_window_x-1);}
        if(x2>(global_window_x-1)){x2=(global_window_x-1);}

        int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
        int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
        int ey1 = dyb*(bx2-xs+0.5)/dx+b1;
        int ey2 = dyt*(bx2-xs+0.5)/dx+t1;

        txt.setFont(font);

        int width = txt.getLocalBounds().width;
        int height = txt.getLocalBounds().height;

        txt.setPosition((x1-width/2), (sy1-height/2));
        window->draw(txt);

        //poly::draw_poly( bx1,  sy2,  bx2,  ey2,  bx2,  ey1,  bx1,  sy1, color, window);  //draws colored poly.
    }
}
    void draw_entity(int x1, int x2, int b1, int b2, int t1, int t2, std::string texture_path, sf::RenderWindow* window){

        //std::cout << texture_path << std::endl;

        if(x2 > 0 || x1 < global_window_x){


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
        if(x1>(global_window_x-1)){x1=(global_window_x-1);}
        if(x2>(global_window_x-1)){x2=(global_window_x-1);}

        int sy1 = dyb*(bx1-xs+0.5)/dx+b1;
        int sy2 = dyt*(bx1-xs+0.5)/dx+t1;
        
        if(!poly::textures_map.contains(texture_path)){

        sf::Texture texture;
        if (!texture.loadFromFile(texture_path))
        {
            if (!texture.loadFromFile(global_path + "EngineAssets/textures/empty.png"))
            {
                //std::cout << "Fatal error!!! could not find EngineAssets folder\n";
                consoleLog("Fatal error!!! could not find EngineAssets folder",1);
            }
            consoleLog("Failed to load texture from path!",1);
        }

        poly::textures_map.insert({texture_path, texture});
    }

        double txt_x = poly::textures_map[texture_path].getSize().x;
        double txt_y = poly::textures_map[texture_path].getSize().y;

        txt_y /= sy2 - sy1;
        txt_x /= txt_y;


        poly::draw_poly_txt_correct( bx1-(txt_x/2),  sy2,  bx1+(txt_x/2),  sy2,  bx1+(txt_x/2),  sy1,  bx1-(txt_x/2),  sy1, texture_path, window);
    }
}

    void static_draw(sf::RenderWindow *window, Camera &cam, Map *map, bool debug_lines, bool affine_rendering, bool global_light, sf::Font font, Window *win) {
        //poly::draw_poly_txt_correct(0,0,250,50,250,300,0,250,"../Engine/EngineAssets/textures/empty.png",window);
        //poly::draw_poly_txt_affine(0,300,250,350,250,600,0,550,"../Engine/EngineAssets/textures/empty.png",window);
        //sf::Color wall_color{ 255, 255, 255 };
        //poly::draw_poly( 0,300,250,350,250,600,0,550, wall_color, window);
    
    global_window_x = window->getSize().x / win->getScale();
    global_window_y = window->getSize().y / win->getScale();


    double wx[4],wy[4],wz[4];
    int s,w;
    double CS=cos(d_to_rad(cam.a)), SN=sin(d_to_rad(cam.a));

    for(s=0;s<map->getObjCount();s++){
        double temp_x = 0, temp_y = 0;

        for(w=0;w<map->objs.at(s).walls.size();w++){
            map->objs.at(s).distance += dist(cam.x, cam.y, map->objs.at(s).walls.at(w).mx, map->objs.at(s).walls.at(w).my);
        }

        map->objs.at(s).distance /= map->objs.at(s).walls.size();
    }

    //orgee::quick_sort(map->objs, 0, map->objs.size()-1);  // why the fuck is it slower

    ///*
    for(s=0;s<map->getObjCount()-1;s++){
        for(w=0;w<map->getObjCount()-s-1;w++){
            if(map->getObjAt(w).distance < map->getObjAt(w+1).distance){
                static_object tmp_obj=map->objs.at(w);
                map->objs.at(w)=map->objs.at(w+1);
                map->objs.at(w+1)=tmp_obj;

                //std::cout << "sort\n" <<  "\n";
                //render.printToScreen("Object sorted");
            }
        }
    }
    //*/
    
    //sectors
     
     for(s=0;s<map->getObjCount();s++){
        map->objs.at(s).distance=0;

        if(cam.z<map->objs.at(s).floor){map->objs.at(s).surface=1;}
        else if (cam.z>(map->objs.at(s).celing+map->objs.at(s).floor)){map->objs.at(s).surface=2;}  //Why this isnt fucking working !!!!!!!!!
        else {map->objs.at(s).surface=0;}


            for(w=0;w<map->objs.at(s).walls.size();w++){
                map->objs.at(s).walls.at(w).mx = (map->objs.at(s).walls.at(w).sx + map->objs.at(s).walls.at(w).ex)/2;
                map->objs.at(s).walls.at(w).my = (map->objs.at(s).walls.at(w).sy + map->objs.at(s).walls.at(w).ey)/2;
                map->objs.at(s).walls.at(w).dist = dist(cam.x, cam.y, map->objs.at(s).walls.at(w).mx, map->objs.at(s).walls.at(w).my);
            }

            //sort walls here
            for(w=0;w<map->objs.at(s).walls.size()-1;w++){
                for(int v=0;v<map->objs.at(s).walls.size()-w-1;v++){
                    //double midle_x = 0, midle_y = 0;
                    //map->objs.at(s).walls.at(v);
                    if(map->objs.at(s).walls.at(v).dist < map->objs.at(s).walls.at(v+1).dist){
                        wall temp;
                        temp = map->objs.at(s).walls.at(v);
                        map->objs.at(s).walls.at(v) = map->objs.at(s).walls.at(v+1);
                        map->objs.at(s).walls.at(v+1) = temp;
                    }
                }
            }
            


            for(w=0;w<map->objs.at(s).walls.size();w++){

                double x1=map->objs.at(s).walls.at(w).sx-cam.x, y1=map->objs.at(s).walls.at(w).sy-cam.y;
                double x2=map->objs.at(s).walls.at(w).ex-cam.x, y2=map->objs.at(s).walls.at(w).ey-cam.y;

                //if(loop==0){double swp=x1; x1=x2;x2=swp;swp=y1;y1=y2;y2=swp;}

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
                //map->objs.at(s).distance+=dist(0,0,(wx[0]+wx[1])/2,(wy[0]+wy[1])/2);

                if(wy[0]<=0 && wy[1]<=0){continue;};

                if(wy[0]<=0){
                    clip_behind_camera(&wx[0],&wy[0],&wz[0],wx[1],wy[1],wz[1]);
                    clip_behind_camera(&wx[2],&wy[2],&wz[2],wx[3],wy[3],wz[3]);
                }

                if(wy[1]<=0){
                    clip_behind_camera(&wx[1],&wy[1],&wz[1],wx[0],wy[0],wz[0]);
                    clip_behind_camera(&wx[3],&wy[3],&wz[3],wx[2],wy[2],wz[2]);
                }

                wx[0]=wx[0]*222/wy[0]+(global_window_x/2); wy[0]=wz[0]*222/wy[0]+(global_window_y/2); 
                wx[1]=wx[1]*222/wy[1]+(global_window_x/2); wy[1]=wz[1]*222/wy[1]+(global_window_y/2);  
                wx[2]=wx[2]*222/wy[2]+(global_window_x/2); wy[2]=wz[2]*222/wy[2]+(global_window_y/2); 
                wx[3]=wx[3]*222/wy[3]+(global_window_x/2); wy[3]=wz[3]*222/wy[3]+(global_window_y/2); 

                draw_plane(window, cam.l, cam.a, cam.x, cam.y, cam.z);
                if(map->objs.at(s).type == "static"){
                    draw_wall(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],1, s , 0, map->objs.at(s).walls.at(w), w, window, map->objs.at(s).flip,true, map->objs.at(s), debug_lines, affine_rendering);
                    if(global_light){

                        double angle = ((atan2(shy1 - shy2, shx1 - shx2))*180/M_PI)+180;

                        angle /= 360;
                        angle = pow((18*angle-9),2);//+160;
                        angle *= -1;
                        angle += 80;
                        if(angle > 80 || angle < 0){
                            angle = 0;
                        }
                
                        sf::Color shadow = sf::Color(0,0,0,angle);

                        shade_wall(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],shadow, window, map->objs.at(s).walls.at(w), affine_rendering);  
                    }
                }else if(map->objs.at(s).type == "text"){
                    draw_text_3d(wx[0], wx[1], wy[0], wy[1], wy[2], wy[3],  window, map->objs.at(s).text, font);
                }else if(map->objs.at(s).type == "entity"){
                    // TODO
                    map->objs.at(s).walls.at(0).ex = map->objs.at(s).walls.at(0).sx;
                    map->objs.at(s).walls.at(0).ey = map->objs.at(s).walls.at(0).sy;
                    draw_entity(wx[0],wx[1],wy[0],wy[1],wy[2],wy[3],map->objs.at(s).walls.at(0).mat.txt_path, window);
                }else{
                    consoleLog("Tried to render unknown object type. \nmap_loader should not allow this to happen, it is possible that some objects got corrupted or map data was edited with outside program",0);
                }
            }
            //map->objs.at(s).distance/=(map->objs.at(s).walls.size());
            map->objs.at(s).surface*=-1;
    }
    }

} // namespace orgee
