// clang-format off
#include <glad/glad.h>
// clang-format on

#include <engine/graphics/OpenGL.hpp>
#include <engine/util/Errors.hpp>

namespace engine::graphics {
    OpenGL::PointShadowData OpenGL::create_point_shadow_map(
        int32_t size) {
        PointShadowData shadow{};

        CHECKED_GL_CALL(
            glGenFramebuffers,
            1,
            &shadow.framebuffer);

        CHECKED_GL_CALL(
            glGenTextures,
            1,
            &shadow.depth_cubemap);

        CHECKED_GL_CALL(
            glBindTexture,
            GL_TEXTURE_CUBE_MAP,
            shadow.depth_cubemap);

        for (int32_t face = 0; face < 6; ++face) {
            CHECKED_GL_CALL(
                glTexImage2D,
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
                0,
                GL_DEPTH_COMPONENT,
                size,
                size,
                0,
                GL_DEPTH_COMPONENT,
                GL_FLOAT,
                nullptr);
        }

        CHECKED_GL_CALL(
            glTexParameteri,
            GL_TEXTURE_CUBE_MAP,
            GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);

        CHECKED_GL_CALL(
            glTexParameteri,
            GL_TEXTURE_CUBE_MAP,
            GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);

        CHECKED_GL_CALL(
            glTexParameteri,
            GL_TEXTURE_CUBE_MAP,
            GL_TEXTURE_WRAP_S,
            GL_CLAMP_TO_EDGE);

        CHECKED_GL_CALL(
            glTexParameteri,
            GL_TEXTURE_CUBE_MAP,
            GL_TEXTURE_WRAP_T,
            GL_CLAMP_TO_EDGE);

        CHECKED_GL_CALL(
            glTexParameteri,
            GL_TEXTURE_CUBE_MAP,
            GL_TEXTURE_WRAP_R,
            GL_CLAMP_TO_EDGE);

        CHECKED_GL_CALL(
            glBindFramebuffer,
            GL_FRAMEBUFFER,
            shadow.framebuffer);

        CHECKED_GL_CALL(
            glFramebufferTexture2D,
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            shadow.depth_cubemap,
            0);

        CHECKED_GL_CALL(
            glDrawBuffer,
            GL_NONE);

        CHECKED_GL_CALL(
            glReadBuffer,
            GL_NONE);

        const auto status =
                CHECKED_GL_CALL(
                    glCheckFramebufferStatus,
                    GL_FRAMEBUFFER);

        RG_GUARANTEE(
            status == GL_FRAMEBUFFER_COMPLETE,
            "Point shadow framebuffer is incomplete.");

        CHECKED_GL_CALL(
            glBindFramebuffer,
            GL_FRAMEBUFFER,
            0);

        return shadow;
    }

    void OpenGL::bind_point_shadow_face(
        const PointShadowData &shadow,
        int32_t face) {
        CHECKED_GL_CALL(
            glBindFramebuffer,
            GL_FRAMEBUFFER,
            shadow.framebuffer);

        CHECKED_GL_CALL(
            glFramebufferTexture2D,
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
            shadow.depth_cubemap,
            0);
    }

    void OpenGL::bind_cubemap_texture(
        uint32_t texture_unit,
        uint32_t texture_id) {
        CHECKED_GL_CALL(
            glActiveTexture,
            GL_TEXTURE0 + texture_unit);

        CHECKED_GL_CALL(
            glBindTexture,
            GL_TEXTURE_CUBE_MAP,
            texture_id);
    }

    void OpenGL::destroy_point_shadow_map(
        const PointShadowData &shadow) {
        CHECKED_GL_CALL(
            glDeleteTextures,
            1,
            &shadow.depth_cubemap);

        CHECKED_GL_CALL(
            glDeleteFramebuffers,
            1,
            &shadow.framebuffer);
    }

    void OpenGL::clear_depth_buffer() {
        CHECKED_GL_CALL(
            glClear,
            GL_DEPTH_BUFFER_BIT);
    }

    void OpenGL::set_viewport(
        int32_t width,
        int32_t height) {
        CHECKED_GL_CALL(
            glViewport,
            0,
            0,
            width,
            height);
    }
} // namespace engine::graphics
