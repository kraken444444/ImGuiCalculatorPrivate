#pragma once
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
class ButtonHelper
{

public:
    void SetButtonColor(const float color[4]);
    void PopButtonColor();
   
};

