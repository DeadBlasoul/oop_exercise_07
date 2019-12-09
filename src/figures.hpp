#pragma once

#include <vector>

#include "geom/polygon.hpp"
#include "editor/figure.hpp"
#include "editor/brush.hpp"
#include "system/sdl2.hpp"

#include "geom/algorithm.hpp"

namespace oop
{
    template<size_t N>
    using poligon_vec2 = basic_polygon<editor::vec2, N>;

    struct shape final : editor::i_figure
    {
        explicit shape(std::vector<editor::vec2>&& storage)
            : points_(std::move(storage))
        {}

        bool inside(const editor::vec2& v)
        {
            return isInside(points_.data(), points_.size(), v);
        }

    private:
        void ondraw(system::renderer& renderer)
        {
            size_t size = points_.size();
            for (size_t i = 0; i < size; ++i) {
                auto& u = points_[i];
                auto& v = points_[(i + 1) % size];

                SDL_RenderDrawLine(renderer, u.x, u.y, v.x, v.y);
            }
        }

        std::vector<editor::vec2> points_;
    };

    struct circle final : editor::i_figure
    {
        explicit circle(const editor::vec2& pos, int radius)
            : pos_(pos)
            , rad_(radius)
        {}

        bool inside(const editor::vec2& p) override
        {
            int x = pos_.x - p.x;
            int y = pos_.y - p.y;

            return sqrt(x * x + y * y) <= rad_;
        }

    private:
        void ondraw(system::renderer& renderer)
        {
            system::draw_circle(renderer, pos_.x, pos_.y, rad_);
        }

        editor::vec2 pos_;
        int          rad_;
    };
}