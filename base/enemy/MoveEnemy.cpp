#include "MoveEnemy.h"

void MoveEnemy::ImpMoveType(SDL_Renderer* screen)
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

void MoveEnemy::EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data)
{
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
    if(x1 >=0 && x2< MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y && on_ground_ == true)
    {
        if(x_val_ > 0)
        {
            if( isblock(map_data,y1,x2)//(map_data.tile[y1][x2] != BLANK_TILE && map_data.tile[y1][x2] != COIN) 
                || isblock(map_data,y2,x2)) //(map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2] != COIN) )
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                x_pos_ -= TILE_SIZE/10;                    
            }
            else if( isblock(map_data,y1-1,x2)//(map_data.tile[y1-1][x2] != BLANK_TILE) 
                || !isblock(map_data,y2+1,x2))//(map_data.tile[y2+1][x2] == BLANK_TILE) )
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
            else if( isblock(map_data,y1-1,x1)//(map_data.tile[y1-1][x1] != BLANK_TILE)
                || !isblock(map_data,y2+1,x1))//(map_data.tile[y2+1][x1] == BLANK_TILE) )
            {

                input_type_.left_ = 0;
                input_type_.right_ = 1;
            }
        }
    }
    x_val_ = 0;
}


void MoveEnemy::DoPlayer(Map& gmap)
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
            if(input_type_.left_ == 1 && input_type_.right_ == 0)
            {
                x_val_ -= threats_speed_;
            }
            else
            {
                x_val_ += threats_speed_;
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