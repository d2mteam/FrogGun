#include "ThreatsObject.h"
Mix_Chunk* ThreatsObject::sound_bullet_ = NULL;
Mix_Chunk* ThreatsObject::sound_jump_ = NULL;

ThreatsObject::ThreatsObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    comeback_time_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    on_ground_ = false;
    frame_ = 0;
    animation_left_ = 0;
    animation_right_ = 0;
    input_type_.left_ = 1;
    input_type_.right_ = 0;
    input_type_.down_ = 0;
    input_type_.jump_ = 0;
    type_move_ = STATIC_MOVE_THREAT;
    frame_bullet_ = 0;
    hp_ = HP;
    enemy_frame_num_ = ENEMY_FRAME_NUM;
    threats_gravity_speed_ = THREATS_GRAVITY_SPEED;
    threats_max_fall_speed_ = THREATS_MAX_FALL_SPEED;
    threats_speed_ = THREATS_SPEED;
    threats_status_ = PATROL;
    timewait_ = TimeWait;
    w_sensor_ = W_SENSOR_;
    h_sensor_ = H_SENSOR_;
    w_atack_ = W_ATACK_;
    h_atack_ = H_ATACK_;
    threats_level_ = 1;
    path_img[LEFT] = "";
    path_img[RIGHT] = "";
    path_img[ATACK_LEFT] = "";
    path_img[ATACK_RIGHT] = "";
    is_fire_ = true;
}

ThreatsObject::~ThreatsObject()
{
    for (auto bullet : bullet_list_) {
        delete bullet;
    }
    bullet_list_.clear();
}

bool ThreatsObject::isblock(const Map& map_data,const int& y,const int& x) const
{
    int v = map_data.tile[y][x];
    return !(v == BLANK_TILE || v == COIN || v == BULLET || v == HEATH);     
}

void ThreatsObject::SetThreatType(const int& e_f_n_, const float& t_g_s_, const int& t_m_f_s_,const int& t_s_,const int& i_f_)
{
    enemy_frame_num_ = e_f_n_;
    threats_gravity_speed_ = t_g_s_;
    threats_max_fall_speed_ = t_m_f_s_;
    threats_speed_ = t_s_;
    is_fire_ = i_f_;       
}

bool ThreatsObject::LoadImg(std::string path,SDL_Renderer* screen)
{

    bool ret = BaseObject::LoadImg(path,screen);
    if(ret == true)
    {
        width_frame_ = rect_.w/enemy_frame_num_;
        height_frame_ = rect_.h;
    }
    return ret;
}

void ThreatsObject::set_clips() //frame
{
    if(width_frame_ > 0 && height_frame_ > 0) 
    {
        for(int i = 0; i < enemy_frame_num_; i++)
            {
                frame_clip_[i].x = i*width_frame_;
                frame_clip_[i].y = 0;
                frame_clip_[i].w = width_frame_;
                frame_clip_[i].h = height_frame_;
            }
    }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if(comeback_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if(frame_ >= enemy_frame_num_)
        {
            frame_ = 0;
        }
        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect RenderQuard = {rect_.x,rect_.y,width_frame_,height_frame_};
        if(ThreatsOnScreen() == true ) SDL_RenderCopy(des, p_object_, currentClip, &RenderQuard);
    }
}

bool ThreatsObject::ThreatsOnScreen() const
{
    int x_left = -width_frame_;
    int x_right = SCREEN_WIDTH + width_frame_ ;
    int y_down = SCREEN_HEIGHT + height_frame_ ;
    int y_up = -height_frame_;
    return ((x_left < rect_.x) && (rect_.x < x_right) && (y_up < rect_.y) && (rect_.y < y_down));  
}

