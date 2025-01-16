#include "AntiTaskbar.h"

#include "../Timings/Timer.h"
#include "../WidgetBase/TextWidget.h"

AntiTaskbar::AntiTaskbar()
{
    task_bar_size_ = get_task_bar_height();
}

AntiTaskbar::~AntiTaskbar()
{
    if(warning_window_)
        warning_window_->mark_for_deletion();
}

void AntiTaskbar::tick(const double delta_time)
{
    if(sf::Mouse::getPosition().y + task_bar_size_ < sf::VideoMode::getDesktopMode().height)
        return;

    sf::Mouse::setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height) / 2);

    if(warning_window_) return;

    warning_window_ = new WindowManager({800, 200}, "NO!", sf::Style::Titlebar);
    warning_window_->background_color = sf::Color::Red;

    const auto txt = new TextWidget;
    txt->setString("STAY AWAY FROM THE TASKBAR!");
    txt->local_transform.translate(warning_window_->getSize().x / 2, warning_window_->getSize().y / 2);
    txt->add_to_parent(warning_window_);
    txt->setCharacterSize(42);
    centre_drawable(txt);

    Timer::create_timer_by_function(this, &AntiTaskbar::invalidate_window, 3);
}

void AntiTaskbar::invalidate_window()
{
    warning_window_->close();
    warning_window_->mark_for_deletion();

    warning_window_ = nullptr;
}
