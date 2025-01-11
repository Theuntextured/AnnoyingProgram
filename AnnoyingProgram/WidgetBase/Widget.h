#pragma once
#include "../Common/CommonLib.h"
#include "../Timings/Tickable.h"

class WindowManager;

class Widget : Tickable
{
	friend class WindowManager;
public:
	Widget();
	~Widget();
	
	bool add_to_window(WindowManager* window);
	bool add_to_parent(Widget* parent);
	bool remove_from_parent();
	WindowManager* get_window_manager() const;
	sf::Transform local_transform = sf::Transform::Identity;
protected:
	virtual void draw_widget(sf::RenderWindow* window) {}
public:
	virtual bool accepts_children() { return false; }
	sf::Transform get_transform();
	long long get_child_id();
protected:
	std::vector<Widget*> children_;
	WindowManager* window_ = nullptr;
	Widget* parent_ = nullptr;
	virtual sf::Transform get_child_transform(const size_t child_index);
private: 
	void draw_internal(sf::RenderWindow* window);
	long long recalculate_child_id();
	bool remove_from_window();
	long long child_id_ = INDEX_INVALID;
};

