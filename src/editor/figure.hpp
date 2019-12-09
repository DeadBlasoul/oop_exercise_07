#pragma once

#include <cstdint>

#include "system/renderer.hpp"
#include "editor/drawable.hpp"

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
    };


}