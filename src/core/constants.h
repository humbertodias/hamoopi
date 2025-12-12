#ifndef HAMOOPI_CONSTANTS_H
#define HAMOOPI_CONSTANTS_H

/**
 * @file constants.h
 * @brief Constantes globais do motor HAMOOPI
 * 
 * Este arquivo centraliza todos os valores constantes usados no jogo,
 * melhorando a manutenibilidade e legibilidade do código.
 */

// ============================================================================
// CONFIGURAÇÕES DE VÍDEO
// ============================================================================

// Resoluções padrão suportadas
#define RES_320x240_WIDTH   320
#define RES_320x240_HEIGHT  240
#define RES_640x480_WIDTH   640
#define RES_640x480_HEIGHT  480
#define RES_720x480_WIDTH   720
#define RES_720x480_HEIGHT  480
#define RES_800x600_WIDTH   800
#define RES_800x600_HEIGHT  600
#define RES_960x640_WIDTH   960
#define RES_960x640_HEIGHT  640
#define RES_960x720_WIDTH   960
#define RES_960x720_HEIGHT  720
#define RES_1024x600_WIDTH  1024
#define RES_1024x600_HEIGHT 600
#define RES_1280x720_WIDTH  1280
#define RES_1280x720_HEIGHT 720

// Resolução base do jogo (referência)
#define GAME_BASE_WIDTH     640
#define GAME_BASE_HEIGHT    480

// Tamanhos de buffers de renderização
#define BUFFER_MAX_WIDTH    2560
#define BUFFER_MAX_HEIGHT   1920
#define BACKGROUND_MAX_WIDTH  1280
#define BACKGROUND_MAX_HEIGHT 960

// ============================================================================
// CONFIGURAÇÕES DE JOGO
// ============================================================================

// Frame rate
#define DEFAULT_FPS         60
#define MIN_FPS             30
#define MAX_FPS             120

// Limites de jogadores e entidades
#define MAX_PLAYERS         2
#define PLAYER_ARRAY_SIZE   3  // índice 0 não usado, 1 e 2 para jogadores
#define MAX_FIREBALLS       3
#define MAX_HIT_SPARKS      99

// Limites de personagens e cenários
#define MAX_CHARACTERS      8
#define MAX_STAGES          8
#define MAX_SPRITE_ATLAS    501

// Hitboxes e Hurtboxes
#define MAX_HITBOXES        9
#define MAX_HURTBOXES       9
#define HITBOX_COORDS       4  // x1, y1, x2, y2

// Tamanhos de sprites
#define SPRITE_SIZE         480
#define SHADOW_WIDTH        480
#define SHADOW_HEIGHT       128
#define MINI_SPRITE_SIZE    32
#define DISPLAY_SPRITE_SIZE 64
#define BIG_DISPLAY_SIZE    128

// ============================================================================
// CONFIGURAÇÕES DE ÁUDIO
// ============================================================================

#define DEFAULT_SOUND_VOLUME 255
#define DEFAULT_SFX_VOLUME   255
#define MAX_VOLUME          255
#define MIN_VOLUME          0

// ============================================================================
// CONFIGURAÇÕES DE ANIMAÇÃO
// ============================================================================

#define MAX_ANIM_FRAMES     30
#define MAX_INTRO_FRAMES    16
#define MAX_TRANS_FRAMES    30
#define MAX_FRAME_TIME_SLOTS 30

// Slots de entrada especial
#define MAX_SPECIAL_INPUTS  10
#define MAX_INPUT_SEQUENCE  17

// ============================================================================
// CONFIGURAÇÕES DE FÍSICA
// ============================================================================

#define GRAVITY_DEFAULT     0.5f
#define FRICTION_DEFAULT    0.1f

// ============================================================================
// CONFIGURAÇÕES DE GAMEPLAY
// ============================================================================

// Rounds
#define MIN_ROUNDS          1
#define MAX_ROUNDS          5
#define DEFAULT_ROUNDS      3

// Tempo
#define DEFAULT_ROUND_TIME  99
#define SECONDS_PER_MINUTE  60

// Dificuldade
#define MIN_DIFFICULTY      1
#define MAX_DIFFICULTY      5
#define DEFAULT_DIFFICULTY  3

// Hit pause
#define HIT_PAUSE_LIGHT     15
#define HIT_PAUSE_MEDIUM    30
#define HIT_PAUSE_HEAVY     45
#define HIT_PAUSE_KO        500

// Energia
#define MAX_ENERGY          100
#define MAX_SPECIAL         100

// ============================================================================
// CONFIGURAÇÕES DE FADE
// ============================================================================

#define FADE_MIN            0
#define FADE_MAX            255
#define FADE_SPEED_DEFAULT  10.0f

// ============================================================================
// ESTADOS DO JOGO
// ============================================================================

// Player states (exemplos)
#define STATE_IDLE          100
#define STATE_WALK_FORWARD  110
#define STATE_WALK_BACKWARD 120
#define STATE_CROUCH        130
#define STATE_JUMP          300
#define STATE_JUMP_FORWARD  310
#define STATE_JUMP_BACKWARD 320

// ============================================================================
// LIMITES DE STRING
// ============================================================================

#define MAX_NAME_LENGTH     50
#define MAX_PATH_LENGTH     99
#define MAX_VERSION_LENGTH  45
#define MAX_LANGUAGE_CODE   3

// ============================================================================
// VALORES PADRÃO DE CONFIGURAÇÃO
// ============================================================================

#define DEFAULT_LANGUAGE    "BR"
#define DEFAULT_WINDOW_RES_NUMBER 2

// Mapa (Arcade Mode)
#define DEFAULT_MAP_CENTER_X 320
#define DEFAULT_MAP_CENTER_Y 118
#define DEFAULT_MAX_STAGES   8

// ============================================================================
// CORES ESPECIAIS
// ============================================================================

#define COLOR_MAGENTA_R     255
#define COLOR_MAGENTA_G     0
#define COLOR_MAGENTA_B     255

#define COLOR_BLACK_R       0
#define COLOR_BLACK_G       0
#define COLOR_BLACK_B       0

// ============================================================================
// EDITOR
// ============================================================================

#define EDITOR_MODE_HITBOX  1
#define EDITOR_MODE_HURTBOX 2

#endif // HAMOOPI_CONSTANTS_H
