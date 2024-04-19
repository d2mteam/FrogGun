#include "ImpTimer.h"
#include "basefuction.h"
ImpTimer::ImpTimer()
{
    start_tick_ = 0;
    pause_tick_ = 0;
    is_paused_ = false;
    is_started_ = false;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick_ = SDL_GetTicks();
}

void ImpTimer::stop(){
    is_started_ = false;
    is_paused_ = false;
}

void ImpTimer::pause(){
    if(is_started_ == true && is_paused_ == false)
    {
        is_paused_ = true;
        pause_tick_ = SDL_GetTicks() - start_tick_;
    }
}

void ImpTimer::unpause()
{
    if(is_paused_ == true)
    {
        is_paused_ = false;
        start_tick_ = SDL_GetTicks() - pause_tick_;
        pause_tick_ = 0;
    }
}

int ImpTimer::get_ticks()
{
    if(is_started_ == true)
    {
        if(is_paused_ == true)
        {
            return pause_tick_;
        }
        else
        {
            return SDL_GetTicks() - start_tick_;
        }
    }
    return 0;
}

bool ImpTimer::is_start()
{
    return is_started_;
}

bool ImpTimer::is_pause()
{
    return is_paused_;
}