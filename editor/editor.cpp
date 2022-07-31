//  This is Editor. It is only to create games. It will be not compiled with game. We compile it before the engine to make game.
//  Engine and game can be compiled without it, editor is only GUI for making and compiling games.

#include <raylib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <boost/predef.h>
#include <boost/process.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <chrono>
#include <thread>
#include <filesystem>
#include <iostream>

#include "pathhandler.hpp"
#include "../engine/functions.hpp"
//#include "image_editor.hpp"

#define RAYGUI_IMPLEMENTATION
#include "../engine/raygui.hpp"                 // Required for GUI

    using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;

    namespace fs = std::filesystem;


    std::string game_path = "../game/";

    std::string working_path = game_path;

    std::string files[128];

    int iii = 0;

    int state = 0;
    bool type_menu = 0;
    const char* state_text = "Coding";

    int x_text_offset = 0;
    int y_text_offset = 0;

void load_files() {
    iii = 0;
    if (iii < 128){
        for (const auto & entry : fs::directory_iterator(working_path)){
            files[iii] = entry.path();
            iii++;
        }
    }else{
        std::cout << "Too many files/directores to load. maximum of 128!" << std::endl;
    }
}


void clear_source_code() {
    system("rm -f ../packaged/game/*.cpp");
    system("rm -f ../packaged/game/*.hpp");
    system("rm -f ../packaged/game/*.h");
    system("rm -f ../packaged/game/*.c");
    system("rm -f ../packaged/engine/*.cpp");
    system("rm -f ../packaged/engine/*.hpp");
    system("rm -f ../packaged/engine/*.h");
    system("rm -f ../packaged/engine/*.c");
    system("rm -f ../packaged/engine/*.sh");
}

void clear_source_code_win() {
    system("rm ../packaged/game/*.cpp");
    system("rm ../packaged/game/*.hpp");
    system("rm ../packaged/game/*.h");
    system("rm ../packaged/game/*.c");
    system("rm ../packaged/engine/*.cpp");
    system("rm ../packaged/engine/*.hpp");
    system("rm ../packaged/engine/*.h");
    system("rm ../packaged/engine/*.c");
    system("rm ../packaged/engine/*.sh");
}

