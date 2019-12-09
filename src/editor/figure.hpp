#pragma once

#include <cstdint>
#include <iostream>

#include "system/renderer.hpp"
#include "editor/drawable.hpp"
#include "editor/brush.hpp"

namespace oop::editor
{
    struct vec2
    {
        vec2() = default;
        vec2(const int32_t x, const int32_t y)
            : x{x}
            , y{y}
        {}

        union
        {
            int32_t points[2];
            struct {
                int32_t x;
                int32_t y;
            };
        };
    };

    struct i_figure : i_drawable
    {
        i_figure() = default;
        i_figure(const i_figure&) = default;
        i_figure(i_figure&&) noexcept = default;
        i_figure& operator=(const i_figure&) = default;
        i_figure& operator=(i_figure&&) noexcept = default;
        virtual ~i_figure() = 0;

        void draw(system::renderer& renderer) override final
        {
            auto [r, g, b] = color.convert_u8();
            SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
            ondraw(renderer);
        }

        virtual bool inside(const editor::vec2&)
        {
            return false;
        }

        virtual void serialize(std::ostream& file) = 0;

        virtual void deserialize(std::istream& file) = 0;

        brush color = { 0, 0, 0 };

    private:
        virtual void ondraw(system::renderer& renderer) = 0;
    };

    inline i_figure::~i_figure() = default;
}