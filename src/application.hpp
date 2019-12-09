#pragma once

#include "system/application_base.hpp"

#include <string>
#include <vector>
#include <memory>

#include "editor/brush.hpp"
#include "editor/builder.hpp"
#include "editor/storage.hpp"

namespace oop
{
    class application final : public system::application_base
    {
    public:
        application();

    private:
        void process_event(const SDL_Event& event) override;
        void construct_frame() override;

        /*!
         * @brief constructs toolbar
         */
        void construct_toolbar();

        // Toolbar file actions
        void open();
        void save();
        void save_as();

        editor::brush                      brush_;
        std::string                        filename_ = "";
        std::unique_ptr<editor::i_builder> builder_;
        editor::storage                    storage_;
    };
}