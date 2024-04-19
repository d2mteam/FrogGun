#ifndef THREATS_OBJECT_H
#define THREATS_OBJECT_H

#include "basefuction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#define ENEMY_FRAME_NUM 8
#define THREATS_GRAVITY_SPEED 0.8
#define THREATS_MAX_FALL_SPEED 8
#define THREATS_SPEED 4
#define W_SENSOR_ 400
#define H_SENSOR_ 400
#define W_ATACK_ 50
#define H_ATACK_ 50
#define TimeWait 30
#define HP 1
class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();
    enum ThreatsTypeMove
    {
        STACTIC,
        STATIC_MOVE_THREAT = 1122,
        MOVE,
        MOVE_IN_SPACE_THREAT,

        FLY,
        FLY_ENEMY,
        FLY_ENEMY_SMART,
        
        TRAP,
        FALL_TRAP,
        MOVE_TRAP,
        MIMIC,  
        MIMIC_COIN,
        MIMIC_HEATH,
        MIMIC_BULLET,
    
        NOT_ENEMY,
        ITEM_COIN,
        ITEM_HEATH,
        ITEM_BULLET,

        RAMDOM_TRAP,
    };
    enum Status
    {
        IDLE  = 199,
        PATROL,
        CHASE,
        ATACK,
        STUN,
        DEAD,
    };
    enum PATH
    {
        LEFT = 0,
        RIGHT,
        ATACK_LEFT,
        ATACK_RIGHT,
    };
      
    void set_x_val(const float& xVal){x_val_ = xVal;}
    void set_y_val(const float& yVal){y_val_ = yVal;}
    void set_x_pos(const float& xPos){x_pos_ = xPos;}
    void set_y_pos(const float& yPos){y_pos_ = yPos;}

    float get_x_val() const {return x_val_;}
    float get_y_val() const {return y_val_;}
    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    void SetMapXY(const int& mp_x,const int& mp_y){map_x_ = mp_x,map_y_ = mp_y;}

    void CheckToMap(Map& map_data);
    
    void set_clips();

    bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    void set_type_move(const int& typemove ){type_move_ = typemove;}
    void SetAnimationPos(const int& pos_left,const int& pos_right){animation_left_ = pos_left,animation_right_ = pos_right;}
    
   // void set_input_left(const int& ileft){input_type_.left_ = ileft;}

    std::vector<BulletObject*> get_bullet_list()  const  {return bullet_list_;}
    
    void MakeBullet(SDL_Renderer* screen,const int& x_limit,const int& y_limit);
    void RemoveBullet(const int& idx);

    SDL_Rect GetRealRect() const;
    bool ThreatsOnScreen() const;

    bool get_frame_bullet() {frame_bullet_--; return frame_bullet_ == 0;}

    void SetThreatType( const int& e_f_n_ = ENEMY_FRAME_NUM, 
                        const float& t_g_s_ = THREATS_GRAVITY_SPEED, 
                        const int& t_m_f_s_ = THREATS_MAX_FALL_SPEED,
                        const int& t_s_ = THREATS_SPEED,const int& i_f_ = true);
    void set_frame_bullet(const int& f_b_ = 20)  {frame_bullet_ = f_b_;}
    
    void set_HP(const int& hp  = 1){hp_ = hp;}
    int get_HP() const {return hp_;}
    void decreaseHP(const int& hp = 1){ hp_ -= hp;}
    bool isThreatsActive();
    int EnemyID() const {return type_move_;}
    void setLV(const int& lv){threats_level_ = lv;}
    int getLV() const {return threats_level_;}
    bool onground() const {return on_ground_;}
    void set_path(const std::string& left = "",
                const std::string right = "",
                const std::string& atack_left = "",
                const std::string& atack_right = "")
    {
        path_img[LEFT] = left;
        path_img[RIGHT] = right;
        path_img[ATACK_LEFT] = atack_left;
        path_img[ATACK_RIGHT] = atack_right;
    }
    bool isblock(const Map& map_data,const int& y,const int& x) const;
    int get_type_move() const {return type_move_;}

    virtual void ImpMoveType(SDL_Renderer* screen);
    virtual void EnemyStatus(SDL_Rect p_rect, SDL_Renderer* screen,const Map& map_data);
    virtual void InitBullet(SDL_Renderer* screen);
    virtual void DoPlayer(Map& gmap);


    static void set_sound(Mix_Chunk* sound_bullet,Mix_Chunk* sound_jump);
protected:
    SDL_Rect frame_clip_[20];
    int frame_;
    int width_frame_;
    int height_frame_;

    bool on_ground_;
    int comeback_time_;

    float x_pos_;
    float y_pos_;
    float x_val_;
    float y_val_;
    int map_x_;
    int map_y_;

    Input input_type_;
    int animation_right_;
    int animation_left_;
    int type_move_;
    std::vector<BulletObject*> bullet_list_;
    int frame_bullet_;
    int hp_;
    int enemy_frame_num_;
    float threats_gravity_speed_;
    int threats_max_fall_speed_;
    int threats_speed_;
    int threats_status_;
    int w_sensor_;
    int h_sensor_;
    int w_atack_;
    int h_atack_;
    int timewait_;
    int threats_level_;
    std::string path_img[4];
    bool is_fire_;
    std::vector<Input> Input_;

    static Mix_Chunk* sound_bullet_;
    static Mix_Chunk* sound_jump_;
};

#endif