 
void draw_debug(bool show_debug,bool vsync) {

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
}