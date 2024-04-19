#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <vector>
#include "basefuction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "LoadAnimation.h"

#define MAX_FALL_SPEED 10
#define GRAVITY_SPEED 0.8
#define PLAYER_SPEED 5
#define PLAYER_JUMP_VAL 15
#define PATROL_SENSOR_X 10
#define DASH_COOLDOWN  10
//#define PATROL_SENSOR_Y 64*3
#define FRAME_NUM 12

#define HEATHMAX 3

#define DASH_DISTANCE 250

const int gunstyle[] = {0,1,3,2};
class MainObject : public  BaseObject
{
public:
    MainObject();
    ~MainObject();
    enum GUN_STYLE
    {
        DEFAULT = 0,
        DOUBLE,
        WAVE,
        SHORTGUN,
    };
    enum STYLE
    {
        STYLE_1 = 1,
        STYLE_2 ,
        STYLE_3 , 
        STYLE_4 ,
    };
    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT  = 1,
        JUMP_RIGHT = 2,
        JUMP_LEFT  = 3,
        ATACK_LEFT = 4,
        ATACK_RIGHT = 5,
    };
    virtual bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events,SDL_Renderer* screen);
    void set_clips();
    void DoPlayer(Map& map_data,SDL_Renderer* screen, std::vector<LoadAnimation*>& p_dash);
    void CheckMap(Map& map_data);
    void SetMapXY(const int map_x,const int map_y)
    {
        //if(map_x - map_x_ > 90 || map_x - map_x_  < -90) return;
        map_x_ = map_x;
        map_y_ = map_y; 
        //map_x_ = map_x; 
    };
    void SetPosXY(const int pos_x,const int pos_y){x_pos_ = pos_x; y_pos_ = pos_y; };
    void set_y_val(const int pos_y){y_val_ = pos_y;}
    void SetStatus(const int& p_x,const int& p_y,const int& p_heath,const int& p_bullet,const int& p_money)
    {
        SetPosXY(p_x,p_y);
        set_heath(p_heath);
        set_bullet_size(p_bullet);
        set_money(p_money);
    }
    int get_x_pos() const {return x_pos_;}
    int get_y_pos() const {return y_pos_;}

    void CenterEntityOnMap(Map& map_data);

    void IncreaseBullet(const int& b_s_ = 1) {bullet_size_ += b_s_;}
    void IncreaseMoney(const int& money = 1){money_ += money;}
    void DecreaseMoney(const int& money = 1){money_ -= money;}
    void IncreaseHeath(const int& heath = 1){heath_ += heath;}
    void DecreaseHeath(const int& heath = 1){heath_ -= heath;}

    void set_money(const int& money)  {money_ = money;}
    void set_heath(const int& heath)  {heath_ = heath;}
    void set_bullet_size(const int& bullet_size) {bullet_size_ = bullet_size;}
    
    int get_money() const {return money_;}
    int get_heath() const {return heath_;}
    int get_bullet_size() const {return bullet_size_;}

    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list = bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list;}
    void HandelBullet(SDL_Renderer* des);
    void RemoveBullet(const int& idx);

    SDL_Rect GetRealRect() const;
    void respawn();
    void reset();
    void PlayerStatus();

    void IncreaseKill() {kill_++;}
    int get_kill() const {return kill_;}
    
    void set_path(const std::string& left = "",
                const std::string& right = "",
                const std::string& jump_left = "",
                const std::string& jump_right = "",
                const std::string& atack_left = "",
                const std::string& atack_right = "")
    {
        path_img[WALK_LEFT] = left;
        path_img[WALK_RIGHT] = right;
        path_img[JUMP_LEFT] = jump_left;
        path_img[JUMP_RIGHT] = jump_right; 
        path_img[ATACK_LEFT] = atack_left;
        path_img[ATACK_RIGHT] = atack_right;
    }
    int get_gun_type() const {return gun_type_;}
    int get_style() const {return style_;}

    static void set_sound(Mix_Chunk* sound_bullet,Mix_Chunk* sound_jump,Mix_Chunk* sound_pickup);
private:
    int LV_;
    int money_; 

    std::vector<BulletObject*> p_bullet_list;
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[FRAME_NUM];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground;

    int dash_dir_;
    bool isdash_;
    int map_x_;
    int map_y_;
    int comeback_time_;
    bool load_bullet_;
    int bullet_size_;
    int heath_;
    int dash_cooldown_;
    std::string path_img[6];
    int kill_;
    int double_jump_;
    int gun_type_;
    int dash_distance_;
    int style_;
    bool q_;
	bool e_; 

    float player_speed_;
    float player_jump_speed_;

    int p_;

    static Mix_Chunk* sound_bullet_;
    static Mix_Chunk* sound_jump_;
    static Mix_Chunk* sound_pickup_;
};
#endif