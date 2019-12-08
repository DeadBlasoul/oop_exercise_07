#pragma once

#include "imgui.h"

enum class mode : ImGuiWindowFlags
{
    strict = ImGuiWindowFlags_NoResize
             | ImGuiWindowFlags_NoCollapse
             | ImGuiWindowFlags_NoMove
             | ImGuiWindowFlags_NoBringToFrontOnFocus
             | ImGuiWindowFlags_NoTitleBar
};

namespace ImGui
{
    inline bool BeginStrict(const char* name, bool* p_open = nullptr)
    {
        return ImGui::Begin(name, p_open, ImGuiWindowFlags(mode::strict));
    }
}