#pragma once
#include "EventCommonIncludes.h"

class EscapingWindow : public WindowManager
{
public:
    EscapingWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
    ~EscapingWindow();

    void tick(const double delta_time) override;

    
    sf::Vector2f target_pos;
    sf::Vector2f window_velocity = {0.f, 0.f};
    sf::Vector2f window_position;
    sf::Thread* thread;
    std::atomic_bool running = false;
    sf::Vector2f last_pos;
    float radius;
};

class ThirdEvent : public Event
{
public:
    ThirdEvent();
    ~ThirdEvent();

    void start() override;
    void end() override;
    void tick(const double delta_time) override;
    void cont();
    void on_close();

    WindowManager* transition_window_manager = nullptr;
    std::vector<WindowManager*> moving_windows;
    AntiTaskbar* anti_taskbar = nullptr;
    AntiTaskManager* anti_task_manager = nullptr;
};
