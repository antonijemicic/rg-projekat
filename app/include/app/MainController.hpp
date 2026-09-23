#pragma once

#include <engine/core/Engine.hpp>

namespace app {

    class MainController final : public engine::core::Controller {
    protected:
        void initialize() override;
        void draw() override;

    private:
        engine::resources::Model *m_model{};
        engine::resources::Shader *m_shader{};
    };

} // namespace app