//#shader vertex
#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex_coords;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vec4 world_position =
    model * vec4(a_position, 1.0);

    frag_position = world_position.xyz;

    frag_normal =
    mat3(transpose(inverse(model))) * a_normal;

    frag_tex_coords = a_tex_coords;

    gl_Position =
    projection * view * world_position;
}

//#shader fragment
#version 330 core

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 specular;
    float shininess;
};

in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_tex_coords;

out vec4 frag_color;

uniform vec3 view_position;

uniform DirectionalLight directional_light;
uniform PointLight point_light;
uniform Material material;

uniform sampler2D texture_diffuse1;

vec3 calculate_directional_light(
    vec3 normal,
    vec3 view_direction,
    vec3 texture_color
) {
    vec3 light_direction =
    normalize(-directional_light.direction);

    float diffuse_factor =
    max(dot(normal, light_direction), 0.0);

    vec3 reflection_direction =
    reflect(-light_direction, normal);

    float specular_factor =
    pow(
        max(
            dot(
                view_direction,
                reflection_direction
            ),
            0.0
        ),
        material.shininess
    );

    vec3 ambient =
    directional_light.ambient *
    texture_color;

    vec3 diffuse =
    directional_light.diffuse *
    diffuse_factor *
    texture_color;

    vec3 specular =
    directional_light.specular *
    specular_factor *
    material.specular;

    return ambient + diffuse + specular;
}

vec3 calculate_point_light(
    vec3 normal,
    vec3 view_direction,
    vec3 texture_color
) {
    vec3 light_direction =
    normalize(
        point_light.position -
        frag_position
    );

    float diffuse_factor =
    max(dot(normal, light_direction), 0.0);

    vec3 reflection_direction =
    reflect(-light_direction, normal);

    float specular_factor =
    pow(
        max(
            dot(
                view_direction,
                reflection_direction
            ),
            0.0
        ),
        material.shininess
    );

    float distance_to_light =
    length(
        point_light.position -
        frag_position
    );

    float attenuation =
    1.0 /
    (
    1.0 +
    0.09 * distance_to_light +
    0.032 *
    distance_to_light *
    distance_to_light
    );

    vec3 ambient =
    point_light.ambient *
    texture_color;

    vec3 diffuse =
    point_light.diffuse *
    diffuse_factor *
    texture_color;

    vec3 specular =
    point_light.specular *
    specular_factor *
    material.specular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

void main() {
    vec3 normal =
    normalize(frag_normal);

    vec3 view_direction =
    normalize(
        view_position -
        frag_position
    );

    vec3 texture_color =
    texture(
        texture_diffuse1,
        frag_tex_coords
    ).rgb;

    vec3 directional_result =
    calculate_directional_light(
        normal,
        view_direction,
        texture_color
    );

    vec3 point_result =
    calculate_point_light(
        normal,
        view_direction,
        texture_color
    );

    vec3 result =
    directional_result +
    point_result;

    frag_color =
    vec4(result, 1.0);
}