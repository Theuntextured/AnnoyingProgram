#include "FirstEvent.h"

#define DO_DELAY

PhaseProperties::PhaseProperties(const sf::String& text, const sf::Color& text_color, const sf::String& font_name,
    const unsigned int text_size, const sf::Uint8 window_style, const sf::VideoMode& video_mode,
    const sf::String& title, const double time_until_next_phase, const bool random_shit, const Delegate& delegate)
{
    this->text = text;
    this->text_color = text_color;
    this->font_name = font_name;
    this->text_size = text_size;
    this->window_style = window_style;
    this->video_mode = video_mode;
    this->time_until_next = time_until_next_phase;
    this->title = title;
    this->delegate = delegate;
    this->random_shit = random_shit;
}

FirstEvent::FirstEvent()
{
    phases = {
        PhaseProperties("Hello! :)", sf::Color::White, "HARLOWSI", 24, sf::Style::Close, sf::VideoMode(200, 50), "Hello", 3.),
        PhaseProperties("Well... Hello?", sf::Color::White, "HARLOWSI", 24, sf::Style::Close, sf::VideoMode(200, 50), "Hello", 3.),
        PhaseProperties("I really like you :)", sf::Color::White, "LHANDW", 24, sf::Style::Close, sf::VideoMode(400, 50), "Hey there", .5),
        PhaseProperties("I do...", sf::Color::White, "LHANDW", 24, sf::Style::Close, sf::VideoMode(100, 50), "Hey there", 1.),
        PhaseProperties("Why do you keep sending me away?", sf::Color::White, "LHANDW", 24, sf::Style::Close, sf::VideoMode(600, 50), "Hey there", .5),
        PhaseProperties("Hey!", sf::Color::White, "COOPBL", 24, sf::Style::Close, sf::VideoMode(100, 50), ">:(", 3.),
        PhaseProperties("Stop!", sf::Color::White, "COOPBL", 24, sf::Style::Close, sf::VideoMode(100, 50), ">:(", 1.),
        PhaseProperties("Stop!", sf::Color::Red, "COOPBL", 72, sf::Style::Close, sf::VideoMode(300, 150), ">:(", 3.),
        PhaseProperties("Alright...", sf::Color::White, "COOPBL", 12, sf::Style::Close, sf::VideoMode(100, 50), ">:(", 1.),
        PhaseProperties("Close me now....", sf::Color::White, "Arial", 24, sf::Style::Titlebar, sf::VideoMode(300, 50), ">:(", 5.), 
        PhaseProperties("Oh...", sf::Color::White, "Arial", 24, sf::Style::Close, sf::VideoMode(50, 50), ":o", 1.),
        PhaseProperties("Well... Since you like closing windows so much...", sf::Color::Cyan, "Arial", 24, sf::Style::Close, sf::VideoMode(600, 50), ">:)", 5)
    };
}

void FirstEvent::start()
{
    anti_task_manager = new AntiTaskManager();
    
    next_phase();
}

void FirstEvent::end()
{
    window_manager->mark_for_deletion();
    anti_task_manager->mark_for_deletion();
}

void FirstEvent::next_phase()
{
    current_phase++;
    if(phases.size() <= static_cast<size_t>(current_phase))
    {
        end_internal();
        return;
    }
    
    const auto& phase = phases[current_phase];
    
    const auto text = new TextWidget();
    text->setString(phase.text);
    text->setFillColor(phase.random_shit ? rand_color() : phase.text_color);
    if(phase.random_shit)
    {
        text->setOutlineColor(rand_color());
        text->setOutlineThickness(rand_range(0.f, 2.f));
    }
    text->setFont(phase.random_shit ? FontManager::get_random_font() : FontManager::get_font_by_name(phase.font_name));
    text->setCharacterSize(phase.text_size);
    text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);

    if(!window_manager)
    {
        window_manager = new WindowManager(phase.video_mode, phase.title, phase.window_style);
        window_manager->on_request_close.bind(this, &FirstEvent::on_window_closed);
    }
    else
    {
        for(const auto w : window_manager->widgets)
        {
            w->mark_for_deletion();
            w->remove_from_parent();
        }
        window_manager->create(phase.video_mode, phase.title, phase.window_style);
    }

    if(phase.random_shit)
        window_manager->background_color = rand_color();
    
    text->add_to_parent(window_manager);
    

    sf::Transform target_transform = sf::Transform::Identity;
    target_transform.translate(static_cast<sf::Vector2f>(window_manager->getSize()) / 2.f);

    sf::Transform original_transform = target_transform;
    original_transform.scale(0.0,0.0);

    auto tl = new TransformTimeline(this, {{0., original_transform}, {2., target_transform}});
    tl->bind_property(text->local_transform);
    tl->play();
}

void FirstEvent::on_window_closed()
{
#ifdef DO_DELAY
    Timer::create_timer_by_function(this, &FirstEvent::next_phase, phases[current_phase].time_until_next);
#else
    next_phase();
#endif
}
