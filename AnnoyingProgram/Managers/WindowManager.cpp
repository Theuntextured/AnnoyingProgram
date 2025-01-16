#include "WindowManager.h"

#include <assert.h>
#include <windows.h>

std::vector<sf::Uint8> WindowManager::icon_pixels;

WindowManager::WindowManager() = default;

WindowManager::WindowManager(sf::VideoMode mode, const sf::String& title, sf::Uint32 style,
    const sf::ContextSettings& settings) : WindowManager()
{
    create(mode, title, style, settings);

    set_icon();
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

void WindowManager::create(sf::VideoMode mode, const sf::String& title, sf::Uint32 style)
{
    RenderWindow::create(mode, title, style);

    set_icon();
    setFramerateLimit(MAX_FPS);
}

void WindowManager::create(sf::VideoMode mode, const sf::String& title, sf::Uint32 style,
    const sf::ContextSettings& settings)
{
    RenderWindow::create(mode, title, style, settings);

    requestFocus();
    set_icon();
    setFramerateLimit(MAX_FPS);
}

void WindowManager::set_icon()
{
    if(icon_pixels.empty())
    {
        icon_pixels.reserve(64 * 64 * 4);

        for(size_t y = 0; y < 64; y++)
            for(size_t x = 0; x < 64; x++)
            {
                auto upper = [](const float x)
                {
                    return (sqrt(1 - square(abs(x) - 1)) + 3.1415926535897932384) / 4.1415926535897932384;
                };
                auto lower = [](const float x)
                {
                    return acos(1 - abs(x)) / 4.1415926535897932384;
                };
                
                bool should_color = 64 * upper((2 * x - 64.) / 32.) > 64 - y && 64 - y > 64 * lower((2 * x - 64.) / 32.);
                
                icon_pixels.push_back(255);
                icon_pixels.push_back(0);
                icon_pixels.push_back(0);
                icon_pixels.push_back(should_color ? 255 : 0);
            }
    }
    
    setIcon(64, 64, icon_pixels.data());
}


void WindowManager::handle_events()
{
    sf::Event event;
    while (pollEvent(event))
    {
        if (event.type == sf::Event::Closed || IsIconic(getSystemHandle()))
        {
            if(can_close)
                close();
            on_request_close();
        }
    }
}
