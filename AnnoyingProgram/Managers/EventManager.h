#pragma once
#include "../Common/CommonLib.h"
#include "Event.h"

class EventManager
{
public:
    EventManager();
    ~EventManager();

    void tick(const double delta_time);
    void cycle_event();
    FORCEINLINE Event* get_current_event() const;

    std::vector<Event*> events;
    size_t current_event = 0;
    
    double total_time = 0;
    bool should_stop = false;

};