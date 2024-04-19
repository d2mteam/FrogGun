#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H

#include "basefuction.h"
#include "BaseObject.h"

#define BULLET_DISTANCE_DEFAULT 320
class BulletObject : public BaseObject
{
public:
    ~BulletObject();
    BulletObject();
     enum GUN_STYLE
    {
        DEFAULT = 0,
        DOUBLE,
        WAVE,
        BOUND,
        
    };
    enum BulletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_DOWN = 22,
    };
    void set_x_val(const int& xval){x_val_ = xval;}
    void set_y_val(const int& yval){y_val_ = yval;}

    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}
    
    void set_is_move(const bool& isMove) {is_move_ = isMove;}
    bool get_is_move() const {return is_move_;}

    void set_bullet_distance(int b_d_){ bullet_distance_ = b_d_;}

    void SetMapXY(const int& mp_x, const int& mp_y){map_x_ = mp_x,map_y_ = mp_y;}
    void SetPosXY(const int& x_pos, const int& y_pos){x_pos_ = x_pos,y_pos_ = y_pos;}
    
    void set_bullet_dir(const unsigned int& bullet_dir){bullet_dir_ = bullet_dir;}
    int get_bullet_dir() const {return bullet_dir_;}
    void HandelMove();

    void set_style(const int& style) {style_ = style;}
    int get_style() const {return style_;}

    static void set_map(const Map& gamemap);
private:
    int x_val_;
    int y_val_;

    int x_pos_;
    int y_pos_;

    int map_x_;
    int map_y_;
    
    bool is_move_;
    int distance_;
    int bullet_distance_;
    int style_;
    unsigned int bullet_dir_;


    static Map gamemap_;
};
#endif