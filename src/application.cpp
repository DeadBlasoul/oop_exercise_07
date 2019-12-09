#include "application.hpp"

#include "imgui.h"

#include <iostream>
#include <vector>

#include "builders.hpp"

using namespace oop;

static void fill_with_style_color(SDL_Renderer* renderer);

application::application()
    : builder_{new idle_builder{}}
{
    ImGui::StyleColorsLight();
}

void application::process_event(const SDL_Event& event)
{
    static int i = 0;
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse && (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN)
        || io.WantCaptureKeyboard)
    {
        if (event.type == SDL_MOUSEBUTTONUP) {
            builder_.reset(new idle_builder{});
        }
    }
    else if (builder_->next(event.button))
    {
        // TODO: extract figure
        builder_.reset(new idle_builder{});
    }
}

void application::construct_frame()
{
    fill_with_style_color(renderer_);

    auto [r, g, b] = brush_.convert_u8();
    SDL_SetRenderDrawColor(renderer_, r, g, b, SDL_ALPHA_OPAQUE);

    builder_->draw(renderer_);
    construct_toolbar();
}

void application::construct_toolbar()
{
    auto const window_flags = 0
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_MenuBar
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoNav
        | ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_NoBringToFrontOnFocus;
    
    int w, h;
    SDL_GetWindowSize(window_, &w, &h);
    ImGui::SetNextWindowSize({ float(w), 0 });
    ImGui::SetNextWindowPos({ 0, 0 });

    if (!ImGui::Begin("toolbar", nullptr, window_flags))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("file"))
        {
            if (ImGui::MenuItem("open"))        open();
            if (ImGui::MenuItem("save"))        save();
            if (ImGui::MenuItem("save as ...")) save_as();
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("figure"))
        {
            ImGui::MenuItem("rhombus");
            ImGui::MenuItem("pentagon");
            ImGui::MenuItem("hexagon");
            if (ImGui::MenuItem("shape"))  builder_.reset(new shape_builder{});
            if (ImGui::MenuItem("circle")) builder_.reset(new circle_builder{});
            ImGui::EndMenu();
        }

        ImGui::SameLine();
        ImGui::ColorEdit3("", brush_.rgb, ImGuiColorEditFlags_NoInputs);

        ImGui::EndMenuBar();
    }

    ImGui::End();
}

void application::open()
{
    std::cout << "open\n";
}

void application::save()
{
    if (filename_.empty())
    {
        save_as();
        return;
    }
    std::cout << "save\n";
}

void application::save_as()
{
    std::cout << "save_as\n";
}

void fill_with_style_color(SDL_Renderer* renderer)
{
    const auto& c = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];
    SDL_SetRenderDrawColor(renderer, 255 * c.x, 255 * c.y, 255 * c.z, 255 * c.w);
    SDL_RenderClear(renderer);
}
