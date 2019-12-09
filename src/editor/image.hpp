#pragma once

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
    };
}