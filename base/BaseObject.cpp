#include "BaseObject.h"
BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x=0;
    rect_.y=0;
    rect_.w=0;
    rect_.h=0;
}
BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path,SDL_Renderer* screen)  // image -> texture
{
    Free();
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if(load_surface == NULL)    throw std::runtime_error("Failed to load image: " + path);
    if(load_surface != NULL)
    {
        SDL_SetColorKey(load_surface,SDL_TRUE,SDL_MapRGB(load_surface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen , load_surface);
        if(new_texture != NULL){
            rect_.w=load_surface->w;
            rect_.h=load_surface->h;
        }
    }
    p_object_ = new_texture;
    SDL_FreeSurface(load_surface);
    load_surface = NULL;
    return p_object_!=NULL;
}

void BaseObject::Render(SDL_Renderer * des,const SDL_Rect* clip )  // Render image 
{
    if(rect_.x + rect_.w <=0 ||  rect_.x >= SCREEN_WIDTH || rect_.y >= SCREEN_HEIGHT || rect_.y + rect_.h <= 0) return;    
    SDL_Rect renderquad = {rect_.x,rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des,p_object_,clip,&renderquad);
}
void  BaseObject::Free() //free
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        rect_.w = 0;
        rect_.h = 0;
        p_object_ = NULL;
    }
}
   
   
   
