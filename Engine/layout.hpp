#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include <vector>
#include <any>

#include "vectors.hpp"

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

    class LayoutElement {
        public:
            virtual Elements GetType() = 0;

            virtual void test() = 0;
            
            virtual ~LayoutElement() {} 
    };

    class Empty : public LayoutElement  {
        public:
            Elements GetType() { return EmptyElement;}

            virtual void test() {std::cout << "test";}
    }; 

    class Rect : public LayoutElement  {
        public:
            Elements GetType() { return RectElement;}

            virtual void test() {std::cout << "test";}
            
            vec2dyn position;
            vec2dyn size;
            alignment align;
            sf::Color color;
            int zindex;
    };

    class Image : public LayoutElement {
        public:
            Elements GetType() { return ImageElement;}

            virtual void test() {std::cout << "test";}
            
            vec2dyn position;
            vec2dyn size;
            alignment align;
            std::string texture_path;
            int zindex;
    };

    class Text : public LayoutElement {
        public:
            Elements GetType() { return TextElement;}

            virtual void test() {std::cout << "test";}
            
            std::string text;
            vec2dyn position;
            int size;
            alignment align;
            std::string font_path;
            int zindex;
    };

    class Layout
    {
    private:
        int zindex;
    public:
        Layout(int z);
        ~Layout();

        std::vector<std::any> ElementArr;
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