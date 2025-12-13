#include "intro.h"

void GameLoop_IntroMode() {
    if (timermenus == 0) {
        play_sample(intro, 255, 128, 1000, 0);
    }

    IntroTimer++;
    P[1].Pode_Mexer = 1;
    P[2].Pode_Mexer = 1;

    if (timermenus == 15) {
        if (key[KEY_ESC]) { sair = 1; }
        if (key[KEY_ALT] && key[KEY_F4]) { sair = 1; }
        if (P[1].key_START_pressed == 1) {
            timermenus = 0;
            FadeCtr = 255;
            FadeIN = 0;
            FadeOUT = 1;
            IntroMode = 0;
            IntroTimer = 0;
            DonationScreen = 1;
        }
    }

    if (IntroTimer == 300 - 30) {
        FadeIN = 1;
        FadeOUT = 0;
    }
    if (IntroTimer >= 300) {
        timermenus = 0;
        IntroMode = 0;
        IntroTimer = 0;
        DonationScreen = 1;
    }
    draw_sprite(bufferx, GAME_intro, 0, 0);
    stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}
