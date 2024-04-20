#include "skull_boss.h"
void skull::ImpMoveType(SDL_Renderer* screen)
{
    if(input_type_.left_ == 1 && input_type_.right_ == 0)
    {
        LoadImg("image//enemy_image//skull_boss_left.png",screen);
    }
    if(input_type_.left_ == 0 && input_type_.right_ == 1)
    {
        LoadImg("image//enemy_image//skull_boss.png",screen);
    }    
}
void skull::EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data)
{
    p_rect.x += map_x_;
    p_rect.y += map_y_;
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
    InitBullet(screen);
    MakeBullet(screen,SCREEN_WIDTH,SCREEN_HEIGHT);      
}
void skull::InitBullet(SDL_Renderer* screen)
{
    frame_bullet_ --;
    if(frame_bullet_ <= 0)
    {
        frame_bullet_ = 10;
        //phase 1
        if(hp_ >= 75)
        {
            int tp = 4;
            for(int i = 0; i < tp; i++)
            {
                BulletObject* p_bullet = new BulletObject();
                p_bullet->SetMapXY(map_x_,map_y_);
                p_bullet->SetPosXY(x_pos_ + width_frame_/2,y_pos_ + height_frame_/2);
                p_bullet->set_is_move(true);
                p_bullet->LoadImg("image//enemy_image//enemy_bullet.png",screen);
                p_bullet->set_bullet_distance(500);
                p_bullet->set_x_val(40);
                p_bullet->set_y_val(5*(i-(tp-1)/2));
                p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                bullet_list_.push_back(p_bullet);
            }
            for(int i = 0; i < tp; i++)
            {
                BulletObject* p_bullet = new BulletObject();
                p_bullet->SetMapXY(map_x_,map_y_);
                p_bullet->SetPosXY(x_pos_ + width_frame_/2,y_pos_ + height_frame_/2);
                p_bullet->set_is_move(true);
                p_bullet->LoadImg("image//enemy_image//enemy_bullet.png",screen);
                p_bullet->set_bullet_distance(500);
                p_bullet->set_x_val(40);
                p_bullet->set_y_val(5*(i-(tp-1)/2));
                p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                bullet_list_.push_back(p_bullet);
            }
        }
        //phase 2
        else
        {
            int tp = 4 + (75 - hp_)/5;
            for(int i = 0; i < tp; i++)
            {
                BulletObject* p_bullet = new BulletObject();
                p_bullet->SetMapXY(map_x_,map_y_);
                p_bullet->SetPosXY(x_pos_ + width_frame_/2,y_pos_ + height_frame_/2);
                p_bullet->set_is_move(true);
                p_bullet->LoadImg("image//enemy_image//enemy_bullet_2.png",screen);
                p_bullet->set_bullet_distance(500);
                p_bullet->set_x_val(40);
                p_bullet->set_y_val(5*(i-(tp-1)/2));
                p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                bullet_list_.push_back(p_bullet);
            }
            for(int i = 0; i < tp; i++)
            {
                BulletObject* p_bullet = new BulletObject();
                p_bullet->SetMapXY(map_x_,map_y_);
                p_bullet->SetPosXY(x_pos_ + width_frame_/2,y_pos_ + height_frame_/2);
                p_bullet->set_is_move(true);
                p_bullet->LoadImg("image//enemy_image//enemy_bullet_2.png",screen);
                p_bullet->set_bullet_distance(500);
                p_bullet->set_x_val(40);
                p_bullet->set_y_val(5*(i-(tp-1)/2));
                p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                bullet_list_.push_back(p_bullet);
            }
        }
    }    
}