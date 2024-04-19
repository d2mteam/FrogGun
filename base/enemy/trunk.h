#ifndef TRUNK_H
#define TRUNK_H
#include "../ThreatsObject.h"
#include "../BaseObject.h"
#include "MoveEnemy.h"
class trunk : public MoveEnemy
{
public:
    trunk() {;}
    ~trunk() {;}
    void ImpMoveType(SDL_Renderer* screen) override;
    void EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data) override;
    void DoPlayer(Map& gmap) override;
    void InitBullet(SDL_Renderer* screen) override;
};
#endif