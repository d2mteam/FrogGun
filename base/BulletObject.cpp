#include "BulletObject.h"
Map BulletObject::gamemap_;
BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    distance_ = 0;

    x_pos_ = 0;
    y_pos_ = 0;
    map_x_ = 0;
    map_y_ = 0;
    style_ = 0;
    bullet_distance_ = BULLET_DISTANCE_DEFAULT;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandelMove()
{
    int x1 = x_pos_/TILE_SIZE;
    int y1 = y_pos_/TILE_SIZE;
    if(gamemap_.tile[y1][x1] != BLANK_TILE && gamemap_.tile[y1][x1] != COIN && gamemap_.tile[y1][x1] != BULLET && gamemap_.tile[y1][x1] != HEATH)
    {
            is_move_ = false;
            distance_ = 0;
    }
    if(is_move_ == true)
    {     
        x_pos_ += x_val_ * (bullet_dir_ == DIR_LEFT ? -1 : 1);
        y_pos_ += y_val_;
        distance_ += x_val_; 
        x_val_ -= 4 * (x_val_ > 10 && style_ != WAVE);
        distance_ += abs(y_val_);
        if(distance_ > bullet_distance_)
        {
            is_move_ = false;
            distance_ = 0;
        }
    }
    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;
}

void BulletObject::set_map(const Map& gamemap)
{
   gamemap_ = gamemap;
}