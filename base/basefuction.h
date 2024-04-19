#ifndef BASE_FUCTION_H
#define BASE_FUCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <cmath>
#include <functional>
#include <cstdlib>
#include <ctime>


//#include "TextObject.h"

//#include "ThreatsObject.h"


const int FRAME_PER_SECOND = 30;
const int SCREEN_WIDTH = 1280; //1280
const int SCREEN_HEIGHT = 640; //640
const int SCREEN_MENU_WIDTH = 1280; //1280
const int SCREEN_MENU_HEIGHT = 640; //640
const int SCREEN_BPP = 32;
const int COLOR_KEY_R=167;
const int COLOR_KEY_G=175;
const int COLOR_KEY_B=180;
const int RENDER_DRAW_COLOR=0xff;

static  SDL_Window* g_window = NULL;
static  SDL_Window* g_menu_window = NULL;
static  SDL_Renderer* g_screen = NULL;
static  SDL_Renderer* g_menu_r_screen = NULL;
static  SDL_Event g_event;

static  Mix_Chunk* g_sound_bullet = NULL;
static  Mix_Chunk* g_sound_explosion = NULL;
static  Mix_Chunk* g_sound_jump = NULL;
static  Mix_Chunk* g_sound_pickup = NULL;
static  Mix_Music* g_gameMusic[9];
static  Mix_Music* g_MenuMusic = NULL;

const std::string music[9] = 
{"AndTheJourneyBegins.wav"
,"DecisiveBattle.wav"
,"ExploringTheUnknown.wav"
,"Minigame.wav"
,"MysteriousDungeon.wav"
,"Preparefo Battle!.wav"
,"Takesomerestandeatsomefood!.wav"
,"TheFinalofTheFantasy.wav"
,"TheIcyCave.wav"}; 
//Map
#define TILE_SIZE 64
#define MAP_MAX_X 400
#define MAP_MAX_Y 10
//Tile
#define BLANK_TILE 0
#define COIN 4
#define HEATH 6
#define BULLET 5
#define SAND 10
struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAP_MAX_Y][MAP_MAX_X]; 
//  char* file_name_;
};

struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int dash_;
};

enum Difficulty
{
   
    Easy = 0,
    Medium ,
    Hard ,
    Very_Hard,
};

enum CHOOSE
{

    START = 0,
    EXIT,
    CONTINUE,
    NEXT_LV,
};

enum STYLE
{
    STYLE_1 = 1,
    STYLE_2 ,
    STYLE_3 , 
    STYLE_4 ,
};

 enum GUN_STYLE
{
    DEFAULT = 0,
    DOUBLE,
    WAVE,
    SHORTGUN,
};
namespace SDLbasefuction
{
    
    bool CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2);
    bool LoadSaveFile(int& px_pos,int& py_pos,int& p_heath,int& p_bullet,int& p_money,int& time_,int& Dif_,int& Map_LV);
    bool SaveGame(const int& px_pos,const int& py_pos,
                const int& p_heath,const int& p_bullet,
                const int& p_money,const int& time_ = 0,
                const int& Dif_ = 0,const int& Map_LV = 1);
    bool CheckMousePos(const int& x,const int& y,const SDL_Rect& Obj_);
    bool PauseMenu(SDL_Renderer* screen);
    bool GameOverMenu(SDL_Renderer* screen,const int& high_score = 0);
    int MainMenu(SDL_Renderer* screen,int& Dif_,bool& game_quit,bool& is_quit,int &NG_,Mix_Music* MenuMusic);
    int Random(int begin,int end);
    void PlayerStatus(const int& money, const int& bullet, 
                    const int& heath, const int& kill, int& time,
                    TTF_Font* font_time,SDL_Renderer* screen,
                    const int& gun_type,const int& style);
    int CheckWin(const int& x_pos,const int& y_pos,SDL_Renderer* screen,int& Map_LV,const int& high_score);
};
#endif

