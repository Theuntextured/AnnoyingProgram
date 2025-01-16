#include "SecondEvent.h"


MovingWindow::MovingWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style,
    const sf::ContextSettings& settings) : WindowManager(mode, title, style, settings)
{
    thread = new sf::Thread(&MovingWindow::move, this);
}

MovingWindow::~MovingWindow()
{
    WindowManager::~WindowManager();
    delete thread;
}

void MovingWindow::tick(const double delta_time)
{
    WindowManager::tick(delta_time);
    if (velocity == sf::Vector2f(0, 0)) return;

    if(processing.load()) return;
    
    last_dt = delta_time;

    //delete thread;

    //thread = new sf::Thread(&MovingWindow::move, this);
    processing.store(true);
    thread->launch();
}

void MovingWindow::move()
{
    const auto bounds = sf::Vector2i(sf::VideoMode::getDesktopMode().width - getSize().x,
                                 sf::VideoMode::getDesktopMode().height - getSize().y);
    auto new_pos = getPosition() + static_cast<sf::Vector2i>(static_cast<float>(last_dt) * velocity);
    if (new_pos.x > bounds.x || new_pos.x < 0)
    {
        velocity.x *= -1;
        new_pos.x = clamp(new_pos.x, 0, bounds.x);
    }
    if (new_pos.y > bounds.y || new_pos.y < 0)
    {
        velocity.y *= -1;
        new_pos.y = clamp(new_pos.y, 0, bounds.y);
    }

    setPosition(new_pos);
    processing.store(false);
}

SecondEvent::SecondEvent()
{
    possible_texts = {
        "Close me",
        "Close this",
        "HELLO!",
        "Hey there!",
        "Hello there!",
        "Hello <3",
        "Hello! :)",
        "I love you!",
        "Love you :)",
        "Hey!",
        "UwU",
        
    };
}

void SecondEvent::start()
{
    anti_task_manager = new AntiTaskManager;
    anti_taskbar = new AntiTaskbar;
    windows.reserve(10);
    for(int i = 0; i < 10; i++)
        create_window();
}

void SecondEvent::end()
{
    anti_task_manager->mark_for_deletion();
    anti_taskbar->mark_for_deletion();
    for(const auto w : windows)
        w->mark_for_deletion();
}

#define WINDOW_OPEN_DELAY 1.
void SecondEvent::tick(const double delta_time)
{
    if(second_phase) return;
    if((current_tick_time += delta_time) > WINDOW_OPEN_DELAY &&running)
    {
        create_window();
        current_tick_time -= WINDOW_OPEN_DELAY;
    }
}

void SecondEvent::create_window()
{
    if(windows.size() >= MAX_WINDOWS) return;
    
    auto w = new MovingWindow({200, 50}, ">:)", sf::Style::Close);
    if(second_phase)
    {
        w->velocity = rand_vec2(sf::Vector2f(-1, -1), sf::Vector2f(1, 1));
        w->velocity /= sqrt(square(w->velocity.x) + square(w->velocity.y));
        w->velocity *= rand_range(50.f, 300.f);
    }
    windows.push_back(w);
    w->setPosition(rand_vec2(sf::Vector2i(0, 0),
                                          sf::Vector2i(
                                              sf::VideoMode::getDesktopMode().width - w->getSize().x,
                                              sf::VideoMode::getDesktopMode().height - w->getSize().y - 100
                                              )));

    w->background_color = rand_color();
    w->on_request_close.bind(this, &SecondEvent::on_window_closed);

    const auto t = new TextWidget;
    t->setString(possible_texts[rand() % possible_texts.size()]);
    t->setFillColor(rand_color());
    t->setOutlineColor(rand_color());
    t->setOutlineThickness(1);
    t->add_to_parent(w);
    t->local_transform.translate(static_cast<sf::Vector2f>(w->getSize()) / 2.f);
    centre_drawable(t);
    
    t->setFont(FontManager::get_random_font());
}

void SecondEvent::start_second_phase()
{
    second_phase = true;
    for(int i = 0; i < MAX_WINDOWS; i++)
        create_window();
}

void SecondEvent::transition()
{
    if(second_phase)
    {
        end_internal();
        return;
    }
    transition_window = new WindowManager({520, 50}, "Enjoying yourself?", sf::Style::Close);
    const auto txt = new TextWidget;
    txt->setString("Too easy? Let me \"move\" things up a notch...");
    txt->local_transform.translate(static_cast<sf::Vector2f>(transition_window->getSize()) / 2.f);
    centre_drawable(txt);
    txt->add_to_parent(transition_window);

    transition_window->on_request_close.bind(this, &SecondEvent::start_second_phase);
}

void SecondEvent::on_window_closed()
{
    for(size_t i = 0; i < windows.size(); i++)
    {
        if(windows[i]->isOpen()) continue;

        windows[i]->mark_for_deletion();
        windows.erase(windows.begin() + static_cast<long long>(i));
        i--;
    }
    if(windows.size() <= 1)
        running = false;

    if(windows.empty())
        Timer::create_timer_by_function(this, &SecondEvent::transition, 3, false);
}
