#include "FirstEvent.h"


PhaseProperties::PhaseProperties(const sf::String& text, const sf::Color& text_color, const sf::String& font_name,
    const unsigned int text_size, const sf::Uint8 window_style, const sf::VideoMode& video_mode,
    const sf::String& title, const double time_until_next_phase)
{
    this->text = text;
    this->text_color = text_color;
    this->font_name = font_name;
    this->text_size = text_size;
    this->window_style = window_style;
    this->video_mode = video_mode;
    this->time_until_next = time_until_next_phase;
    this->title = title;
}

void FirstEvent::start()
{
    
}

void FirstEvent::end()
{

}

void FirstEvent::tick()
{

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
    text->setFillColor(phase.text_color);
    text->setFont(FontManager::get_font_by_name(phase.font_name));
    text->setCharacterSize(phase.text_size);
    text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);

    if(!window_manager)
    {
        window_manager = new WindowManager(phase.video_mode, phase.title, phase.window_style);
       // window_manager->on_closed = Delegate(this, &FirstEvent::on_window_closed);
    }
    else
    {
        window_manager->create(phase.video_mode, phase.title, phase.window_style);
    }
    
    text->add_to_window(window_manager);
    

    sf::Transform target_transform = sf::Transform::Identity;
    target_transform.translate(window_manager->getSize().x / 2, window_manager->getSize().y / 2);

    sf::Transform original_transform = target_transform;
    original_transform.scale(0.0,0.0);

    auto tl = new TransformTimeline({{0., original_transform}, {2., target_transform}});
    tl->bind_property(text->local_transform);
    tl->play();
}

void FirstEvent::on_window_closed()
{
}
