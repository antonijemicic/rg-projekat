#ifndef MATF_RG_PROJECT_MAINCONTROLLER_HPP
#define MATF_RG_PROJECT_MAINCONTROLLER_HPP

#include <engine/core/Engine.hpp>

namespace app {
    class MainController final : public engine::core::Controller {
    public:
        std::string_view name() const override {
            return "app::MainController";
        }

    private:
        void initialize() override;

        bool loop() override;

        void poll_events() override;

        void update() override;

        void begin_draw() override;

        void end_draw() override;

        void update_camera();

        bool m_cursor_enabled{true};
    };
} // namespace app

#endif // MATF_RG_PROJECT_MAINCONTROLLER_HPP
