#include "FinalEvent.h"

FinalEvent::FinalEvent()
{
    phases = {
        PhaseProperties("Well...", sf::Color::White, "HARLOWSI", 24, sf::Style::Close, sf::VideoMode(200, 50), ":(", .5),
        PhaseProperties("You forced me.", sf::Color::White, "HARLOWSI", 24, sf::Style::Close, sf::VideoMode(200, 50), ":(", .5),
        
        PhaseProperties("I love you :)", sf::Color::Magenta, "HARLOWSI", 24, sf::Style::Titlebar, sf::VideoMode(200, 50), "<3", 3., true),
        };
}

void FinalEvent::start()
{
    FirstEvent::start();
    anti_task_manager->warn_only = true;
}

void FinalEvent::end()
{
    FirstEvent::end();
}

void FinalEvent::tick(const double delta_time)
{
    FirstEvent::tick(delta_time);
}

void FinalEvent::next_phase()
{
    if (static_cast<int>(phases.size() - 1) == current_phase)
        current_phase--;
    FirstEvent::next_phase();
}
