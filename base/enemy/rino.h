#ifndef RINO_H
#define RINO_H
#include "../ThreatsObject.h"
#include "../BaseObject.h"
#include "MoveEnemy.h"
class rino : public MoveEnemy
{
public:
    rino(){;}
    ~rino(){;}
    void  ImpMoveType(SDL_Renderer* screen) override;
    void EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data) override;
    void DoPlayer(Map& gmap) override;
};
#endif