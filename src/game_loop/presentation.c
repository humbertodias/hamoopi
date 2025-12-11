#include "presentation.h"

void GameLoop_ApresentacaoMode() {
    if (timermenus == 0) {
        play_midi(bgm_apresentacao, 1);
        FadeIN = 0;
        FadeOUT = 1;
    } //bgm
    draw_sprite(bufferx, GAME_logo, 0, 0);

    // atencao! modo Arcade desativado no momento!!! //
    /*temporario*/
    if (timermenus == 0) { menu_op = 2; }
    if (menu_op == 1) { menu_op = 2; } /*temporario*/

    if (timermenus == 15) {
        if (P[1].key_UP_pressed == 1) {
            menu_op--;
            play_sample(cursor, 255, 128, 1000, 0);
            if (menu_op < 1) { menu_op = 5; }
        }
        if (P[1].key_DOWN_pressed == 1) {
            menu_op++;
            play_sample(cursor, 255, 128, 1000, 0);
            if (menu_op > 5) { menu_op = 1; }
        }
        //if (P[1].key_START_pressed==1 && menu_op==1) { play_sample(confirm, 255, 128, 1000, 0); timermenus=0; FadeCtr=255; FadeIN=0; FadeOUT=1; menu_op=1; ApresentacaoMode=0; SelectCharMode=1; ModoHistoria=1; }
        if (P[1].key_START_pressed == 1 && menu_op == 2) {
            play_sample(confirm, 255, 128, 1000, 0);
            timermenus = 0;
            FadeCtr = 255;
            FadeIN = 0;
            FadeOUT = 1;
            menu_op = 1;
            ApresentacaoMode = 0;
            SelectCharMode = 1;
            strcpy(ChoiceP2, "");
            strcpy(P[2].Name, "");
        }
        if (P[1].key_START_pressed == 1 && menu_op == 3) {
            play_sample(confirm, 255, 128, 1000, 0);
            timermenus = 0;
            FadeCtr = 255;
            FadeIN = 0;
            FadeOUT = 1;
            menu_op = 1;
            ApresentacaoMode = 0;
            EditMode = 1;
        }
        if (P[1].key_START_pressed == 1 && menu_op == 4) {
            play_sample(confirm, 255, 128, 1000, 0);
            timermenus = 0;
            FadeCtr = 255;
            FadeIN = 0;
            FadeOUT = 1;
            menu_op = 1;
            ApresentacaoMode = 0;
            OptionsMode = 1;
            options_op = 1;
        }
        if (P[1].key_START_pressed == 1 && menu_op == 5) { sair = 1; }
        if (key[KEY_ALT] && key[KEY_F4]) { sair = 1; }
        if (key[KEY_ESC]) { sair = 1; }
    }
    strcpy(ChoiceP1, "");
    strcpy(ChoiceP2, "");
    strcpy(ChoiceBG, "");
    int espacamento = 30;
    if (menu_op == 1) { draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*0)); }
    if (menu_op == 2) { draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*1)); }
    if (menu_op == 3) { draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*2)); }
    if (menu_op == 4) { draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*3)); }
    if (menu_op == 5) { draw_sprite(bufferx, spr_menu_icon, 180, 225+(espacamento*4)); }

    if (strcmp(IDIOMA, "US") == 0) {
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 0, makecol(000, 000, 000), -1, "ARCADE");
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 1, makecol(000, 000, 000), -1, "VERSUS");
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 2, makecol(000, 000, 000), -1, "EDITOR");
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 3, makecol(000, 000, 000), -1, "OPTIONS");
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 4, makecol(000, 000, 000), -1, "EXIT");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 0, makecol(155, 155, 155), -1, "ARCADE");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 1, makecol(255, 255, 255), -1, "VERSUS");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 2, makecol(255, 255, 255), -1, "EDITOR");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 3, makecol(255, 255, 255), -1, "OPTIONS");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 4, makecol(255, 010, 005), -1, "EXIT");
        if (menu_op == 1)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 0, makecol(255, 170, 000), -1, "ARCADE");
        if (menu_op == 2)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 1, makecol(255, 170, 000), -1, "VERSUS");
        if (menu_op == 3)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 2, makecol(255, 170, 000), -1, "EDITOR");
        if (menu_op == 4)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 3, makecol(255, 170, 000), -1, "OPTIONS");
        if (menu_op == 5)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 4, makecol(255, 170, 000), -1, "EXIT");
    }
    if (strcmp(IDIOMA, "BR") == 0) {
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 0, makecol(000, 000, 000), -1, "ARCADE");
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 1, makecol(000, 000, 000), -1, "VERSUS");
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 2, makecol(000, 000, 000), -1, "EDITOR");
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 3, makecol(000, 000, 000), -1, "OPÇÕES");
        textprintf_centre_ex(bufferx, font_30, 322, 227 + 30 * 4, makecol(000, 000, 000), -1, "SAIR");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 0, makecol(155, 155, 155), -1, "ARCADE");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 1, makecol(255, 255, 255), -1, "VERSUS");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 2, makecol(255, 255, 255), -1, "EDITOR");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 3, makecol(255, 255, 255), -1, "OPÇÕES");
        textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 4, makecol(255, 010, 005), -1, "SAIR");
        if (menu_op == 1)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 0, makecol(255, 170, 000), -1, "ARCADE");
        if (menu_op == 2)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 1, makecol(255, 170, 000), -1, "VERSUS");
        if (menu_op == 3)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 2, makecol(255, 170, 000), -1, "EDITOR");
        if (menu_op == 4)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 3, makecol(255, 170, 000), -1, "OPÇÕES");
        if (menu_op == 5)
            textprintf_centre_ex(bufferx, font_30, 320, 225 + 30 * 4, makecol(255, 170, 000), -1, "SAIR");
    }

    //versao da HAMOOPI
    textprintf_right_ex(bufferx, font_debug, 629, 457, makecol(000, 000, 000), -1, "%s", versao); //sombra do texto
    textprintf_right_ex(bufferx, font_debug, 627, 455, makecol(255, 255, 255), -1, "%s", versao); //texto

    stretch_blit(bufferx, bufferx, 0, 0, 640, 480, 0, 0, 640, 480);
}
