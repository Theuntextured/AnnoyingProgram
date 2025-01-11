#pragma once

#include "../Common/CommonLib.h"

class Tickable : public GenericObject
{
public:
	static std::map<Tickable*, double> tickables;
	
	Tickable();
	~Tickable();
	
	virtual void tick(const double delta_time) {}
	FORCEINLINE void mark_for_deletion() { is_marked_for_deletion = true; }

	FORCEINLINE double get_tick_interval() const { return tick_interval_; }
	void set_tick_interval(const double interval);

	bool is_marked_for_deletion = false;

private:
	double tick_interval_ = 0;
};
