#pragma once
#include "CommonLib.h"
#include "Widget.h"
#include "Timeline.h"

class Button : public Widget
{
public:
	Button();
	void draw(sf::RenderWindow* window) override;
	void tick(const double delta_time) override;
	bool accepts_children() override;
	bool is_pressed() const;
	bool is_hovered() const;
	
	sf::RectangleShape shape;
	
	Delegate on_pressed;
	Delegate on_released;
	Delegate on_hover_start;
	Delegate on_hovering;
	Delegate on_hover_end;
	
private:
	bool is_pressed_ = false;
	bool is_hovering_ = false;
};
