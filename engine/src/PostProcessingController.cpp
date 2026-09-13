#include <engine/graphics/PostProcessingController.hpp>

#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <engine/resources/Shader.hpp>

namespace engine::graphics {
    void PostProcessingController::initialize() {
        const auto platform =
                core::Controller::get<
                    platform::PlatformController>();

        const auto resources =
                core::Controller::get<
                    resources::ResourcesController>();

        m_shader =
                resources->shader("post_processing");

        m_width  = platform->window()->width();
        m_height = platform->window()->height();

        m_framebuffer =
                OpenGL::create_framebuffer(
                    m_width,
                    m_height);

        m_screen_quad =
                OpenGL::create_screen_quad();
    }

    void PostProcessingController::begin_draw() {
        const auto platform =
                core::Controller::get<
                    platform::PlatformController>();

        const int width =
                platform->window()->width();

        const int height =
                platform->window()->height();

        if (width != m_width || height != m_height) {
            resize_framebuffer(
                width,
                height);
        }

        OpenGL::bind_framebuffer(
            m_framebuffer.framebuffer);

        OpenGL::enable_depth_testing();
        OpenGL::clear_buffers();
    }

    void PostProcessingController::draw() {
        OpenGL::bind_framebuffer(0);

        OpenGL::disable_depth_testing();
        OpenGL::clear_buffers();

        m_shader->use();

        m_shader->set_int(
            "screen_texture",
            0);

        m_shader->set_int(
            "effect",
            static_cast<int>(m_effect));

        OpenGL::draw_screen_quad(
            m_screen_quad,
            m_framebuffer.color_texture);

        OpenGL::enable_depth_testing();
    }

    void PostProcessingController::resize_framebuffer(
        int width,
        int height) {
        if (width <= 0 || height <= 0) {
            return;
        }

        OpenGL::destroy_framebuffer(
            m_framebuffer);

        m_framebuffer =
                OpenGL::create_framebuffer(
                    width,
                    height);

        m_width  = width;
        m_height = height;
    }

    void PostProcessingController::terminate() {
        OpenGL::destroy_screen_quad(
            m_screen_quad);

        OpenGL::destroy_framebuffer(
            m_framebuffer);
    }
} // namespace engine::graphics
