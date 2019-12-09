#pragma once

#include <tuple>
#include <istream>

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

inline std::istream& operator>>(std::istream& s, oop::editor::brush& brush)
{
    int r, g, b;
    s >> r >> g >> b;

    brush = oop::editor::brush{r / 255.0f, g / 255.0f, b / 255.0f };

    return s;
}