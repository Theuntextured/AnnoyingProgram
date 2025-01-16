#pragma once
#include "WindowManager.h"
#include "../Timings/Tickable.h"
#include "../Engine/ExternalProcessHandler.h"

class AntiTaskManager final : public Tickable
{
public:
    AntiTaskManager();
    ~AntiTaskManager();

    void tick(const double delta_time) override;
    void close_task_manager();
    void warn_about_task_manager();
    
    bool warn_only = false;
    WindowManager* window_manager = nullptr;
};