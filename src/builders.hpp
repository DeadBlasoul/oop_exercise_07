#pragma once

#include <optional>
#include <cmath>

#include "editor/builder.hpp"
#include "editor/figure.hpp"
#include "system/sdl2.hpp"
#include "figures.hpp"

namespace oop
{
    struct idle_builder final
        : editor::i_builder
    {
        void draw(system::renderer&) override
        {
            // Placeholder
        }

        bool next(const SDL_MouseButtonEvent&) override
        {
            return false;
        }

        editor::fig_ptr extract() override
        {
            return nullptr;
        }
    };

    struct shape_builder final
        : editor::i_builder
    {
        void draw(system::renderer& renderer) override
        {
            if (vertices_.empty())
            {
                return;
            }

            const size_t size = vertices_.size();
            for (size_t i = 0; i < size - 1; i++)
            {
                const auto& v1 = vertices_[i], v2 = vertices_[i + 1];
                SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
            }

            auto const pos = ImGui::GetMousePos();
            auto const last = vertices_[size - 1];
            SDL_RenderDrawLine(renderer, last.x, last.y, int(pos.x), int(pos.y));
        }

        bool next(const SDL_MouseButtonEvent& event) override
        {
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                vertices_.emplace_back(event.x, event.y);
                if (event.button == SDL_BUTTON_RIGHT) {
                    return true;
                }
            }
            return false;
        }

        editor::fig_ptr extract() override final
        {
            return editor::fig_ptr{new shape(std::move(vertices_))};
        }

    private:
        std::vector<editor::vec2> vertices_;
    };

    struct circle_builder final
        : editor::i_builder
    {
        void draw(system::renderer& renderer) override
        {
            if (center_.has_value())
            {
                auto const & center = *center_;
                auto const pos     = ImGui::GetMousePos();
                auto const x       = pos.x - center.x;
                auto const y       = pos.y - center.y;
                auto const rad     = sqrt(x * x + y * y);
                draw_circle(renderer, int(center.x), int(center.y), int(rad));
            }
        }

        bool next(const SDL_MouseButtonEvent& event) override
        {
            if (event.type == SDL_MOUSEBUTTONUP && event.button == SDL_BUTTON_LEFT)
            {
                if (center_.has_value())
                {
                    auto const & center = *center_;
                    auto const pos     = ImGui::GetMousePos();
                    auto const x       = pos.x - center.x;
                    auto const y       = pos.y - center.y;

                    radius_ = sqrt(x * x + y * y);
                    return true;
                }
                center_.emplace(event.x, event.y);
            }
            return false;
        }

        editor::fig_ptr extract() override
        {
            return editor::fig_ptr{ new circle(center_.value(), radius_) };
        }

    private:
        float                       radius_ = 0;
        std::optional<editor::vec2> center_;
    };

    template<size_t N>
    struct polygon_builder final : editor::i_builder {
        void draw(system::renderer& renderer) override
        {
            if (vertices_.empty())
            {
                return;
            }

            const size_t size = vertices_.size();
            for (size_t i = 0; i < size - 1; i++)
            {
                const auto& v1 = vertices_[i], v2 = vertices_[i + 1];
                SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
            }

            auto const pos = ImGui::GetMousePos();
            auto const last = vertices_[size - 1];
            SDL_RenderDrawLine(renderer, last.x, last.y, int(pos.x), int(pos.y));
        }

        bool next(const SDL_MouseButtonEvent& event) override
        {
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                vertices_.emplace_back(event.x, event.y);
                if (vertices_.size() == N) {
                    return true;
                }
            }
            return false;
        }

        editor::fig_ptr extract() override
        {
            return editor::fig_ptr{ new shape(std::move(vertices_)) };
        }

    private:
        std::vector<editor::vec2> vertices_;
    };
}