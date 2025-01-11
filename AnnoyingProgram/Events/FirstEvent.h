#pragma once
#include "EventCommonIncludes.h"

struct PhaseProperties
{    
    PhaseProperties(const sf::String& text,
                    const sf::Color& text_color,
                    const sf::String& font_name,
                    const unsigned int text_size,
                    const sf::Uint8 window_style,
                    const sf::VideoMode& video_mode,
                    const sf::String& title,
                    const double time_until_next_phase);
    
    sf::String text;
    sf::Color text_color;
    sf::String font_name;
    unsigned int text_size;
    
    sf::Uint8 window_style;
    sf::VideoMode video_mode;
    sf::String title;
    
    double time_until_next;
};

class FirstEvent : public Event
{
    public: void start() override;
    void end() override;
    void tick() override;

    void next_phase();
    void on_window_closed();
    bool next_phase_queued;
    int current_phase = -1;
    std::vector<PhaseProperties> phases;

    WindowManager* window_manager = nullptr;
};
