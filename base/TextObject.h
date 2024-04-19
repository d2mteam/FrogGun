#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H
#include "basefuction.h"
class TextObject
{
public:
    TextObject();
    ~TextObject();
    enum TextColour
    {
        RED_TEXT = 10,
        WHITE_TEXT = 11,
        BLACK_TEXT = 12,
    };

    bool LoadFromFile(std::string path);
    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();
    void SetColor(int type);
    void SetColor(Uint8 red, Uint8 green,Uint8 blue);

    void RenderText(SDL_Renderer* screen, 
                    int xp, int yp, 
                    SDL_Rect* clip = NULL, 
                    double angle = 0.0, 
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
    int GetWidth() const {return width_;}
    int GetHeight() const {return height_;}
    
    void SetText(const std::string& text) { str_val_ = text;}
private:
    std::string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
};

#endif