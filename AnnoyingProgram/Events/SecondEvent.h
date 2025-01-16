#pragma once
#include "EventCommonIncludes.h"

#define MAX_WINDOWS 30

class MovingWindow : public WindowManager
{
public:
    MovingWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
    ~MovingWindow();
    
    void tick(const double delta_time) override;
    void move();
    
    sf::Vector2f velocity;
    std::atomic_bool processing = false;

    double last_dt = 0;
    sf::Thread* thread;
};

class SecondEvent : public Event
{
public:
    SecondEvent();
    void start() override;
    void end() override;
    void tick(double delta_time) override;
    void create_window();
    void start_second_phase();
    void transition();
    
    void on_window_closed();
    
    std::vector<MovingWindow*> windows;
    double current_tick_time = 0;
    std::vector<sf::String> possible_texts;
    bool running = true;
    double window_open_delay = 1.;
    bool second_phase = false;
    WindowManager* transition_window = nullptr;
    AntiTaskbar* anti_taskbar = nullptr;
    AntiTaskManager* anti_task_manager = nullptr;
};
