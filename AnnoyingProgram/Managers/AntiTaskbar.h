#pragma once
#include "WindowManager.h"
#include "../Timings/Tickable.h"
#include "../Common/CommonLib.h"

class AntiTaskbar final : public Tickable
{
public:
    AntiTaskbar();
    ~AntiTaskbar();
    
    void tick(const double delta_time) override;
private:
    void invalidate_window();

    int task_bar_size_;
    WindowManager* warning_window_;
};
