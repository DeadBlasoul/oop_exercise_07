#include "application_base.hpp"

#include "imgui.h"
#include "imgui_sdl.h"
#include "imgui_impl_sdl.h"

#include <atomic>
#include <stdexcept>

using namespace oop::system;

std::atomic_bool application_base::running_ = false;

application_base::application_base()
    : window_{nullptr}
    , renderer_{nullptr}
{
    auto expected = false;
    if (auto const ok = running_.compare_exchange_strong(expected, true); !ok)
    {
        throw std::runtime_error("application: already running");
    }

    window_ = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);

    ImGui::CreateContext();

    // ImGui_ImplSDL2_InitForOpenGL is a wrapper for ImGui_ImplSDL2_Init which ignores sdl_gl_context.
    ImGui_ImplSDL2_InitForOpenGL(window_, nullptr);

    ImGuiSDL::Initialize(renderer_, 800, 600);
    ImGui_ImplSDL2_NewFrame(window_);
    ImGui::NewFrame();
}

application_base::~application_base()
{
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    running_.store(false);
}

int application_base::start(std::string_view name, int argc, char* argv[])
{
//    configure();
    run();
    return 0;
}

void application_base::run()
{
    while (!done_)
    {
        process_events();
        construct_frame();
        update();
    }
}

void application_base::process_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        process_event(event);

        if (event.type == SDL_QUIT)
        {
            done_ = true;
        }
    }
}

void application_base::process_event(const SDL_Event& event)
{
    // Placeholder
}

void application_base::construct_frame()
{
    // Placeholder
}

void application_base::update() const
{
    renderer_.update(window_);
}
