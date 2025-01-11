#include "EventManager.h"

#define STRINGIFY(x) #x
//adds event dir
#define EVENT_DIR(event_name) STRINGIFY(../Events/ ## event_name ## .h)
#define REGISTER_EVENT(event_class) events.push_back(new event_class());

#include EVENT_DIR(FirstEvent)

EventManager::EventManager()
{
    
REGISTER_EVENT(FirstEvent);


    if (!events.empty())
        events.back()->start_internal();
}

#undef EVENT_DIR
#undef REGISTER_EVENT

EventManager::~EventManager()
{
    for(const auto e : events)
        e->end();
}

void EventManager::tick(const double delta_time)
{
    if(!get_current_event())
    {
        should_stop = true;
        return;
    }
    if(get_current_event()->ended_)
        cycle_event();
    if(should_stop)
        return;

    get_current_event()->tick();
}

void EventManager::cycle_event()
{
    get_current_event()->end_internal();
    current_event++;
    if(current_event >= events.size())
    {
        should_stop = true;
        return;
    }
    get_current_event()->start_internal();    
}

Event* EventManager::get_current_event() const
{
    if(current_event < events.size())
        return events[current_event];
    return nullptr;
}

