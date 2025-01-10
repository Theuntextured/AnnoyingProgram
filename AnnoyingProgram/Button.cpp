#include "Button.h"
#include "WindowManager.h"

Button::Button()
{
	shape.setSize(sf::Vector2f(144, 64));
	shape.setOrigin(shape.getSize() / 2.f);

	sf::Transform tr = sf::Transform::Identity;
	tr.translate(sf::Vector2f(400, 300));
	tr.rotate(45);
	tr.scale(sf::Vector2f(1.5, 1));
	
	
	auto timeline = new TransformTimeline({{0., tr}, {1, sf::Transform::Identity}});
	timeline->bind_property(local_transform);
	timeline->play(TimelinePlayType::PingPong);
}

void Button::draw(sf::RenderWindow* window)
{
	window->draw(shape, get_transform());
}

void Button::tick(const double delta_time)
{
	const auto window = get_window_manager();
	const auto transform = get_transform();
	const auto mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*static_cast<sf::RenderWindow*>(window)));
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
		on_hovering();
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

	const bool mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if(mouse_pressed)
	{
		if (!is_pressed_)
		{
			is_pressed_ = true;
			on_pressed();
		}
	}
	else if(is_pressed_)
	{
		is_pressed_ = false;
		on_released();
	}
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