bool ThreatsObject::isThreatsActive()
{
    int x_left = -width_frame_ - SCREEN_WIDTH/2;
    int x_right = SCREEN_WIDTH* 3/2  + width_frame_ ;
    int y_down = SCREEN_HEIGHT + height_frame_ ;
    int y_up = -height_frame_;
    int x_p_ = x_pos_ - map_x_;
    int y_p_ = y_pos_ - map_y_;
    return ((x_left < x_p_) && (x_p_ < x_right) && (y_up < y_p_) && (y_p_ < y_down));  
}
void ThreatsObject::DoPlayer(Map& gmap) //move enemy
{
    if(comeback_time_ == 0)
    {
//Gravity
        y_val_ += threats_gravity_speed_;
        x_val_ = 0;
        if(y_val_ > threats_max_fall_speed_)
        {
            y_val_ = threats_max_fall_speed_;
        }
//type enemy
        if(type_move_ == MOVE_IN_SPACE_THREAT || type_move_ == MOVE_TRAP)
        {
            if(on_ground_ == true)
            {
                if(input_type_.left_ == 1)
                {
                    x_val_ -= threats_speed_;
                }
                if(input_type_.right_ == 1)
                {
                    x_val_ += threats_speed_;
                }
            }
        }
        if(type_move_ == FLY_ENEMY)
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
            if(input_type_.jump_ == 1)
            {
                y_val_ -= 10; 
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

void ThreatsObject::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;
    //Check hoz


    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_+ width_frame_ * 0.8 - 1)/TILE_SIZE;
    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;


    if(x1 >=0 && x2< MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y)
    {
        if(x_val_ > 0)
        {      if( isblock(map_data,y1,x2) //(map_data.tile[y1][x2] != BLANK_TILE && map_data.tile[y1][x2] != COIN) 
             ||  isblock(map_data,y2,x2)) //map_data.tile[y2][x2] != BLANK_TILE && map_data.tile[y2][x2] != COIN) )
            {
                x_pos_ = x2*TILE_SIZE;
                x_pos_ -= width_frame_ + 1 ;
                x_val_ = 0;
            }
        }
        else if(x_val_ < 0)
        {
            if( isblock(map_data,y1,x1)//(map_data.tile[y1][x1] != BLANK_TILE && map_data.tile[y1][x1] != COIN)
             || isblock(map_data,y2,x1))//(map_data.tile[y2][x1] != BLANK_TILE && map_data.tile[y2][x1] != COIN) ) 
            {
                x_pos_ = (x1+1)*TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    //Check ver

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_ + width_min* 0.1 )/TILE_SIZE;
    x2 = (x_pos_ + width_min - width_frame_*0.1)/TILE_SIZE;
    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_  - 1)/TILE_SIZE;

    if(x1 >=0 && x2 < MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y)
    {
        if(y_val_ > 0)
        {
            if( isblock(map_data,y2,x1)//(map_data.tile[y2][x1] != BLANK_TILE &&  map_data.tile[y2][x1] != COIN)
             || isblock(map_data,y2,x2) )//(map_data.tile[y2][x2] != BLANK_TILE &&  map_data.tile[y2][x2] != COIN ) )
            {
                y_pos_ = y2*TILE_SIZE;   
                y_pos_ -= height_frame_;
                y_val_ = 0;
                on_ground_ = true;

            }
        }
        else if(y_val_ < 0)
        {
            if( isblock(map_data,y1,x1)//(map_data.tile[y1][x1] != BLANK_TILE && map_data.tile[y1][x1] != COIN)
             || isblock(map_data,y1,x2)) //(map_data.tile[y1][x2] != BLANK_TILE && map_data.tile[y1][x2] != COIN) )
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        } 
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;
    
    // goc trai goc phai
    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ -1;
    }
    if(y_pos_ < 0)
    {
        y_pos_ = 0;
		y_val_ = threats_gravity_speed_; 
    }
    if(y_pos_ >= map_data.max_y_){
        comeback_time_ = 60;
    }
}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move_ == FLY_ENEMY || type_move_ == FLY_ENEMY_SMART)
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
    if(type_move_ == MOVE_IN_SPACE_THREAT)
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
    else
    {
        
    }
}

void ThreatsObject::InitBullet(SDL_Renderer* screen)
{
    
}
void ThreatsObject::MakeBullet(SDL_Renderer* screen,const int& x_limit,const int& y_limit)
{
    for(int i = 0; i < bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        if(p_bullet != NULL)
        {

            if(p_bullet->get_is_move() == true)
            {
                p_bullet->SetMapXY(map_x_,map_y_);
                p_bullet->HandelMove();
                p_bullet->Render(screen);
            }
            else
            {
                RemoveBullet(i);
                set_frame_bullet();
            }
        }
    }
}



SDL_Rect ThreatsObject::GetRealRect() const
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.h = height_frame_;
    rect.w = width_frame_;
    return rect;
}

void ThreatsObject::RemoveBullet(const int& idx)
{
    int size = bullet_list_.size();
    if( size > 0 && idx < size)
    {
        BulletObject* p_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin() + idx);
        if(p_bullet != NULL)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void ThreatsObject::EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data)
{
	if(type_move_ > MIMIC) return;
    if(type_move_ != FLY_ENEMY)
    {    
        p_rect.x += map_x_;
        p_rect.y += map_y_;
        SDL_Rect threat_sensor_rect = frame_clip_[0];
        threat_sensor_rect.x = x_pos_ + width_frame_/2 - w_sensor_/2;
        threat_sensor_rect.y = y_pos_ + height_frame_/2 - h_sensor_/2;
        threat_sensor_rect.w = w_sensor_;
        threat_sensor_rect.h = h_sensor_;
        if(SDLbasefuction::CheckCollision(p_rect,threat_sensor_rect) == true && type_move_ != MOVE_TRAP)
        {
            threats_status_ = CHASE;
            threat_sensor_rect.x = x_pos_ + width_frame_/2 - w_atack_/2;
            threat_sensor_rect.y = y_pos_ + height_frame_/2 - h_atack_/2;
            threat_sensor_rect.w = w_atack_;
            threat_sensor_rect.h = h_atack_;
            if(SDLbasefuction::CheckCollision(p_rect,threat_sensor_rect) == true && 0) 
            {
                threats_status_ = ATACK;
            }
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
            case ATACK:
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
        if(x1 >=0 && x2< MAP_MAX_X && y1 >= 0 && y2 < MAP_MAX_Y && on_ground_ == true && threats_status_ != CHASE)
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
    if(type_move_ == FLY_ENEMY)
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
    }
    if(type_move_ == FLY_ENEMY_SMART)
    {
        p_rect.x += map_x_;
        p_rect.y += map_y_;
        SDL_Rect e_rect = frame_clip_[0];
        e_rect.x = x_pos_;
        e_rect.y = y_pos_;
        
    }
    frame_bullet_ -= (frame_bullet_ > 0);
    if(bullet_list_.size() == 0 && frame_bullet_ <= 0 && is_fire_ == true) //reload
    {
        InitBullet(screen);
        frame_bullet_ = timewait_;
    }
    MakeBullet(screen,SCREEN_WIDTH,SCREEN_HEIGHT);   
}


void ThreatsObject::set_sound(Mix_Chunk* sound_bullet,Mix_Chunk* sound_jump)
{
	sound_bullet_ = sound_bullet;
	sound_jump_ = sound_jump;
}