#include "Button.h"

Button::Button() = default;

void Button::draw(sf::RenderWindow* window)
{
	window->draw(shape, get_transform());
}

void Button::tick(const double delta_time)
{
	const auto transform = get_transform();
	const auto mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
	const auto mouse_local_position = transform.getInverse().transformPoint(mouse_position);
	const sf::FloatRect local_bounds = shape.getLocalBounds();

	const bool overlaps = local_bounds.contains(mouse_local_position);
	if(overlaps)
	{
		if(!is_hovering_)
		{
			is_hovering_ = true;
			on_hover_start();
		}
		on_hover();
	}
	else if(is_hovering_)
	{
		is_hovering_ = false;
		on_hover_end();
		if(is_pressed_)
		{
			is_pressed_ = false;
			on_released();
		}
	}

	if(!overlaps)
		return;

	bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	//call delegates and set vars
	
}

bool Button::accepts_children()
{
	return children_.empty();
}

bool Button::is_pressed() const
{
	return is_pressed_;
}

bool Button::is_hovered() const
{
	return is_hovering_;
}
