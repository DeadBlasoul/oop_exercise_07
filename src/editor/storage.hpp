#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "editor/drawable.hpp"
#include "editor/figure.hpp"

namespace oop::editor
{
    using fig_ptr = std::shared_ptr<i_figure>;

    struct action {
        enum class type {
            add,
            remove
        };

        type    ty;
        fig_ptr fig;
        size_t  ix; // internal value, has no effect in API
    };

    struct storage : i_drawable
    {
        void draw(system::renderer& renderer) override
        {
            for (auto fig : *this)
            {
                fig->draw(renderer);
            }
        }

        void commit(const action& act) {
            action commited = act;

            switch (act.ty)
            {
            case action::type::add:
            {
                figures_.push_back(act.fig);
                commited.ix = figures_.size() - 1;
                break;
            }
            case action::type::remove:
            {
                if (auto it = std::find(figures_.begin(), figures_.end(), act.fig); it != figures_.end()) {
                    commited.ix = figures_.erase(it) - figures_.begin();
                }
                else
                {
                    throw std::runtime_error("unable to delete unknown figure");
                }
                break;
            }
            }

            actions_.push_back(commited);
        }

        void undo_last_change()
        {
            if (actions_.empty())
            {
                return;
            }

            auto& last = actions_[actions_.size() - 1];

            switch (last.ty)
            {
            case action::type::add:
            {
                figures_.erase(figures_.end() - 1);
                actions_.erase(actions_.end() - 1);
                break;
            }
            case action::type::remove:
            {
                auto it  = actions_.end() - 1;
                auto fig = it->fig;
                figures_.insert(figures_.begin() + it->ix, fig);
                actions_.erase(it);
                break;
            }
            }
        }

        void remove(const vec2& p)
        {
            size_t size = figures_.size();
            for (size_t i = 1; i <= size; ++i)
            {
                if (figures_[size - i]->inside(p))
                {
                    action act = { action::type::remove, figures_[size - i] };
                    commit(act);
                    break;
                }
            }
        }

        void open(std::string_view filename)
        {
            std::vector<fig_ptr> figs;
        }

        void save(std::string_view filename)
        {

        }

        using const_iterator = std::vector<fig_ptr>::const_iterator;

        const_iterator begin() const
        {
            return figures_.begin();
        }

        const_iterator end() const
        {
            return figures_.end();
        }

        /*!
         * @brief undo last change in associated storage
         */
        void undo(std::vector<fig_ptr>& storage);
    private:
        std::vector<action>  actions_;
        std::vector<fig_ptr> figures_;
    };
}