#pragma once
#include "Widget.h"
#include "Tickable.h"

class WindowManager : public sf::RenderWindow, public Tickable
{
public:
	WindowManager();
	WindowManager(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
	void tick(const double delta_time) override;

	void handle_events();
	
	std::vector<Widget*> widgets;

	Delegate on_closed;
};
