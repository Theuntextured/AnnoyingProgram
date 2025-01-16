#include "AntiTaskManager.h"

#include "WindowManager.h"
#include "../Timings/Timeline.h"
#include "../WidgetBase/TextWidget.h"

#define TASK_MANAGER_NAME L"Taskmgr.exe"

AntiTaskManager::AntiTaskManager()
{
    if (ExternalProcessHandler::is_process_running(TASK_MANAGER_NAME))
        ExternalProcessHandler::terminate_process(TASK_MANAGER_NAME);
}

AntiTaskManager::~AntiTaskManager()
{
    if(is_valid_object(window_manager))
        window_manager->mark_for_deletion();
}

void AntiTaskManager::tick(const double delta_time)
{
    if (!ExternalProcessHandler::is_process_running(TASK_MANAGER_NAME))
        return;

    if(warn_only)
        warn_about_task_manager();
    else
        close_task_manager();
}

void AntiTaskManager::close_task_manager()
{
    ExternalProcessHandler::terminate_process(TASK_MANAGER_NAME);

    const bool is_valid = is_valid_object(window_manager);
    if(is_valid && window_manager->isOpen())
        return;

    if(is_valid)
        window_manager->mark_for_deletion();

    window_manager = new WindowManager(sf::VideoMode::getDesktopMode(), "Womp Womp :(", sf::Style::Fullscreen);
    window_manager->background_color = sf::Color::Black;

    auto ctl = new ColorTimeline(this, {
    {.0, sf::Color::Red},         //!< Red predefined color
    {.2, sf::Color::Green},       //!< Green predefined color
    {.4, sf::Color::Blue},        //!< Blue predefined color
    {.6, sf::Color::Yellow},      //!< Yellow predefined color
    {.8, sf::Color::Magenta},     //!< Magenta predefined color
    {1., sf::Color::Cyan},  
    });
        

    ctl->bind_property(window_manager->background_color);
    ctl->play(TimelinePlayType::PingPong);

    const auto txt = new TextWidget;
    txt->setString("You Tried!!!! BUT I'M SMARTERRR!!!!");
    txt->setFillColor(sf::Color::White);
    txt->setOutlineColor(sf::Color::Black);
    txt->setOutlineThickness(1);
    txt->setCharacterSize(24);
    centre_drawable(txt);
    txt->local_transform.translate(static_cast<float>(window_manager->getSize().x) / 2.f, static_cast<float>(window_manager->getSize().y) / 2.f);
    txt->add_to_parent(window_manager);
    
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
    
    const auto ttl = new TransformTimeline(this, transforms);
    ttl->bind_property(txt->local_transform);
    ttl->play(TimelinePlayType::PingPong);
}

void AntiTaskManager::warn_about_task_manager()
{
    const bool is_valid = is_valid_object(window_manager);
    if(is_valid && window_manager->isOpen())
        return;

    if(is_valid)
        window_manager->mark_for_deletion();

    window_manager = new WindowManager({400, 200}, "Pweeseee! :3", sf::Style::Close);
    window_manager->background_color = sf::Color::Magenta;

    const auto txt = new TextWidget;
    txt->setString("Please don't let me go :(");
    txt->setFillColor(sf::Color::White);
    txt->setOutlineColor(sf::Color::Black);
    txt->setOutlineThickness(1);
    txt->setCharacterSize(32);
    centre_drawable(txt);
    txt->local_transform.translate(static_cast<float>(window_manager->getSize().x) / 2.f, static_cast<float>(window_manager->getSize().y) / 2.f);
    txt->add_to_parent(window_manager);
}
