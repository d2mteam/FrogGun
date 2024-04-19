#ifndef SKULL_BOSS_H
#define SKULL_BOSS_H
#include "../ThreatsObject.h"
#include "../BaseObject.h"
#include "bat.h"
#define HP_MAX 50
class skull : public bat
{
public:
    skull() {;}
    ~skull() {;}
    void ImpMoveType(SDL_Renderer* screen) override;
    void EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data) override;
    void InitBullet(SDL_Renderer* screen) override;
};
#endif