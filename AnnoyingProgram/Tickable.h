#pragma once

#include "CommonLib.h"

class Tickable : public GenericObject
{
public:
	static std::map<Tickable*, double> tickables;
	
	Tickable();
	~Tickable();
	
	virtual void tick(const double delta_time) = 0;
	
	FORCEINLINE double get_tick_interval() const { return tick_interval_; }
	void set_tick_interval(const double interval);

private:
	double tick_interval_ = 0;
};
