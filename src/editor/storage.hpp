#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <vector>

#include "editor/drawable.hpp"
#include "editor/figure.hpp"

namespace oop::editor
{
    using fig_ptr = std::shared_ptr<i_figure>;

    struct i_command
    {
        virtual ~i_command() = 0;

        virtual bool commit(std::vector<fig_ptr>& figs) = 0;
        virtual void reset(std::vector<fig_ptr>& figs) = 0;
    };

    inline i_command::~i_command() = default;

    typedef std::shared_ptr<i_command> cmd_ptr;

    struct storage final : i_drawable
    {
        void draw(system::renderer& renderer) override
        {
            for (auto fig : *this)
            {
                fig->draw(renderer);
            }
        }

        void commit(const cmd_ptr& cmd)
        {
            if (cmd->commit(figures_))
            {
                commands_.push_back(cmd);
            }
        }

        void undo()
        {
            if (commands_.empty())
            {
                return;
            }

            const auto last = commands_.end() - 1;
            (*last)->reset(figures_);
            commands_.erase(last);
        }

        void clear()
        {
            actions_.clear();
            figures_.clear();
        }

        void push_back(fig_ptr fig)
        {
            figures_.push_back(fig);
        }

        void save(std::string_view filename)
        {
            std::fstream f;
            f.open(filename.data(), std::ios_base::out);

            for (auto& fig : *this)
            {
                fig->serialize(f);
                f << std::endl;
            }
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
        std::vector<cmd_ptr> commands_;
        std::vector<fig_ptr> figures_;
    };
}