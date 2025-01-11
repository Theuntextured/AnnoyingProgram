#pragma once
#include "../WidgetBase/Widget.h"
#include "../Timings/Tickable.h"

class WindowManager : public sf::RenderWindow, public Tickable
{
public:
	WindowManager();
	WindowManager(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
	~WindowManager();
	void tick(const double delta_time) override;

	void handle_events();
	
	std::vector<Widget*> widgets;
	sf::Color background_color = sf::Color::Black;
	sf::Thread* input_handling_thread;
	std::atomic<bool> is_processing_input = false;

	Delegate on_closed;
};
