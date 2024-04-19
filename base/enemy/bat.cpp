#include "bat.h"

void bat::ImpMoveType(SDL_Renderer* screen)
{
    if(input_type_.left_ == 1 && input_type_.right_ == 0)
    {
        LoadImg("image//enemy_image//bat_left.png",screen);
    }
    if(input_type_.left_ == 0 && input_type_.right_ == 1)
    {
        LoadImg("image//enemy_image//bat_right.png",screen);
    }
}

void bat::EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data)
{
    p_rect.x += map_x_;
    p_rect.y += map_y_;
    SDL_Rect threat_sensor_rect = frame_clip_[0];
    threat_sensor_rect.x = x_pos_ - 200;
    threat_sensor_rect.y = y_pos_ - 200;
    threat_sensor_rect.w = 400;
    threat_sensor_rect.h = 400;
    if(SDLbasefuction::CheckCollision(p_rect,threat_sensor_rect) == true)
    {
        animation_left_ = x_pos_ - (animation_right_ - animation_left_)/2;
        animation_right_ = x_pos_ + (animation_right_ - animation_left_)/2;
        threats_status_ = CHASE;
    }
    else
    {
        threats_status_ = PATROL;
    }
    switch (threats_status_)
    {
        case PATROL:
            if(x_pos_ + width_frame_ > animation_right_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
            }
            if(x_pos_ < animation_left_)
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
            }
            input_type_.down_ = 0;
            input_type_.jump_ = 0;
            break;
        case CHASE:
            if(x_pos_ > p_rect.x + p_rect.w)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
            }
            if(x_pos_ + height_frame_< p_rect.x)
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;

            }
            if(y_pos_ > p_rect.y + p_rect.h)
            {
                input_type_.down_ = 0;
                input_type_.jump_ = 1;
            }
            if(y_pos_ + height_frame_ < p_rect.y)
            {
                input_type_.down_ = 1;
                input_type_.jump_ = 0;
            }
            break;
        default:
            break;
    }

    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    x_val_ = threats_speed_ * (input_type_.right_ - input_type_.left_);
    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_+ width_frame_ -1)/TILE_SIZE;
    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min -1)/TILE_SIZE;
    if(x1 >=0 && x2< MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y  && threats_status_ != CHASE)
    {
        if(x_val_ > 0)
        {
            if( isblock(map_data,y1,x2)//(map_data.tile[y1][x2] != BLANK_TILE && map_data.tile[y1][x2] != COIN) 
                || isblock(map_data,y2,x2)) //(map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2] != COIN) )
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;                 
            }
        }
        else if(x_val_ < 0)
        {
            if( isblock(map_data,y1,x1)//(map_data.tile[y1][x1] != BLANK_TILE && map_data.tile[y1][x1] != COIN)
                || isblock(map_data,y2,x1))//(map_data.tile[y2][x1] != BLANK_TILE && map_data.tile[y2][x1] != COIN) )
            {
                input_type_.left_ = 0;
                input_type_.right_ = 1;
            }
        }
    }
    x_val_ = 0;
  
    if(threats_status_ == CHASE)    InitBullet(screen);
    MakeBullet(screen,SCREEN_WIDTH,SCREEN_HEIGHT);  
}

void bat::InitBullet(SDL_Renderer* screen)
{
    frame_bullet_ --;
    if(frame_bullet_ <= 0)
    {
        frame_bullet_ = 40;
        BulletObject* p_bullet = new BulletObject();
        p_bullet->SetMapXY(map_x_,map_y_);
        p_bullet->SetPosXY(x_pos_ - 20*(input_type_.left_ == 1 ? -1 : 1 ) + width_frame_ * (input_type_.right_ == 1),y_pos_ + height_frame_* 0.3);
        p_bullet->set_is_move(true);
        p_bullet->LoadImg("image//enemy_image//enemy_bullet.png",screen);
        p_bullet->set_bullet_dir((input_type_.left_ == 1 ? BulletObject::DIR_LEFT : BulletObject::DIR_RIGHT ));
        p_bullet->set_x_val(30);
        bullet_list_.push_back(p_bullet);
    }
}

void bat::DoPlayer(Map& gmap)
{ 
    if(comeback_time_ == 0)
    {
        x_val_ = 0;
        y_val_ = 0;
        if(input_type_.left_ == 1)
        {
            x_val_ -= threats_speed_;
        }
        else if(input_type_.right_ == 1)
        {
            x_val_ += threats_speed_;
        }
        if(input_type_.down_ == 1)
        {
            y_val_ += 10; 
        }
        else if(input_type_.jump_ == 1)
        {
            y_val_ -= 10; 
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