int main(int argc,char** argv){
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    // Drawing text

    int g = 0;
    const char* text = "Empty";

    //Code editor

    std::string textfile = "No file opened";
    //char* working_textfile = glogal_functions::unconstchar(textfile);
    int coursor_pos = 0;
    char replaced = textfile.at(coursor_pos);
    int txt_cnt = -1;

    //Editor init stuff

    load_files();
    float gloabal_font_size = 1;

    std::string path = MyPaths::getExecutablePath().substr(0, MyPaths::getExecutablePath().find_last_of("\\/"));
    const char* dir = path.c_str();
    text = path.c_str();
    bool succes = ChangeDirectory(dir);

    //image edotor stuff

    float img_contrs = 5;
    float old_img_contrs = 5;
    bool painting = 0;
    Color paint_color = BLACK;

    //Init

    InitWindow(screenWidth, screenHeight, "O.R.G.Y Editor");
    MaximizeWindow();

    GuiLoadStyle("editor_style.rgs");

    int counter = 0;
    int fade = 0;

    Image current_for_edit;
    int whith_image = 0;
    Texture2D texture;

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));


    int timer = 0;
    while (!WindowShouldClose())
    {
        timer++;
        if(timer>(GetFPS()/10)){
            timer = 0;
        }
        SetWindowTitle(TextFormat("O.R.G.Y Editor - %i",GetFPS()));

        BeginDrawing();

            ClearBackground(Color{15,15,15,255});
            load_files();

            if(counter<255){
                int alpha = 255 - counter;
                DrawText("Powered by: raylib", round(GetScreenWidth()/2-250), round(GetScreenHeight()/2-25), 50, Color{255,255,255,(unsigned char)alpha});
                counter++;
            }else{
                if(fade < 253){
                    fade+=2;
                }else{
                    fade=255;
                }
                //  left panel
                DrawRectangle(0,0,(GetScreenWidth()*0.12),GetScreenHeight(),Color{22,22,22,(unsigned char)fade});
                
                int left_anchor = (GetScreenHeight()*0.04) + 5;

                if(game_path != working_path){
                    if ( GuiButton( (Rectangle){ 5, (GetScreenHeight()-left_anchor), (GetScreenWidth()*0.12)-10, (GetScreenHeight()*0.04) }, "../") ){
                        working_path = working_path.substr(0, working_path.find_last_of("\\/")+1);
                        load_files();
                    }
                    left_anchor += (GetScreenHeight()*0.04) + 5;
                }


                if(state == 0){
                    state_text = "Coding";
                    y_text_offset += GetMouseWheelMove()*(GetFPS()/4);
                    if(y_text_offset > 0){
                        y_text_offset = 0;
                    }
                    //GuiTextBoxMulti(Rectangle{(GetScreenWidth()*0.12),(GetScreenHeight()*0.08),(GetScreenWidth()-(GetScreenWidth()*0.32)),GetScreenHeight()-(GetScreenHeight()*0.08)}, textfile, 1024, 1); 

                    if(txt_cnt != -1){
                        DrawText(textfile.c_str(), (GetScreenWidth()*0.12)+x_text_offset, (GetScreenHeight()*0.08)+y_text_offset, gloabal_font_size, WHITE);
                        if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight())-((GetScreenHeight()*0.04)+16), (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "Save") ){
                        //ImageColorInvert(&current_for_edit);  
                        //ExportImage(current_for_edit, files[whith_image].c_str());
                        textfile.at(coursor_pos) = replaced;
                        SaveFileText(files[txt_cnt].c_str(), glogal_functions::unconstchar(textfile.c_str()));
                        }

                        /*
                        if (IsKeyDown(KEY_SPACE)){
                            if(timer==(GetFPS()/10)){
                            textfile.at(coursor_pos) = replaced;
                            textfile += "  ";
                            for(int i = (textfile.size()-2); i>=coursor_pos ;i--){
                                textfile.at(i+1)=textfile.at(i);
                            }
                            textfile.at(coursor_pos) = ' ';
                            coursor_pos++;
                            replaced = textfile.at(coursor_pos);
                            }
                        }
                        */

                        if (IsKeyDown(KEY_ENTER)){
                            if(timer==(GetFPS()/10)){
                            textfile.at(coursor_pos) = replaced;
                            textfile += "  ";
                            for(int i = (textfile.size()-2); i>=coursor_pos ;i--){
                                textfile.at(i+1)=textfile.at(i);
                            }
                            textfile.at(coursor_pos) = '\n';
                            coursor_pos++;
                            replaced = textfile.at(coursor_pos);
                            }
                        }

                        if (IsKeyDown(KEY_BACKSPACE)){
                            if(timer==(GetFPS()/10)){
                            textfile.at(coursor_pos) = replaced;
                            if(coursor_pos > 0){
                                //textfile += "  ";
                                for(int i = coursor_pos-1; i<(textfile.size()-1) ;i++){
                                    textfile.at(i)=textfile.at(i+1);
                                }
                                //textfile.at(coursor_pos) = ' ';
                                coursor_pos--;
                                replaced = textfile.at(coursor_pos);
                            }
                            }
                        }

                        if (IsKeyDown(KEY_RIGHT)){
                            if(timer==(GetFPS()/10)){
                            textfile.at(coursor_pos) = replaced;
                            if(coursor_pos < textfile.size()){
                                coursor_pos++;
                                replaced = textfile.at(coursor_pos);
                            }
                            }
                        }

                        if (IsKeyDown(KEY_LEFT)){
                            if(timer==(GetFPS()/10)){
                            textfile.at(coursor_pos) = replaced;
                            if(coursor_pos > 0){
                                coursor_pos--;
                                replaced = textfile.at(coursor_pos);
                            }
                            }
                        }

                            int key = GetCharPressed();

                            // Check if more characters have been pressed on the same frame
                            while (key > 0)
                            {
                            // NOTE: Only allow keys in range [32..125]
                            if ((key >= 32) && (key <= 125))
                            {
                                textfile.at(coursor_pos) = replaced;
                                textfile += "  ";
                                for(int i = (textfile.size()-2); i>=coursor_pos ;i--){
                                    textfile.at(i+1)=textfile.at(i);
                            }
                            textfile.at(coursor_pos) = (char)key;
                            coursor_pos++;
                            replaced = textfile.at(coursor_pos);
                            }

                            key = GetCharPressed();  // Check next character in the queue
                            }

                        //coursor_pos = 0;
                        if(textfile.at(coursor_pos) != '_'){
                        replaced = textfile.at(coursor_pos);
                        }

                        if(textfile.at(coursor_pos) != '\n'){
                        textfile.at(coursor_pos) = '_';
                        }
                        //int txt_cnt = -1;
                    }
                }else if(state == 1){
                    state_text = "Map editing";
                    DrawText("Not implemented yet :C", (GetScreenWidth()*0.12), (GetScreenHeight()*0.08), gloabal_font_size, RED);
                }else if(state == 2){
                    state_text = "Image editing";


                    texture = LoadTextureFromImage(current_for_edit); 
                    //DrawTexture(texture, (GetScreenWidth()*0.12)+8, (GetScreenHeight()*0.08)+8, WHITE); 
                    float txt_scale = ((GetScreenHeight()-(GetScreenHeight()*0.08)-16))/current_for_edit.height;
                    DrawTextureEx(texture, Vector2{(GetScreenWidth()*0.12)+8, (GetScreenHeight()*0.08)+8}, 0, txt_scale, WHITE); 

                    //editing
                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight()*0.08)+16, (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "Invert") ){
                        ImageColorInvert(&current_for_edit);  

                    }

                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.04)+16, (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "Grayscale") ){
                        ImageColorGrayscale(&current_for_edit);  

                    }

                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16+(GetScreenWidth()*0.06), (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.08)+32, (GetScreenWidth()*0.06), (GetScreenHeight()*0.04) }, "+") ){
                        //ImageColorGrayscale(&current_for_edit);  
                        ImageColorBrightness(&current_for_edit, 1); 

                    }
                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.08)+32, (GetScreenWidth()*0.06), (GetScreenHeight()*0.04) }, "-") ){
                        //ImageColorGrayscale(&current_for_edit);  
                        ImageColorBrightness(&current_for_edit, -1); 

                    }
                    GuiLabel((Rectangle){ ((GetScreenWidth()-(GetScreenWidth()*0.32))-16)-(GetScreenWidth()*0.05), (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.08)+32, (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "Brightness: "); 
                    

                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16+(GetScreenWidth()*0.06), (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.12)+48, (GetScreenWidth()*0.06), (GetScreenHeight()*0.04) }, "+") ){
                        //ImageColorGrayscale(&current_for_edit);  
                        ImageColorContrast(&current_for_edit, 1); 

                    }
                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.12)+48, (GetScreenWidth()*0.06), (GetScreenHeight()*0.04) }, "-") ){
                        //ImageColorGrayscale(&current_for_edit);  
                        ImageColorContrast(&current_for_edit, -1); 

                    }
                    GuiLabel((Rectangle){ ((GetScreenWidth()-(GetScreenWidth()*0.32))-16)-(GetScreenWidth()*0.05), (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.12)+48, (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "Contrast: "); 
                    
                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16+(GetScreenWidth()*0.06), (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.16)+64, (GetScreenWidth()*0.06), (GetScreenHeight()*0.04) }, "+90*") ){
                        //ImageColorGrayscale(&current_for_edit);  
                        //ImageColorContrast(&current_for_edit, 1); 
                        ImageRotateCW( &current_for_edit ); 

                    }
                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.16)+64, (GetScreenWidth()*0.06), (GetScreenHeight()*0.04) }, "-90*") ){
                        //ImageColorGrayscale(&current_for_edit);  
                        //ImageColorContrast(&current_for_edit, -1); 
                        ImageRotateCCW( &current_for_edit ); 

                    }
                    GuiLabel((Rectangle){ ((GetScreenWidth()-(GetScreenWidth()*0.32))-16)-(GetScreenWidth()*0.05), (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.16)+64, (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "Rotate: "); 
                    
                    //DrawText("Brightness: ", (GetScreenWidth()-(GetScreenWidth()*0.32))-16+(GetScreenWidth()*0.06)-(GetScreenWidth()*0.11), (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.08)+32, gloabal_font_size, WHITE);
                    //DrawText(const char *text, int posX, int posY, int fontSize, Color color); 
                    /*
                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.08)+32, (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "[EXPERIMENTAL] Toggle painting") ){
                        painting = !painting;

                    }
                    //DrawText("Brightness: ", 5, (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.08)+32, WHITE);
                    img_contrs = GuiSliderBar((Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight()*0.08)+16+(GetScreenHeight()*0.12)+32+16, (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "Brush size: ", NULL, img_contrs, 1, 256);
                    
                    if(painting){
                        DrawCircleV(GetMousePosition(), img_contrs, paint_color); 
                        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                                ImageDrawCircle(&current_for_edit, ((GetMousePosition().x-(GetScreenWidth()*0.12)+8)/txt_scale)-((img_contrs/2)/txt_scale), ((GetMousePosition().y-(GetScreenHeight()*0.08)+8)/txt_scale)-((img_contrs/2)/txt_scale), img_contrs/txt_scale, paint_color);   
                            
                        }
                    }
                    */
                    if ( GuiButton( (Rectangle){ (GetScreenWidth()-(GetScreenWidth()*0.32))-16, (GetScreenHeight())-((GetScreenHeight()*0.04)+16), (GetScreenWidth()*0.12), (GetScreenHeight()*0.04) }, "Save") ){
                        //ImageColorInvert(&current_for_edit);  
                        ExportImage(current_for_edit, files[whith_image].c_str());
                    }
                }

                for(int bdir = 0; bdir < iii; bdir++){
                    std::string::size_type i = files[bdir].find(game_path);
                    if (i != std::string::npos)
                    files[bdir].erase(i, game_path.length());

                    if(files[bdir].find(".cpp") != std::string::npos || files[bdir].find(".hpp") != std::string::npos || files[bdir].find(".c") != std::string::npos || files[bdir].find(".h") != std::string::npos){
                        if ( GuiButton( (Rectangle){ 5, (GetScreenHeight()-left_anchor), (GetScreenWidth()*0.12)-10, (GetScreenHeight()*0.04) }, files[bdir].c_str() ) ){
                            state = 0;
                            std::cout << "Running coding sesion\n";
                            textfile = glogal_functions::unconstchar(LoadFileText( (game_path+files[bdir]).c_str() ));  
                            txt_cnt = bdir;
                            coursor_pos = 0;
                            y_text_offset = 0;
                            x_text_offset = 0;
                        }
                    }else if(files[bdir].find(".png") != std::string::npos || files[bdir].find(".bmp") != std::string::npos){
                        if ( GuiButton( (Rectangle){ 5, (GetScreenHeight()-left_anchor), (GetScreenWidth()*0.12)-10, (GetScreenHeight()*0.04) }, files[bdir].c_str() ) ){
                            state = 2;
                            std::cout << "Running image sesion\n";
                            //UnloadImage(current_for_edit);
                            current_for_edit = LoadImage( (game_path+files[bdir]).c_str() ); 
                            whith_image = bdir;
                        }
                    }else{
                        if ( GuiButton( (Rectangle){ 5, (GetScreenHeight()-left_anchor), (GetScreenWidth()*0.12)-10, (GetScreenHeight()*0.04) }, files[bdir].c_str() ) ){
                            working_path = game_path + files[bdir];
                            load_files();
                            std::cout << "Reloading files\n";
                        }
                    }
                    left_anchor += (GetScreenHeight()*0.04) + 5;
                }

                //  right panel
                DrawRectangle(GetScreenWidth()-(GetScreenWidth()*0.2),0,(GetScreenWidth()*0.2),GetScreenHeight(),Color{22,22,22,(unsigned char)fade});
                DrawRectangle(GetScreenWidth()-(GetScreenWidth()*0.2),0,(GetScreenWidth()*0.2),(GetScreenHeight()*0.08),Color{26,26,26,(unsigned char)fade});
                //DrawRectangle(GetScreenWidth()-(GetScreenWidth()*0.2),0,(GetScreenWidth()*0.2),(GetScreenHeight()*0.08),Color{18,18,18,(unsigned char)fade});

                // center up panel
                DrawRectangle((GetScreenWidth()*0.12),0,(GetScreenWidth()-(GetScreenWidth()*0.32)),(GetScreenHeight()*0.08),Color{20,20,20,(unsigned char)fade});
                if(GuiButton( (Rectangle){ (GetScreenWidth()*0.12)+(GetScreenHeight()*0.02), (GetScreenHeight()*0.02), (GetScreenWidth()*0.085), (GetScreenHeight()*0.04) }, state_text )){
                    type_menu = !type_menu;
                }

                if(type_menu){
                    DrawRectangle((GetScreenWidth()*0.12),(GetScreenHeight()*0.08),(GetScreenWidth()*0.085)+16,(GetScreenHeight()*0.08)+8+(GetScreenHeight()*0.04)+24,Color{255,255,255,(unsigned char)fade});
                    DrawRectangle((GetScreenWidth()*0.12)+2,(GetScreenHeight()*0.08)+2,(GetScreenWidth()*0.085)-4+16,(GetScreenHeight()*0.08)+8+(GetScreenHeight()*0.04)+20,Color{18,18,18,(unsigned char)fade});
                    if(GuiButton( (Rectangle){ (GetScreenWidth()*0.12)+8, (GetScreenHeight()*0.08)+8, (GetScreenWidth()*0.085), (GetScreenHeight()*0.04) }, "Coding" )){
                        state = 0;
                        type_menu = 0;
                    }
                    if(GuiButton( (Rectangle){ (GetScreenWidth()*0.12)+8, (GetScreenHeight()*0.08)+8+(GetScreenHeight()*0.04)+8, (GetScreenWidth()*0.085), (GetScreenHeight()*0.04) }, "Map editing" )){
                        state = 1;
                        type_menu = 0;
                    }
                    if(GuiButton( (Rectangle){ (GetScreenWidth()*0.12)+8, (GetScreenHeight()*0.08)+8+(GetScreenHeight()*0.08)+16, (GetScreenWidth()*0.085), (GetScreenHeight()*0.04) }, "Image editing" )){
                        state = 2;
                        type_menu = 0;
                    }
                }


                // Compilation
                float shs = (GetScreenHeight()*0.015);
                float sws = (GetScreenWidth()*0.015);
                if(shs<sws){
                    GuiSetStyle(DEFAULT, TEXT_SIZE, shs);
                    gloabal_font_size = shs;
                }else{
                    GuiSetStyle(DEFAULT, TEXT_SIZE, sws);
                    gloabal_font_size = sws;
                }

                if ( GuiButton( (Rectangle){ GetScreenWidth()-(GetScreenWidth()*0.19), (GetScreenHeight()*0.02), (GetScreenWidth()*0.085), (GetScreenHeight()*0.04) }, "Compile" ) ){   //cempile only
                    if(BOOST_OS_WINDOWS){
                        //std::cout << "Detected Windows" << std::endl;
                        text = "(unsuported yet) Compiled for Windows [Experimental].";
                        g=100;
                        DrawText(text, 5, (GetScreenHeight()*0.03), (GetScreenHeight()*0.02), YELLOW);
                    }else if(BOOST_OS_LINUX){
                        //std::cout << "Detected Linux" << std::endl;
                        text = "Compiled for Linux.";
                        g=100;
                        DrawText(text, 5, (GetScreenHeight()*0.03), (GetScreenHeight()*0.02), YELLOW);
                        sleep_for(1000ns);
                        system("rm -f ../packaged");
                        system("mkdir ../packaged");
                        system("ls ../");
                        system("cp -R ../game ../packaged");
                        system("cp -R ../engine ../packaged");
                        //system("cp -R ../engine/run.sh ../packaged");
                        system("g++ -lstdc++fs -std=c++20 -o ../packaged/app ../engine/engine.cpp -lstdc++fs -lraylib -lGL -lm -lpthread -ldl -lrt -lX11");
                        clear_source_code();
                    }else{
                        //std::cout << "Unsuported OS" << std::endl;
                        text = "Unsuported OS!";
                        g=100;
                        DrawText(text, 5, (GetScreenHeight()*0.03), (GetScreenHeight()*0.02), YELLOW);
                        sleep_for(1000ns);
                    }
                }

                if ( GuiButton( (Rectangle){ GetScreenWidth()-(GetScreenWidth()*0.095), (GetScreenHeight()*0.02), (GetScreenWidth()*0.085), (GetScreenHeight()*0.04) }, "Compile & Run" ) ){    //compile & run
                    if(BOOST_OS_WINDOWS){
                        //std::cout << "Detected Windows" << std::endl;
                        text = "(unsuported yet) Compiled for Windows [Experimental].";
                        g=100;
                        DrawText(text, 5, (GetScreenHeight()*0.03), (GetScreenHeight()*0.02), YELLOW);
                    }else if(BOOST_OS_LINUX){
                        text = "Compiled for Linux.";
                        g=100;
                        DrawText(text, 5, (GetScreenHeight()*0.03), (GetScreenHeight()*0.02), YELLOW);
                        sleep_for(1000ns);
                        system("rm -f ../packaged");
                        system("mkdir ../packaged");
                        system("ls ../");
                        system("cp -R ../game ../packaged");
                        system("cp -R ../engine ../packaged");
                        system("cp -R ../engine/run.sh ../packaged");
                        system("g++ -lstdc++fs -std=c++20 -o ../packaged/app ../engine/engine.cpp -lstdc++fs -lraylib -lGL -lm -lpthread -ldl -lrt -lX11");
                        clear_source_code();
                        system("./../packaged/run.sh");
                        system("rm -f ../packaged/*.sh");
                    }else{
                        //std::cout << "Unsuported OS" << std::endl;
                        text = "Unsuported OS!";
                        g=100;
                        DrawText(text, 5, (GetScreenHeight()*0.03), (GetScreenHeight()*0.02), YELLOW);
                        sleep_for(1000ns);
                    }
                }

                if(g>0){
                    DrawText(text, 15, (GetScreenHeight()*0.98)-15, (GetScreenHeight()*0.02), YELLOW);
                    g--;
                }else{
                    text = path.c_str();
                    if(succes){
                        //nothing
                    }else{
                       DrawText("Working directory failed to change, editor will not work preperly!", 5, (GetScreenHeight()*0.03), (GetScreenHeight()*0.02), RED);
                        DrawText(TextFormat("Path: %s in not valid.", text), 5, (GetScreenHeight()*0.03)+5+(GetScreenHeight()*0.02) , (GetScreenHeight()*0.02), YELLOW);
                    }
                }

            }

        EndDrawing();
        UnloadTexture(texture);
    }
    UnloadImage(current_for_edit);
    CloseWindow();

    return 0;
}
