#pragma once
#include "EventCommonIncludes.h"
#include "FirstEvent.h"

class FinalEvent : public FirstEvent
{
public:
    FinalEvent();
    
    void start() override;
    void end() override;
    void tick(const double delta_time) override;

    void next_phase() override;
};
