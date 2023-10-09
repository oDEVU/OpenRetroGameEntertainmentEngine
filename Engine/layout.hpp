#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>
#include <any>

#include "vectors.hpp"
#include "poly.hpp"

namespace orgee
{
    enum Elements  {
        EmptyElement,
        RectElement,
        ImageElement,
        TextElement,
    };

    enum alignment {
        TopLeft,
        Top,
        TopRight,
        Right,
        BottomRight,
        Bottom,
        BottomLeft,
        Left,
        None,
    };

    std::map<std::string, sf::Font> font_map;

    class LayoutElement {
        public:
            virtual void test() = 0;

            virtual void Update(float delta) = 0;

            virtual void Create() = 0;

            virtual void Draw(sf::RenderWindow *window) const = 0;
            
            virtual ~LayoutElement() {} 
    };

    class Empty : public LayoutElement  {
        public:
            virtual void test() {std::cout << "test";}

            virtual void Update(float delta) {};

            virtual void Create() {};

            void Draw(sf::RenderWindow *window) const override {}
    }; 

    class Rect : public LayoutElement  {
        public:
            Rect(vec2dyn c_position,vec2dyn c_size,alignment c_align,sf::Color c_color,int c_zindex){
                position = c_position;
                size = c_size;
                align = c_align;
                color = c_color;
                zindex = c_zindex;
            }

            virtual void test() {std::cout << "test";}

            virtual void Update(float delta) {};

            virtual void Create() {};

            void Draw(sf::RenderWindow *window) const override {

                    //std::cout << text;

                    int height = 0;
                    int width = 0;

                    int find = size.x.find("px");

                    if(find != std::string::npos){
                        width = stoi(size.x.substr(0,find));
                    }else{
                       find = size.x.find("%"); 

                       float t = stoi(size.x.substr(0,find));

                       width = window->getSize().x * (float)(t/100);
                    }

                    find = size.y.find("px");

                    if(find != std::string::npos){
                        height = stoi(size.y.substr(0,find));
                    }else{
                       find = size.x.find("%"); 

                       float t = stoi(size.y.substr(0,find));

                       height = window->getSize().y * (float)(t/100);
                    }

                    int pos_x = 0;
                    int pos_y = 0;

                    if(position.x != ""){

                    int at = position.x.find("px");

                    //pos x
                    if(at != std::string::npos){
                        pos_x = stoi(position.x.substr(0,at));
                    }else{
                       at = position.x.find("%"); 

                       float t = stoi(position.x.substr(0,at));

                       pos_x = window->getSize().x * (float)(t/100);
                    }

                    at = position.y.find("px");

                    //pos y
                    if(at != std::string::npos){
                        pos_y = stoi(position.y.substr(0,at));
                    }else{
                       at = position.x.find("%"); 

                       float t = stoi(position.y.substr(0,at));

                       pos_y = window->getSize().y * (float)(t/100);
                    }
                    }

                        int x = pos_x, y = pos_y;

                        switch(align) {
                            case Bottom:
                                pos_y = (window->getSize().y - height)-y;
                                pos_x = ((window->getSize().x/2) - (width/2))+x;
                                break;
                            case BottomLeft:
                                pos_y = window->getSize().y - height-y;
                                pos_x = 0+x;
                                break;
                            case BottomRight:
                                pos_y = window->getSize().y - height-y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Top:
                                pos_y = 0+y;
                                pos_x = (window->getSize().x/2) - (width/2)+x;
                                break;
                            case TopLeft:
                                pos_y = 0+y;
                                pos_x = 0+x;
                                break;
                            case TopRight:
                                pos_y = 0+y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Right:
                                pos_y = (window->getSize().y/2) - (height/2)+y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Left:
                                pos_y = (window->getSize().y/2) - (height/2)+y;
                                pos_x = 0+x;
                                break;
                            default:
                                break;
                        }


                    sf::RectangleShape rectangle(sf::Vector2f(width,height));
                    rectangle.setPosition(pos_x,pos_y);

                    rectangle.setFillColor(color);

                    window->draw(rectangle);
                }
            
