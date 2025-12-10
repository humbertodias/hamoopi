#ifndef HAMOOPI_PLAYER_H
#define HAMOOPI_PLAYER_H

#include "../backend/platform_compat.h"
#include "../core/types.h"
#include "../core/globals.h"
#include "../modules/collision.h"

// Player state management functions
void LOAD_PLAYERS();
void PLAYER_STATE(int Player, int State, int AnimIndex, int QtdeFrames);
void AddTableAtlas(int PlayerInd, int State, int AnimIndex, int TotImg);
void New_Fireball(int Player);
void New_HitBox(int Qtde_HitBoxes);

#endif // HAMOOPI_PLAYER_H
