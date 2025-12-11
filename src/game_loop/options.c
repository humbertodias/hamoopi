#pragma once

#include "options.h"

void GameLoop_OptionsMode() {
    if (timermenus >= 15) {
        int salvardados = 0;
        if (key[KEY_ESC]) {
            play_sample(back, 255, 128, 1000, 0);
            timermenus = 0;
            FadeCtr = 255;
            FadeIN = 0;
            FadeOUT = 1;
            menu_op = 1;
            ApresentacaoMode = 1;
            OptionsMode = 0;
            salvardados = 1;
        }
        if (key[KEY_ALT] && key[KEY_F4]) { sair = 1; }
        if (P[1].key_START_pressed == 1 && options_op == 15) {
            play_sample(confirm, 255, 128, 1000, 0);
            timermenus = 0;
            FadeCtr = 255;
            FadeIN = 0;
            FadeOUT = 1;
            menu_op = 1;
            ApresentacaoMode = 1;
            OptionsMode = 0;
            salvardados = 1;
        }
        if (P[1].key_UP_pressed == 1) {
            options_op--;
            play_sample(cursor, 255, 128, 1000, 0);
            if (options_op < 1) { options_op = 15; }
        }
        if (P[1].key_DOWN_pressed == 1) {
            options_op++;
            play_sample(cursor, 255, 128, 1000, 0);
            if (options_op > 15) { options_op = 1; }
        }

        if (salvardados == 1) {
            salvardados = 0;
            //salva dados
            set_config_file("SETUP.ini");
            set_config_string("CONFIG", "language", IDIOMA);
            set_config_int("CONFIG", "rounds", RoundTotal);
            set_config_int("CONFIG", "time", RoundTime/60);
            set_config_int("CONFIG", "P1_Energy", P[1].Energy);
            set_config_int("CONFIG", "P2_Energy", P[2].Energy);
            set_config_int("CONFIG", "P1_Special", P[1].Special);
            set_config_int("CONFIG", "P2_Special", P[2].Special);
            set_config_int("CONFIG", "FullScreen", ModoFullscreen);
            set_config_int("CONFIG", "draw_shadows", op_desenhar_sombras);
            set_config_int("CONFIG", "zoom", op_Zoom);
            set_config_int("CONFIG", "show_inputs", Draw_Input);
            set_config_int("CONFIG", "window_res_x", WindowResX);
            set_config_int("CONFIG", "window_res_y", WindowResY);
            set_config_int("CONFIG", "frame_data", op_ShowFrameData);
            set_volume(op_sfx_volume, op_sound_volume);
        }
    }

    if (timermenus == 0) {
        set_config_file("SETUP.ini");
        RoundTotal = get_config_int("CONFIG", "rounds", 3);
        RoundTime = get_config_int("CONFIG", "time", 99);
        RoundTime = RoundTime * 60 + 59;
        P[1].Energy = get_config_int("CONFIG", "P1_Energy", 1000);
        P[2].Energy = get_config_int("CONFIG", "P2_Energy", 1000);
        P[1].Special = get_config_int("CONFIG", "P1_Special", 1000);
        P[2].Special = get_config_int("CONFIG", "P2_Special", 1000);
        ModoFullscreen = get_config_int("CONFIG", "FullScreen", 0);
        op_desenhar_sombras = get_config_int("CONFIG", "draw_shadows", 1);
        op_Zoom = get_config_int("CONFIG", "zoom", 1);
        Draw_Input = get_config_int("CONFIG", "show_inputs", 0);
        op_sound_volume = get_config_int("CONFIG", "sound_volume", 255);
        op_sfx_volume = get_config_int("CONFIG", "sfx_volume", 255);
        WindowResX = get_config_int("CONFIG", "window_res_x", 640);
        WindowResY = get_config_int("CONFIG", "window_res_y", 480);
        if (WindowResX == 320 && WindowResY == 240) WindowResNumber = 1;
        if (WindowResX == 640 && WindowResY == 480) WindowResNumber = 2;
        if (WindowResX == 720 && WindowResY == 480) WindowResNumber = 3; //SD
        if (WindowResX == 800 && WindowResY == 600) WindowResNumber = 4;
        if (WindowResX == 960 && WindowResY == 640) WindowResNumber = 5;
        if (WindowResX == 960 && WindowResY == 720) WindowResNumber = 6;
        if (WindowResX == 1024 && WindowResY == 600) WindowResNumber = 7;
        if (WindowResX == 1280 && WindowResY == 720) WindowResNumber = 8; //HD
    }

    draw_sprite(bufferx, GAME_options, 0, 0);
    int espacamento = 22;
    if (options_op == 1) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 0)); }
    if (options_op == 2) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 1)); }
    if (options_op == 3) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 2)); }
    if (options_op == 4) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 3)); }
    if (options_op == 5) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 4)); }
    if (options_op == 6) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 5)); }
    if (options_op == 7) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 6)); }
    if (options_op == 8) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 7)); }
    if (options_op == 9) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 8)); }
    if (options_op == 10) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento* 9)); }
    if (options_op == 11) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*10)); }
    if (options_op == 12) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*11)); }
    if (options_op == 13) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*12)); }
    if (options_op == 14) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*13)); }
    if (options_op == 15) { draw_sprite(bufferx, spr_menu_icon, 130, 70+(espacamento*14)); }

    //desenha valores configuraveis

    if (strcmp(IDIOMA, "US") == 0) {
        draw_sprite(bufferx, flag_US, 422, 58);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 0), makecol(025, 025, 025), -1, "Language: %s",
                      IDIOMA);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 1), makecol(025, 025, 025), -1, "Rounds: %i",
                      RoundTotal);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 2), makecol(025, 025, 025), -1, "Timer: %i",
                      RoundTime / 60);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 3), makecol(025, 025, 025), -1, "P1 Energy: %i",
                      P[1].Energy / 10);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 4), makecol(025, 025, 025), -1, "P1 Special: %i",
                      P[1].Special / 10);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 5), makecol(025, 025, 025), -1, "P2 Energy: %i",
                      P[2].Energy / 10);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 6), makecol(025, 025, 025), -1, "P2 Special: %i",
                      P[2].Special / 10);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 7), makecol(025, 025, 025), -1, "Full Screen: %i",
                      ModoFullscreen);
        if (WindowResNumber == 1)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 320x240");
        if (WindowResNumber == 2)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 640x480");
        if (WindowResNumber == 3)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 720x480");
        if (WindowResNumber == 4)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 800x600");
        if (WindowResNumber == 5)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 960x640");
        if (WindowResNumber == 6)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 960x720");
        if (WindowResNumber == 7)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 1024x600");
        if (WindowResNumber == 8)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 1280x720");
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 9), makecol(025, 025, 025), -1, "Draw Shadows: %i",
                      op_desenhar_sombras);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 10), makecol(025, 025, 025), -1, "Enable Zoom: %i",
                      op_Zoom);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 11), makecol(025, 025, 025), -1, "Draw Inputs: %i",
                      Draw_Input);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 12), makecol(025, 025, 025), -1, "Frame Data: %i",
                      op_ShowFrameData);

        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 14), makecol(025, 025, 025), -1, "EXIT");
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 0), makecol(255, 255, 255), -1, "Language: %s",
                      IDIOMA);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 1), makecol(255, 255, 255), -1, "Rounds: %i",
                      RoundTotal);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 2), makecol(255, 255, 255), -1, "Timer: %i",
                      RoundTime / 60);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 3), makecol(255, 255, 255), -1, "P1 Energy: %i",
                      P[1].Energy / 10);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 4), makecol(255, 255, 255), -1, "P1 Special: %i",
                      P[1].Special / 10);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 5), makecol(255, 255, 255), -1, "P2 Energy: %i",
                      P[2].Energy / 10);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 6), makecol(255, 255, 255), -1, "P2 Special: %i",
                      P[2].Special / 10);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 7), makecol(255, 255, 255), -1, "Full Screen: %i",
                      ModoFullscreen);
        if (WindowResNumber == 1)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 320x240");
        if (WindowResNumber == 2)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 640x480");
        if (WindowResNumber == 3)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 720x480");
        if (WindowResNumber == 4)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 800x600");
        if (WindowResNumber == 5)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 960x640");
        if (WindowResNumber == 6)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 960x720");
        if (WindowResNumber == 7)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 1024x600");
        if (WindowResNumber == 8)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 1280x720");
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 9), makecol(255, 255, 255), -1, "Draw Shadows: %i",
                      op_desenhar_sombras);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 10), makecol(255, 255, 255), -1, "Enable Zoom: %i",
                      op_Zoom);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 11), makecol(255, 255, 255), -1, "Draw Inputs: %i",
                      Draw_Input);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 12), makecol(255, 255, 255), -1, "Frame Data: %i",
                      op_ShowFrameData);

        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 14), makecol(255, 010, 005), -1, "EXIT");
        if (options_op == 1)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 0), makecol(255, 170, 000), -1, "Language: %s",
                          IDIOMA);
        if (options_op == 2)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 1), makecol(255, 170, 000), -1, "Rounds: %i",
                          RoundTotal);
        if (options_op == 3)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 2), makecol(255, 170, 000), -1, "Timer: %i",
                          RoundTime / 60);
        if (options_op == 4)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 3), makecol(255, 170, 000), -1, "P1 Energy: %i",
                          P[1].Energy / 10);
        if (options_op == 5)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 4), makecol(255, 170, 000), -1, "P1 Special: %i",
                          P[1].Special / 10);
        if (options_op == 6)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 5), makecol(255, 170, 000), -1, "P2 Energy: %i",
                          P[2].Energy / 10);
        if (options_op == 7)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 6), makecol(255, 170, 000), -1, "P2 Special: %i",
                          P[2].Special / 10);
        if (options_op == 8)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 7), makecol(255, 170, 000), -1, "Full Screen: %i",
                          ModoFullscreen);
        if (options_op == 9) {
            if (WindowResNumber == 1)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 320x240");
            if (WindowResNumber == 2)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 640x480");
            if (WindowResNumber == 3)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 720x480");
            if (WindowResNumber == 4)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 800x600");
            if (WindowResNumber == 5)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 960x640");
            if (WindowResNumber == 6)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 960x720");
            if (WindowResNumber == 7)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 1024x600");
            if (WindowResNumber == 8)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 1280x720");
        }
        if (options_op == 10)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 9), makecol(255, 170, 000), -1, "Draw Shadows: %i",
                          op_desenhar_sombras);
        if (options_op == 11)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 10), makecol(255, 170, 000), -1, "Enable Zoom: %i",
                          op_Zoom);
        if (options_op == 12)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 11), makecol(255, 170, 000), -1, "Draw Inputs: %i",
                          Draw_Input);
        if (options_op == 13)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 12), makecol(255, 170, 000), -1, "Frame Data: %i",
                          op_ShowFrameData);

        if (options_op == 15)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 14), makecol(255, 170, 000), -1, "EXIT");
    }

    if (strcmp(IDIOMA, "BR") == 0) {
        draw_sprite(bufferx, flag_BR, 422, 58);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 0), makecol(025, 025, 025), -1, "Idioma: %s", IDIOMA);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 1), makecol(025, 025, 025), -1, "Rounds: %i",
                      RoundTotal);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 2), makecol(025, 025, 025), -1, "Relógio: %i",
                      RoundTime / 60);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 3), makecol(025, 025, 025), -1, "P1 Energia: %i",
                      P[1].Energy / 10);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 4), makecol(025, 025, 025), -1, "P1 Especial: %i",
                      P[1].Special / 10);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 5), makecol(025, 025, 025), -1, "P2 Energia: %i",
                      P[2].Energy / 10);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 6), makecol(025, 025, 025), -1, "P2 Especial: %i",
                      P[2].Special / 10);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 7), makecol(025, 025, 025), -1, "Tela Cheia: %i",
                      ModoFullscreen);
        if (WindowResNumber == 1)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 320x240");
        if (WindowResNumber == 2)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 640x480");
        if (WindowResNumber == 3)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 720x480");
        if (WindowResNumber == 4)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 800x600");
        if (WindowResNumber == 5)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 960x640");
        if (WindowResNumber == 6)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 960x720");
        if (WindowResNumber == 7)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 1024x600");
        if (WindowResNumber == 8)
            textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 8), makecol(025, 025, 025), -1,
                          "Win Res: 1280x720");
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 9), makecol(025, 025, 025), -1, "Desenhar Sombras: %i",
                      op_desenhar_sombras);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 10), makecol(025, 025, 025), -1, "Ativar Zoom: %i",
                      op_Zoom);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 11), makecol(025, 025, 025), -1, "Desenhar Inputs: %i",
                      Draw_Input);
        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 12), makecol(025, 025, 025), -1, "Frame Data: %i",
                      op_ShowFrameData);

        textprintf_ex(bufferx, font_20, 192, 82 + (espacamento * 14), makecol(025, 025, 025), -1, "SAIR");
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 0), makecol(255, 255, 255), -1, "Idioma: %s", IDIOMA);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 1), makecol(255, 255, 255), -1, "Rounds: %i",
                      RoundTotal);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 2), makecol(255, 255, 255), -1, "Relógio: %i",
                      RoundTime / 60);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 3), makecol(255, 255, 255), -1, "P1 Energia: %i",
                      P[1].Energy / 10);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 4), makecol(255, 255, 255), -1, "P1 Especial: %i",
                      P[1].Special / 10);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 5), makecol(255, 255, 255), -1, "P2 Energia: %i",
                      P[2].Energy / 10);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 6), makecol(255, 255, 255), -1, "P2 Especial: %i",
                      P[2].Special / 10);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 7), makecol(255, 255, 255), -1, "Tela Cheia: %i",
                      ModoFullscreen);
        if (WindowResNumber == 1)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 320x240");
        if (WindowResNumber == 2)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 640x480");
        if (WindowResNumber == 3)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 720x480");
        if (WindowResNumber == 4)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 800x600");
        if (WindowResNumber == 5)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 960x640");
        if (WindowResNumber == 6)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 960x720");
        if (WindowResNumber == 7)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 1024x600");
        if (WindowResNumber == 8)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 255, 255), -1,
                          "Win Res: 1280x720");
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 9), makecol(255, 255, 255), -1, "Desenhar Sombras: %i",
                      op_desenhar_sombras);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 10), makecol(255, 255, 255), -1, "Ativar Zoom: %i",
                      op_Zoom);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 11), makecol(255, 255, 255), -1, "Desenhar Inputs: %i",
                      Draw_Input);
        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 12), makecol(255, 255, 255), -1, "Frame Data: %i",
                      op_ShowFrameData);

        textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 14), makecol(255, 010, 005), -1, "SAIR");
        if (options_op == 1)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 0), makecol(255, 170, 000), -1, "Idioma: %s",
                          IDIOMA);
        if (options_op == 2)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 1), makecol(255, 170, 000), -1, "Rounds: %i",
                          RoundTotal);
        if (options_op == 3)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 2), makecol(255, 170, 000), -1, "Relógio: %i",
                          RoundTime / 60);
        if (options_op == 4)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 3), makecol(255, 170, 000), -1, "P1 Energia: %i",
                          P[1].Energy / 10);
        if (options_op == 5)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 4), makecol(255, 170, 000), -1, "P1 Especial: %i",
                          P[1].Special / 10);
        if (options_op == 6)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 5), makecol(255, 170, 000), -1, "P2 Energia: %i",
                          P[2].Energy / 10);
        if (options_op == 7)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 6), makecol(255, 170, 000), -1, "P2 Especial: %i",
                          P[2].Special / 10);
        if (options_op == 8)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 7), makecol(255, 170, 000), -1, "Tela Cheia: %i",
                          ModoFullscreen);
        if (options_op == 9) {
            if (WindowResNumber == 1)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 320x240");
            if (WindowResNumber == 2)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 640x480");
            if (WindowResNumber == 3)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 720x480");
            if (WindowResNumber == 4)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 800x600");
            if (WindowResNumber == 5)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 960x640");
            if (WindowResNumber == 6)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 960x720");
            if (WindowResNumber == 7)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 1024x600");
            if (WindowResNumber == 8)
                textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 8), makecol(255, 170, 000), -1,
                              "Win Res: 1280x720");
        }
        if (options_op == 10)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 9), makecol(255, 170, 000), -1,
                          "Desenhar Sombras: %i", op_desenhar_sombras);
        if (options_op == 11)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 10), makecol(255, 170, 000), -1, "Ativar Zoom: %i",
                          op_Zoom);
        if (options_op == 12)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 11), makecol(255, 170, 000), -1,
                          "Desenhar Inputs: %i", Draw_Input);
        if (options_op == 13)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 12), makecol(255, 170, 000), -1, "Frame Data: %i",
                          op_ShowFrameData);

        if (options_op == 15)
            textprintf_ex(bufferx, font_20, 190, 80 + (espacamento * 14), makecol(255, 170, 000), -1, "SAIR");
    }

    //altera valores configuraveis
    if (P[1].key_RIGHT_pressed == 1 && options_op == 1) { strcpy(IDIOMA, "BR"); }
    if (P[1].key_LEFT_pressed == 1 && options_op == 1) { strcpy(IDIOMA, "US"); }
    if (P[1].key_RIGHT_pressed == 1 && options_op == 2 && RoundTotal <= 4) { RoundTotal = RoundTotal + 1; }
    if (P[1].key_LEFT_pressed == 1 && options_op == 2 && RoundTotal >= 2) { RoundTotal = RoundTotal - 1; }
    if ((/*P[1].key_RIGHT_pressed ==1 || */P[1].key_RIGHT_hold == 1) && options_op == 3 && RoundTime <= 60 * 99) {
        RoundTime = RoundTime + 60;
        if (RoundTime > 60 * 99)RoundTime = 60 * 99;
    }
    if ((/*P[1].key_LEFT_pressed  ==1 || */P[1].key_LEFT_hold == 1) && options_op == 3 && RoundTime >= 66 * 10) {
        RoundTime = RoundTime - 60;
        if (RoundTime < 60 * 10)RoundTime = 60 * 10;
    }
    if (P[1].key_RIGHT_pressed == 1 && options_op == 4 && P[1].Energy < 1000) { P[1].Energy = P[1].Energy + 100; }
    if (P[1].key_LEFT_pressed == 1 && options_op == 4 && P[1].Energy > 100) { P[1].Energy = P[1].Energy - 100; }
    if (P[1].key_RIGHT_pressed == 1 && options_op == 5 && P[1].Special < 1000) { P[1].Special = P[1].Special + 100; }
    if (P[1].key_LEFT_pressed == 1 && options_op == 5 && P[1].Special > 0) { P[1].Special = P[1].Special - 100; }
    if (P[1].key_RIGHT_pressed == 1 && options_op == 6 && P[2].Energy < 1000) { P[2].Energy = P[2].Energy + 100; }
    if (P[1].key_LEFT_pressed == 1 && options_op == 6 && P[2].Energy > 100) { P[2].Energy = P[2].Energy - 100; }
    if (P[1].key_RIGHT_pressed == 1 && options_op == 7 && P[2].Special < 1000) { P[2].Special = P[2].Special + 100; }
    if (P[1].key_LEFT_pressed == 1 && options_op == 7 && P[2].Special > 0) { P[2].Special = P[2].Special - 100; }
    if (P[1].key_RIGHT_pressed == 1 && options_op == 8 && ModoFullscreen == 0) {
        ModoFullscreen = 1;
        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 640, 480, 0, 0);
    }
    if (P[1].key_LEFT_pressed == 1 && options_op == 8 && ModoFullscreen == 1) {
        ModoFullscreen = 0;
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, WindowResX, WindowResY, 0, 0);
    }
    if (P[1].key_RIGHT_pressed == 1 && options_op == 9 && WindowResNumber <= 7) { WindowResNumber++; }
    if (P[1].key_LEFT_pressed == 1 && options_op == 9 && WindowResNumber >= 2) { WindowResNumber--; }
    if (P[1].key_START_pressed == 1 && options_op == 9 && ModoFullscreen == 0) {
        if (WindowResNumber == 1) {
            WindowResX = 320;
            WindowResY = 240;
        }
        if (WindowResNumber == 2) {
            WindowResX = 640;
            WindowResY = 480;
        }
        if (WindowResNumber == 3) {
            WindowResX = 720;
            WindowResY = 480;
        }
        if (WindowResNumber == 4) {
            WindowResX = 800;
            WindowResY = 600;
        }
        if (WindowResNumber == 5) {
            WindowResX = 960;
            WindowResY = 640;
        }
        if (WindowResNumber == 6) {
            WindowResX = 960;
            WindowResY = 720;
        }
        if (WindowResNumber == 7) {
            WindowResX = 1024;
            WindowResY = 600;
        }
        if (WindowResNumber == 8) {
            WindowResX = 1280;
            WindowResY = 720;
        }
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, WindowResX, WindowResY, 0, 0);
    }
    if (P[1].key_LEFT_pressed == 1 && options_op == 10) op_desenhar_sombras = 0;
    if (P[1].key_RIGHT_pressed == 1 && options_op == 10) op_desenhar_sombras = 1;
    if (P[1].key_LEFT_pressed == 1 && options_op == 11) op_Zoom = 0;
    if (P[1].key_RIGHT_pressed == 1 && options_op == 11) op_Zoom = 1;
    if (P[1].key_LEFT_pressed == 1 && options_op == 12) Draw_Input = 0;
    if (P[1].key_RIGHT_pressed == 1 && options_op == 12) Draw_Input = 1;
    if (P[1].key_LEFT_pressed == 1 && options_op == 13) op_ShowFrameData = 0;
    if (P[1].key_RIGHT_pressed == 1 && options_op == 13) op_ShowFrameData = 1;

    stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}