            vec2dyn position;
            vec2dyn size;
            alignment align;
            sf::Color color;
            int zindex;
    };

    class Image : public LayoutElement {
        public:
            Image(vec2dyn c_position,vec2dyn c_size,alignment c_align,std::string c_texture_path,int c_zindex){
                position = c_position;
                size = c_size;
                align = c_align;
                texture_path = c_texture_path;
                zindex = c_zindex;
            }

            virtual void test() {std::cout << "test";}

            virtual void Update(float delta) {};

            virtual void Create() {};

            void Draw(sf::RenderWindow *window) const override {
                    int height = 0;
                    int width = 0;

                    int find = size.x.find("px");

                    if(find != std::string::npos){
                        width = stoi(size.x.substr(0,find));
                    }else{
                       find = size.x.find("%"); 

                       float t = stoi(size.x.substr(0,find));

                       width = window->getSize().x * (float)(t/100);
                    }

                    find = size.y.find("px");

                    if(find != std::string::npos){
                        height = stoi(size.y.substr(0,find));
                    }else{
                       find = size.x.find("%"); 

                       float t = stoi(size.y.substr(0,find));

                       height = window->getSize().y * (float)(t/100);
                    }

                    int pos_x = 0;
                    int pos_y = 0;

                    if(position.x != ""){

                    int at = position.x.find("px");

                    //pos x
                    if(at != std::string::npos){
                        pos_x = stoi(position.x.substr(0,at));
                    }else{
                       at = position.x.find("%"); 

                       float t = stoi(position.x.substr(0,at));

                       pos_x = window->getSize().x * (float)(t/100);
                    }

                    at = position.y.find("px");

                    //pos y
                    if(at != std::string::npos){
                        pos_y = stoi(position.y.substr(0,at));
                    }else{
                       at = position.x.find("%"); 

                       float t = stoi(position.y.substr(0,at));

                       pos_y = window->getSize().y * (float)(t/100);
                    }
                    }

                        int x = pos_x, y = pos_y;

                        switch(align) {
                            case Bottom:
                                pos_y = (window->getSize().y - height)-y;
                                pos_x = ((window->getSize().x/2) - (width/2))+x;
                                break;
                            case BottomLeft:
                                pos_y = window->getSize().y - height-y;
                                pos_x = 0+x;
                                break;
                            case BottomRight:
                                pos_y = window->getSize().y - height-y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Top:
                                pos_y = 0+y;
                                pos_x = (window->getSize().x/2) - (width/2)+x;
                                break;
                            case TopLeft:
                                pos_y = 0+y;
                                pos_x = 0+x;
                                break;
                            case TopRight:
                                pos_y = 0+y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Right:
                                pos_y = (window->getSize().y/2) - (height/2)+y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Left:
                                pos_y = (window->getSize().y/2) - (height/2)+y;
                                pos_x = 0+x;
                                break;
                            default:
                                break;
                        }

                    poly::draw_poly_txt_correct(pos_x, pos_y+height, pos_x+width, pos_y+height, pos_x+width, pos_y, pos_x, pos_y, global_path + texture_path, window);
                    }

            vec2dyn position;
            vec2dyn size;
            alignment align;
            std::string texture_path;
            int zindex;
    };

    class Text : public LayoutElement {
        public:
            Text(vec2dyn c_position,int c_size,alignment c_align,std::string c_font_path,std::string c_text,int c_zindex){
                position = c_position;
                size = c_size;
                align = c_align;
                font_path = c_font_path;
                zindex = c_zindex;
                text = c_text;
            }
            virtual void test() {std::cout << "test";}

            virtual void Update(float delta) {};

            virtual void Create() {};

