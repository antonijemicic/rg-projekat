//
// Created by Administrator on 9/12/2026.
//

#ifndef MATF_RG_PROJECT_MAINAPP_HPP
#define MATF_RG_PROJECT_MAINAPP_HPP

#include <engine/core/Engine.hpp>

namespace app {
    class MainApp final : public engine::core::App {
    private:
        void app_setup() override;
    };
} // namespace app

#endif //MATF_RG_PROJECT_MAINAPP_HPP
