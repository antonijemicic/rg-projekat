#ifndef MATF_RG_PROJECT_POSTPROCESSINGCONTROLLER_HPP
#define MATF_RG_PROJECT_POSTPROCESSINGCONTROLLER_HPP

#include <engine/core/Controller.hpp>
#include <engine/graphics/OpenGL.hpp>

namespace engine::resources {
    class Shader;
}

namespace engine::graphics {
    enum class PostProcessingEffect {
        None      = 0,
        Invert    = 1,
        Grayscale = 2
    };

    class PostProcessingController final : public core::Controller {
    public:
        std::string_view name() const override {
            return "PostProcessingController";
        }

        void set_effect(PostProcessingEffect effect) {
            m_effect = effect;
        }

        PostProcessingEffect effect() const {
            return m_effect;
        }

    private:
        void initialize() override;

        void begin_draw() override;

        void draw() override;

        void terminate() override;

        void resize_framebuffer(
            int width,
            int height);

        resources::Shader *m_shader{nullptr};

        PostProcessingEffect m_effect{
            PostProcessingEffect::None
        };

        OpenGL::FramebufferData m_framebuffer{};
        OpenGL::ScreenQuadData m_screen_quad{};

        int m_width{0};
        int m_height{0};
    };
} // namespace engine::graphics

#endif // MATF_RG_PROJECT_POSTPROCESSINGCONTROLLER_HPP