            void Draw(sf::RenderWindow *window) const override {
                    if(!font_map.contains(font_path)){

                        sf::Font new_font;
                        if (!new_font.loadFromFile(global_path + font_path))
                        {
                            if (!new_font.loadFromFile(global_path + "EngineAssets/fonts/font.ttf"))
                            {
                                consoleLog("Fatal error!!! could not find EngineAssets folder",1);
                            }
                            consoleLog("Failed to load font from path!",1);
                        }

                        font_map.insert({font_path, new_font});
                    }

                    sf::Text txt((std::string)text,font_map[font_path]);
                    txt.setFont(font_map[font_path]);
                    txt.setCharacterSize(size);

                    //std::cout << size << std::endl;

                    int width = txt.getLocalBounds().width;
                    int height = txt.getLocalBounds().height;

                    int pos_x = 0;
                    int pos_y = 0;

                    if(position.x != ""){

                    int at = position.x.find("px");

                    //pos x
                    if(at != std::string::npos){
                        pos_x = stoi(position.x.substr(0,at));
                    }else{
                       at = position.x.find("%"); 

                       float t = stoi(position.x.substr(0,at));

                       pos_x = window->getSize().x * (float)(t/100);
                    }

                    at = position.y.find("px");

                    //pos y
                    if(at != std::string::npos){
                        pos_y = stoi(position.y.substr(0,at));
                    }else{
                       at = position.x.find("%"); 

                       float t = stoi(position.y.substr(0,at));

                       pos_y = window->getSize().y * (float)(t/100);
                    }
                    }

                        int x = pos_x, y = pos_y;

                        switch(align) {
                            case Bottom:
                                pos_y = (window->getSize().y - height)-y;
                                pos_x = ((window->getSize().x/2) - (width/2))+x;
                                break;
                            case BottomLeft:
                                pos_y = window->getSize().y - height-y;
                                pos_x = 0+x;
                                break;
                            case BottomRight:
                                pos_y = window->getSize().y - height-y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Top:
                                pos_y = 0+y;
                                pos_x = (window->getSize().x/2) - (width/2)+x;
                                break;
                            case TopLeft:
                                pos_y = 0+y;
                                pos_x = 0+x;
                                break;
                            case TopRight:
                                pos_y = 0+y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Right:
                                pos_y = (window->getSize().y/2) - (height/2)+y;
                                pos_x = (window->getSize().x/1) - (width/1)-x;
                                break;
                            case Left:
                                pos_y = (window->getSize().y/2) - (height/2)+y;
                                pos_x = 0+x;
                                break;
                            default:
                                break;
                        }

                    txt.setPosition((pos_x-width/2), (pos_y-height/2));
                    window->draw(txt);
                    }
            
            std::string text;
            vec2dyn position;
            int size;
            alignment align;
            std::string font_path;
            int zindex;
    };

    class BaseButton : public LayoutElement {
        public:
            BaseButton(vec2dyn c_position,vec2dyn c_size,alignment c_align,sf::Color c_color,int c_zindex, std::string c_text, int c_text_size, std::string c_font_path){
                position = c_position;
                size = c_size;
                align = c_align;
                color = c_color;
                zindex = c_zindex;
                text_string = c_text;
                text_size = c_text_size;
                font_path = c_font_path;
            }

            virtual void test() {std::cout << "test";}

            virtual void Update(float delta) {};

            virtual void Create() {
                rect = new Rect(position,size,align,color,zindex);
                text = new Text(position,text_size,align,font_path,text_string,zindex);

                std::cout << "created" << std::endl;
            };

            void Draw(sf::RenderWindow *window) const override {
                    rect->Draw(window);
                    text->Draw(window);
                }
            
            vec2dyn position;
            vec2dyn size;
            int text_size;
            std::string font_path;
            alignment align;
            sf::Color color;
            int zindex;
            std::string text_string;
            Rect *rect;//(position,size,align,color,index);
            Text *text;// = new Text(text
    };

    class Layout
    {
    private:
        int zindex;
    public:
        Layout(int z);
        ~Layout();

        std::vector<LayoutElement*> ElementArr;
/*
        void Add(LayoutElement* elem){
            ElementArr.push_back(elem);
        }

        std::vector GetElementArr(){
            return ElementArr;
        }*/
    };
    
    Layout::Layout(int z)
    {
        zindex = z;
    }
    
    Layout::~Layout()
    {
    }
    
}