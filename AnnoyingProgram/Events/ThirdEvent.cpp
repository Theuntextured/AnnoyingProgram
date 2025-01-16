#include "ThirdEvent.h"

#include <random>


#define ELASTIC_FORCE_MULTIPLIER 2.f
#define REPULSION_FORCE_MULTIPLIER 1000000.f
#define DAMPING_FACTOR .35f
#define RADIUS_MULTIPLIER 1.5f

EscapingWindow::EscapingWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style,
const sf::ContextSettings& settings) : WindowManager::WindowManager(mode, title, style, settings)
{
    window_position = {rand_range<float>(0, sf::VideoMode::getDesktopMode().width), rand_range<float>(0, sf::VideoMode::getDesktopMode().width)};
    
    target_pos = sf::Vector2f(static_cast<float>(sf::VideoMode::getDesktopMode().width),
                                 static_cast<float>(sf::VideoMode::getDesktopMode().height)) / 2.f;
    radius = len(static_cast<sf::Vector2f>(getSize())) / 2.f * RADIUS_MULTIPLIER;

    auto target = this;
    auto func = [target]() {
        target->setPosition(static_cast<sf::Vector2i>(target->window_position)
                                - static_cast<sf::Vector2i>(target->getSize() / 2u));
        target->running = false;
    };
    
    thread = new sf::Thread(func);


    std::vector colors = {
        sf::Color::Black,
        sf::Color::White,
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Cyan
    };

    std::ranges::shuffle(colors, std::default_random_engine(rand()));

    std::vector<TimelinePoint<sf::Color>> points;
    
    for(size_t i = 0; i < colors.size(); i++)
    {
        points.emplace_back(static_cast<double>(i), *(colors.begin() + i));
    }
    
    const auto ctl = new ColorTimeline(this, points);
        

    ctl->bind_property(background_color);
    ctl->play(TimelinePlayType::PingPong);

    const auto txt = new TextWidget;
    txt->setString("Catch me!");
    txt->setFont(FontManager::get_fallback_font());
    txt->setFillColor(rand_color());
    txt->setOutlineColor(rand_color());
    txt->setOutlineThickness(1);
    txt->setCharacterSize(24);
    txt->local_transform.translate(static_cast<sf::Vector2f>(getSize() / 2u));
    centre_drawable(txt);
    txt->add_to_parent(this);
}

EscapingWindow::~EscapingWindow()
{
    delete thread;
}

void EscapingWindow::tick(const double delta_time)
{
    WindowManager::tick(delta_time);
    
    const auto mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());

    auto acceleration = ELASTIC_FORCE_MULTIPLIER * (target_pos - window_position);
    
    const auto diff = window_position + sf::Vector2f(static_cast<float>(getSize().x / 2u),
                                    - static_cast<float>(getSize().y / 2u))
                                    - mouse_pos;
    const auto len_diff = len(diff);
    
    acceleration += (diff / len_diff) * REPULSION_FORCE_MULTIPLIER / std::max(1.f, square(len_diff) - radius);
    
    window_velocity += acceleration * static_cast<float>(delta_time);
    window_velocity *= std::pow(1 - DAMPING_FACTOR, static_cast<float>(delta_time));
    window_position = window_position + (window_velocity * static_cast<float>(delta_time));
    
#ifdef _DEBUG
    std::cout <<    "Pos: " << vec_to_string(window_position) <<
                    "\nVelocity: " << vec_to_string(window_velocity) <<
                    "\nAccel: " << vec_to_string(acceleration) <<
                    "\nMouse Pos: " << vec_to_string(mouse_pos) <<
                    "\nTarget Pos: " << vec_to_string(target_pos) <<
                    std::endl << std::endl;
#endif
    
    if(running) return;

    running = true;
    thread->launch();
}

ThirdEvent::ThirdEvent() = default;

ThirdEvent::~ThirdEvent() = default;

void ThirdEvent::start()
{
    anti_taskbar = new AntiTaskbar;
    transition_window_manager = new WindowManager({800, 200}, "Rude...", sf::Style::Close);

    const auto txt = new TextWidget;
    txt->setString("Try closing these then >:)");
    txt->setFont(FontManager::get_fallback_font());
    txt->setCharacterSize(30);
    txt->setFillColor(sf::Color::Cyan);
    centre_drawable(txt);
    txt->local_transform.translate(static_cast<sf::Vector2f>(transition_window_manager->getSize() / 2u));
    txt->add_to_parent(transition_window_manager);
    transition_window_manager->on_request_close.bind(this, &ThirdEvent::cont);
    
}

void ThirdEvent::end()
{
    anti_taskbar->mark_for_deletion();
}

void ThirdEvent::tick(const double delta_time)
{
    
}

void ThirdEvent::cont()
{
    for(int i = 0; i < 20; i++)
    {
        const auto w = new EscapingWindow({150, 50}, ">:)", sf::Style::Close);
        moving_windows.push_back(w);

        w->on_request_close.bind(this, &ThirdEvent::on_close);
    }
}

void ThirdEvent::on_close()
{
    for(size_t i = 0; i < moving_windows.size(); i++)
    {
        if(moving_windows[i]->isOpen()) continue;

        moving_windows[i]->mark_for_deletion();
        moving_windows.erase(moving_windows.begin() + static_cast<long long>(i));
        i--;
    }

    if(moving_windows.empty())
    {
        end_internal();
    }
}
