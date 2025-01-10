#include "WindowManager.h"

WindowManager::WindowManager()
{
    
}

WindowManager::WindowManager(sf::VideoMode mode, const sf::String& title, sf::Uint32 style,
    const sf::ContextSettings& settings) : WindowManager()
{
    create(mode, title, style, settings);    
}

void WindowManager::tick(const double delta_time)
{
    handle_events();
    clear();
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
            close();
            on_closed();
        }
    }
}
