#pragma once

#include "editor/drawable.hpp"
#include "editor/figure.hpp"

namespace oop::editor
{
    struct i_builder: i_drawable
    {
        i_builder() = default;
        i_builder(const i_builder&) = default;
        i_builder(i_builder&&) noexcept = default;
        i_builder& operator=(const i_builder&) = default;
        i_builder& operator=(i_builder&&) noexcept = default;
        ~i_builder() = 0;

        /*!
         * @brief
         * Builds figure click-by-click
         *
         * @param event
         * Mouse event on editor
         *
         * @return true if figure complete
         */
        virtual bool next(const SDL_MouseButtonEvent& event) = 0;
    };

    inline i_builder::~i_builder() = default;
}