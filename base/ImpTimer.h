#ifndef IMP_TIMER_H
#define IMP_TIMER_H

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool is_start();
    bool is_pause();
private:
    int start_tick_;
    int pause_tick_;

    bool is_paused_;
    bool is_started_;
};

#endif