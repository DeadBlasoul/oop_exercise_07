#pragma once

#include <tuple>

namespace oop::editor
{
    struct brush
    {
        union
        {
            float rgb[3];
            struct
            {
                float r, g, b;
            };
        };

        std::tuple<Uint8, Uint8, Uint8> convert_u8() const noexcept
        {
            return {r * 255, g * 255, b * 255};
        }
    };
}