#include "Widget.h"

#include <assert.h>

#include "WindowManager.h"

Widget::Widget() = default;

Widget::~Widget()
{
	remove_from_parent();
	for(const auto c : children_)
		delete c;
}

bool Widget::add_to_window(WindowManager* window)
{
	CHECK_RET_FALSE(is_valid_object(window), "Tried adding a widget to an invalid window.")
	CHECK_RET_FALSE(!parent_ && !window_, "Tried adding a widget to a window, but it has already been added to a parent.")
	window_ = window;
	window->widgets.push_back(this);
	return true;
}

bool Widget::remove_from_window()
{
	if(!window_)
		return false;
	const auto id = std::find(window_->widgets.begin(), window_->widgets.end(), this);
	if(id == window_->widgets.end())
	{
		window_ = nullptr;
		return false;
	}
	window_->widgets.erase(id);
	window_ = nullptr;
	return true;
}

bool Widget::add_to_parent(Widget* parent)
{
	CHECK_RET_FALSE(is_valid_object(parent), "Tried adding a widget to an invalid window.")
	CHECK_RET_FALSE(!parent_ && !window_, "Tried adding a widget to a window, but it has already been added to a parent.")
	CHECK_RET_FALSE(parent->accepts_children(), "Tried adding a widget to a parent that doesnt accept children.")
	parent_ = parent;
	parent->children_.push_back(this);
	return true;
}

bool Widget::remove_from_parent()
{
	if(window_)
		return remove_from_window();
	if(!parent_)
		return false;
	const auto id = get_child_id();
	assert(id != INDEX_INVALID);
	parent_->children_.erase(parent_->children_.begin() + id);
	parent_ = nullptr;
	return true;
}

sf::Transform Widget::get_transform()
{
	if(window_)
	{
		return local_transform;
	}
	return parent_->get_transform() *
		parent_->get_child_transform(get_child_id()) *
		local_transform;
}

long long Widget::get_child_id()
{
	if(!parent_)
		return INDEX_INVALID;
	if(child_id_ == INDEX_INVALID || static_cast<long long>(parent_->children_.size()) >= child_id_)
		return recalculate_child_id();
	if(parent_->children_[child_id_] != this)
		return recalculate_child_id();
	return child_id_;
}

sf::Transform Widget::get_child_transform(const size_t child_index)
{
	return sf::Transform::Identity;
}

void Widget::draw_internal(sf::RenderWindow* window)
{
	draw(window);
	for(const auto i : children_)
		draw_internal(window);
}

long long Widget::recalculate_child_id()
{
	const auto it = std::find(parent_->children_.begin(), parent_->children_.end(), this);
	if(it == parent_->children_.end())
	{
		child_id_ = INDEX_INVALID;
		return INDEX_INVALID;
	}
	child_id_ = std::distance(parent_->children_.begin(), it);
	return child_id_;
}
