#pragma once
#include "../Timings/Tickable.h"
#include "../Engine/ExternalProcessHandler.h"

class AntiTaskManager final : public Tickable
{
public:
    AntiTaskManager();
    ~AntiTaskManager();

    void tick(const double delta_time) override;
};