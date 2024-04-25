#ifndef INTRO_CXX
#define INTRO_CXX

#include <raylib.h>
#include <raymath.h>

#include "../scene.cpp"

namespace Intro {
    Sound intro_Sound;
    Texture intro_Texture;

    int tick = 0.f;
    int blink_Countdown = 0;
    
    void Init() {
        intro_Sound = LoadSound("audio/intro.wav");
        intro_Texture = LoadTexture("textures/logo.png");
        PlaySound(intro_Sound);

        tick = 0.f;
        blink_Countdown = 0;
    }

    void Update() {
        ClearBackground(BLACK);

        // Dammit, the first day of coding and the code is already garbage
        // Dont fucking know what this code does

        // TODO: Add some useful comments

        tick++;
        float opacity_Logo = 0.f;
        float opacity_Light = 0.f;

        if(tick < GetFPS() * 2) {
            opacity_Light = 255;
            if(blink_Countdown < 0) {
                blink_Countdown = rand() % 20;
            } else {
                opacity_Light -= blink_Countdown * 10.f;
                blink_Countdown--;
            }
            opacity_Light = opacity_Light > 200 ? 255 : 0;
        } else {
            opacity_Light = 255;
        }

        opacity_Logo = 255;

        // God damn, why would you even set the FPS to 0?!
        if(GetFPS() != 0) {
            if(tick > GetFPS() * 6) {
                Switch_To_Scene(GAME);
            }
        }

        opacity_Logo = Clamp(opacity_Logo, 0.f, 255.f);
        opacity_Light = Clamp(opacity_Light, 0.f, 255.f);

        DrawEllipse(GetScreenWidth() / 2, GetScreenHeight() / 1.5, 200.f, 100.f, Color {255, 255, 255, (unsigned char)opacity_Light});

        DrawTexture(intro_Texture, GetScreenWidth() / 2 - intro_Texture.width / 2, GetScreenHeight() / 2 - intro_Texture.height / 2, Color {255, 255, 255, (unsigned char)opacity_Logo});
        DrawTriangle({GetScreenWidth() / 2.f - 200.f, GetScreenHeight() / 1.5f},
                     {GetScreenWidth() / 2.f + 200.f, GetScreenHeight() / 1.5f},
                     {GetScreenWidth() / 2.f, 50.f}, Color {255, 255, 255, (unsigned char)(opacity_Light / 4.f)});
        
        DrawTriangle({GetScreenWidth() / 2.f - 200.f, GetScreenHeight() / 1.5f},
                     {GetScreenWidth() / 2.f, GetScreenHeight() / 1.3f},
                     {GetScreenWidth() / 2.f + 200.f, GetScreenHeight() / 1.5f}, Color {255, 255, 255, (unsigned char)(opacity_Light / 4.f)});
    
        if(tick < GetFPS() * 1) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color {0, 0, 0, (unsigned char)Remap(tick, 0.f, GetFPS() * 1.f, 255.f, 0.f)});
        } else if(tick > GetFPS() * 3) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color {0, 0, 0, (unsigned char)Remap(Clamp(tick, GetFPS() * 3.f, GetFPS() * 5.f), GetFPS() * 3.f, GetFPS() * 5.f, 0.f, 255.f)});
        }
    }
};

#endif // INTRO_CXX