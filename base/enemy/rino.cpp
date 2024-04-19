#include "rino.h"

void rino::ImpMoveType(SDL_Renderer* screen)
{
    if(input_type_.left_ == 1 && input_type_.right_ == 0)
    {
        LoadImg("image//enemy_image//rino_left.png",screen);
    }
    if(input_type_.left_ == 0 && input_type_.right_ == 1)
    {
        LoadImg("image//enemy_image//rino_right.png",screen);
    }
}

void rino::EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data)
{
    p_rect.x += map_x_;
    p_rect.y += map_y_;
    SDL_Rect threat_sensor_rect = frame_clip_[0];
    threat_sensor_rect.x = x_pos_ + width_frame_/2 - w_sensor_/2;
    threat_sensor_rect.y = y_pos_ + height_frame_/2 - h_sensor_/2;
    threat_sensor_rect.w = w_sensor_;
    threat_sensor_rect.h = h_sensor_;
    if(SDLbasefuction::CheckCollision(p_rect,threat_sensor_rect) == true)
    {
        threats_status_ = CHASE;
    }
    else
    {
        threats_status_ = PATROL;
    }
    switch (threats_status_)
    {
        case PATROL:
            break;
        case CHASE:
            if(x_pos_ > p_rect.x + p_rect.w)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
            }
            if(x_pos_ + width_frame_< p_rect.x )
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
            }
            break;
        default:
            break;
    }
    if(threats_status_ != CHASE)    MoveEnemy::EnemyStatus(p_rect,screen,map_data);
}


void rino::DoPlayer(Map& gmap)
{
    if(comeback_time_ == 0)
    {
        y_val_ += threats_gravity_speed_;
        x_val_ = 0;
        if(y_val_ > threats_max_fall_speed_)
        {
            y_val_ = threats_max_fall_speed_;
        }
        if(on_ground_ == true)
        {
            if(input_type_.left_ == 1)
            {
                x_val_ -= threats_speed_ * (threats_status_ == CHASE ? 2 : 1);
            }
            if(input_type_.right_ == 1)
            {
                x_val_ += threats_speed_ * (threats_status_ == CHASE ? 2 : 1);
            }
        }
        CheckToMap(gmap);
    }
    else if(comeback_time_ > 0)
    {
        comeback_time_ --;
        on_ground_ == false;
        if(comeback_time_ == 0)
        {
            x_val_ = 0;
            y_val_ = 0;
            if(x_pos_ > 256){
                x_pos_ -= 256;
                animation_left_ -= 256;
                animation_right_ -= 256;
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            comeback_time_ = 0;
        }
    }  
}