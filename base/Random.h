#ifndef RANDOM_H
#define RANDOM_H

#include "basefuction.h"
#include "ThreatsObject.h"
#include "enemy/bat.h"
#include "enemy/trap.h"
#include "enemy/rino.h"
#include "enemy/slime.h"
#include "enemy/trunk.h"
#include "enemy/skull_boss.h"
namespace Random
{
    std::vector<ThreatsObject*> MakeThreatslist(const int& Difficulty_, SDL_Renderer* screen);
    void ClearThreatsList(std::vector<ThreatsObject*>& threats_list);
    std::vector<ThreatsObject*> summonBoss(SDL_Renderer* screen);
    void RandomEnemy(std::vector<ThreatsObject*>& threats_list, SDL_Renderer* screen, const int& Dif, const int& x_pos_);
}
#endif