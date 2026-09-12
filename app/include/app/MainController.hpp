//
// Created by Administrator on 9/12/2026.
//

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

        void begin_draw() override;

        void end_draw() override;
    };
} // namespace app

#endif //MATF_RG_PROJECT_MAINCONTROLLER_HPP
