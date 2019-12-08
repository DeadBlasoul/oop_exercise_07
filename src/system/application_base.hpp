#pragma once

#include <atomic>
#include <string>

#include "system/renderer.hpp"

namespace oop::system
{
    class application_base
    {
    public:
        /*!
         * @brief application entry point
         *
         * Starts new application instance; one per process.
         *
         *
         * @throws std::runtime_error
         * If here is already another instance exception will be thrown.
         */
        int start(std::string_view name, int argc, char* argv[]);
        int start(int argc, char* argv[])
        {
            return start("SDL2 Window", argc, argv);
        }

    protected:
        application_base();
        virtual ~application_base();

    private:
        void configure();
        void run();
        void process_events();
        void update() const;

        virtual void construct_frame();

    public:
        application_base(const application_base&) = delete;
        application_base(application_base&&) noexcept = delete;

        application_base& operator=(const application_base&) = delete;
        application_base& operator=(application_base&&) noexcept = delete;

    private:
        static std::atomic_bool running_;
        SDL_Window*             window_;
        renderer                renderer_;
    };
}