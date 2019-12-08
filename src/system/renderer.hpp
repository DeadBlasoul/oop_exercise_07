#pragma once

#include <SDL.h>

#include "imgui.h"
#include "imgui_sdl.h"
#include "imgui_impl_sdl.h"

namespace oop::system
{
    struct renderer
    {
        renderer() = default;

        explicit renderer(SDL_Renderer* renderer)
            : renderer_{ renderer }
        {}

        renderer& operator=(SDL_Renderer* renderer)
        {
            renderer_ = renderer;
            return *this;
        }

        void update(SDL_Window* window) const {
            ImGui::Render();
            ImGuiSDL::Render(ImGui::GetDrawData());
            SDL_RenderPresent(renderer_);
            ImGui_ImplSDL2_NewFrame(window);
            ImGui::NewFrame();
        }

        [[nodsicard]]
        SDL_Renderer& operator*() const noexcept
        {
            return *renderer_;
        }

        SDL_Renderer& operator->() const noexcept
        {
            return *renderer_;
        }

        [[nodsicard]]
        operator SDL_Renderer*() const noexcept
        {
            return renderer_;
        }

    private:
        SDL_Renderer* renderer_;
    };
}