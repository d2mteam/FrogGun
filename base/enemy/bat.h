#ifndef BAT_H
#define BAT_H
#include "../ThreatsObject.h"
#include "../BaseObject.h"

class bat : public ThreatsObject
{
public:
    bat() {;}
    ~bat() {;}
    virtual void ImpMoveType(SDL_Renderer* screen) override;
    virtual void EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data) override;
    virtual void InitBullet(SDL_Renderer* screen) override;
    virtual void DoPlayer(Map& gmap) override;
};
#endif