#include "versus.h"

void GameLoop_TelaDeVersus() {
    if (timermenus == 0) { play_midi(bgm_versus_mode, 0); } //bgm
    int iniciaRound = 0;
    if (key[KEY_ESC]) {
        play_sample(back, 255, 128, 1000, 0);
        timermenus = 0;
        SelectCharMode = 1;
        TelaDeVersus = 0;
        if (ModoHistoria == 0) { strcpy(ChoiceBG, ""); }
        play_midi(bgm_select_screen, 1); //bgm
    }

    TelaDeVersusTimer++;

    int numtemp = 57;

    if ((P[1].key_START_pressed == 1 || P[2].key_START_pressed == 1) && timermenus >= 15) {
        TelaDeVersusTimer = 350 - numtemp;
        zeraListaDeInputs();
        desabilita_players = 1;
    }

    if (TelaDeVersusTimer == 350 - numtemp) {
        FadeIN = 1;
        FadeOUT = 0;
        AnimTransTimer = 0;
    }
    if (TelaDeVersusTimer > 350) {
        iniciaRound = 1;
        desabilita_players = 0;
    }

    if (iniciaRound == 1) {
        iniciaRound = 0;
        timermenus = 0;
        TelaDeVersus = 0;
        GamePlayMode = 1;
        RoundAtual = 1;
        zeraListaDeInputs();
        LOAD_PLAYERS();
        //carrega dados
        set_config_file("SETUP.ini");
        RoundTotal = get_config_int("CONFIG", "rounds", 3);
        RoundTime = get_config_int("CONFIG", "time", 99);
        RoundTime = RoundTime * 60 + 59;
        P[1].Energy = get_config_int("CONFIG", "P1_Energy", 1000);
        P[2].Energy = get_config_int("CONFIG", "P2_Energy", 1000);
        P[1].Special = get_config_int("CONFIG", "P1_Special", 1000);
        P[2].Special = get_config_int("CONFIG", "P2_Special", 1000);
    }

    //bg
    draw_sprite(bufferx, VS_SCREEN, 0, 0);
    //P1
    masked_stretch_blit(P1BIGDisplay, bufferx, 0, 0, 128, 128, 5, 140, 256, 256);
    //P2
    clear_to_color(P2BIGDisplayInv, makecol(255, 0, 255));
    draw_sprite_h_flip(P2BIGDisplayInv, P2BIGDisplay, 0, 0);
    masked_stretch_blit(P2BIGDisplayInv, bufferx, 0, 0, 128, 128, 379, 140, 256, 256);
    //VS
    draw_sprite(bufferx, vs_icon, 195, 20);
    //informacoes
    //sombra
    textprintf_centre_ex(bufferx, font_debug, 152, 405, makecol(000, 000, 000), -1, "P1 WINS: %i", P[1].Wins);
    textprintf_centre_ex(bufferx, font_debug, 152, 420, makecol(000, 000, 000), -1, "P1 LOSES: %i", P[1].Loses);
    textprintf_centre_ex(bufferx, font_debug, 152, 435, makecol(000, 000, 000), -1, "P1 DRAWS: %i", P[1].Draws);
    textprintf_centre_ex(bufferx, font_debug, 152, 450, makecol(000, 000, 000), -1, "P1 PERFECTS: %i", P[1].Perfects);
    textprintf_centre_ex(bufferx, font_debug, 492, 405, makecol(000, 000, 000), -1, "P2 WINS: %i", P[2].Wins);
    textprintf_centre_ex(bufferx, font_debug, 492, 420, makecol(000, 000, 000), -1, "P2 LOSES: %i", P[2].Loses);
    textprintf_centre_ex(bufferx, font_debug, 492, 435, makecol(000, 000, 000), -1, "P2 DRAWS: %i", P[2].Draws);
    textprintf_centre_ex(bufferx, font_debug, 492, 450, makecol(000, 000, 000), -1, "P2 PERFECTS: %i", P[2].Perfects);
    //texto
    textprintf_centre_ex(bufferx, font_debug, 150, 403, makecol(255, 255, 255), -1, "P1 WINS: %i", P[1].Wins);
    textprintf_centre_ex(bufferx, font_debug, 150, 418, makecol(255, 255, 255), -1, "P1 LOSES: %i", P[1].Loses);
    textprintf_centre_ex(bufferx, font_debug, 150, 433, makecol(255, 255, 255), -1, "P1 DRAWS: %i", P[1].Draws);
    textprintf_centre_ex(bufferx, font_debug, 150, 448, makecol(255, 255, 255), -1, "P1 PERFECTS: %i", P[1].Perfects);
    textprintf_centre_ex(bufferx, font_debug, 490, 403, makecol(255, 255, 255), -1, "P2 WINS: %i", P[2].Wins);
    textprintf_centre_ex(bufferx, font_debug, 490, 418, makecol(255, 255, 255), -1, "P2 LOSES: %i", P[2].Loses);
    textprintf_centre_ex(bufferx, font_debug, 490, 433, makecol(255, 255, 255), -1, "P2 DRAWS: %i", P[2].Draws);
    textprintf_centre_ex(bufferx, font_debug, 490, 448, makecol(255, 255, 255), -1, "P2 PERFECTS: %i", P[2].Perfects);

    stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}
