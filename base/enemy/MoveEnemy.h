#ifndef MOVE_ENEMY_H
#define MOVE_ENEMY_H
#include "../ThreatsObject.h"
#include "../BaseObject.h"
class MoveEnemy : public ThreatsObject
{
public:
    MoveEnemy() {;}
    ~MoveEnemy() {;}
    virtual void  ImpMoveType(SDL_Renderer* screen) override;
    virtual void EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data) override;
    virtual void DoPlayer(Map& gmap) override;
};
#endif