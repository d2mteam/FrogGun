#include "trunk.h"

void trunk::ImpMoveType(SDL_Renderer* screen)
{
    if(!bullet_list_.empty())
    {
        if(input_type_.left_ == 1 && input_type_.right_ == 0)
        {
            LoadImg(path_img[ATACK_LEFT],screen);
        }
        if(input_type_.left_ == 0 && input_type_.right_ == 1)
        {
            LoadImg(path_img[ATACK_RIGHT],screen);
        }
    }
    else
    {
        if(input_type_.left_ == 1 && input_type_.right_ == 0)
        {
            LoadImg(path_img[LEFT],screen);
        }
        if(input_type_.left_ == 0 && input_type_.right_ == 1)
        {
            LoadImg(path_img[RIGHT],screen);
        }
    }
}

void trunk::EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data)
{
    w_sensor_ = 640;
    h_sensor_ = 300; 
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
    if(threats_status_ == CHASE)    InitBullet(screen);
    MakeBullet(screen,SCREEN_WIDTH,SCREEN_HEIGHT);  
}

void trunk::InitBullet(SDL_Renderer* screen)
{
    frame_bullet_ --;
    if(frame_bullet_ <= 0)
    {
        frame_bullet_ = 30;
        for(int i = 0; i < 4; i++)
        {
            BulletObject* p_bullet = new BulletObject();
            p_bullet->set_bullet_dir((input_type_.left_ == 1 ? 
                                        BulletObject::DIR_LEFT : BulletObject::DIR_RIGHT));
            if(input_type_.left_ == 1)    
                p_bullet->LoadImg("image//enemy_image//trunk//trunk_bullet_left.png",screen);
            else   
                p_bullet->LoadImg("image//enemy_image//trunk//trunk_bullet_right.png",screen);
            p_bullet->SetMapXY(map_x_,map_y_);
            p_bullet->SetPosXY(x_pos_ - 20 *((input_type_.left_ == 1) ? 1 : -1),y_pos_ + height_frame_ * 0.3);
            p_bullet->set_x_val(30);
            p_bullet->set_y_val(3 * (i- 1.5));
            p_bullet->set_is_move(true);
            bullet_list_.push_back(p_bullet);
        }
    }
}


void trunk::DoPlayer(Map& gmap)
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
                x_val_ -= threats_speed_ * (threats_status_ == CHASE ? 0.2 : 1);
            }
            if(input_type_.right_ == 1)
            {
                x_val_ += threats_speed_ * (threats_status_ == CHASE ? 0.2 : 1);
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