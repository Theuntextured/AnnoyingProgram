#include "WindowManager.h"

WindowManager::WindowManager() = default;

WindowManager::WindowManager(sf::VideoMode mode, const sf::String& title, sf::Uint32 style,
    const sf::ContextSettings& settings) : WindowManager()
{
    create(mode, title, style, settings);
}

WindowManager::~WindowManager()
{
    for(const auto w : widgets)
        delete w;
}

void WindowManager::tick(const double delta_time)
{
    handle_events();
    clear(background_color);
    for(const auto w : widgets)
        w->draw_internal(this);
    display();
}


void WindowManager::handle_events()
{
    sf::Event event;
    while (pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            if(can_close)
                close();
            on_request_close();
        }
    }
}
