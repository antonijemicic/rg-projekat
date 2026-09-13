//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(
    model * vec4(aPos, 1.0));

    Normal =
    mat3(transpose(inverse(model)))
    * aNormal;

    gl_Position =
    projection
    * view
    * vec4(FragPos, 1.0);
}

//#shader fragment
#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 point_light_position;
uniform vec3 point_light_color;

uniform vec3 spot_light_position;
uniform vec3 spot_light_direction;
uniform vec3 spot_light_color;

uniform vec3 view_position;
uniform vec3 object_color;

uniform samplerCube point_shadow_map;
uniform float point_shadow_far_plane;
uniform bool point_shadows_enabled;

vec3 sample_offsets[20] = vec3[](
vec3(1.0, 1.0, 1.0),
vec3(1.0, -1.0, 1.0),
vec3(-1.0, -1.0, 1.0),
vec3(-1.0, 1.0, 1.0),

vec3(1.0, 1.0, -1.0),
vec3(1.0, -1.0, -1.0),
vec3(-1.0, -1.0, -1.0),
vec3(-1.0, 1.0, -1.0),

vec3(1.0, 1.0, 0.0),
vec3(1.0, -1.0, 0.0),
vec3(-1.0, -1.0, 0.0),
vec3(-1.0, 1.0, 0.0),

vec3(1.0, 0.0, 1.0),
vec3(-1.0, 0.0, 1.0),
vec3(1.0, 0.0, -1.0),
vec3(-1.0, 0.0, -1.0),

vec3(0.0, 1.0, 1.0),
vec3(0.0, -1.0, 1.0),
vec3(0.0, -1.0, -1.0),
vec3(0.0, 1.0, -1.0)
);

float calculate_point_shadow(
    vec3 frag_position,
    vec3 normal) {

    if (!point_shadows_enabled) {
        return 0.0;
    }

    vec3 frag_to_light =
    frag_position
    - point_light_position;

    float current_depth =
    length(frag_to_light);

    if (current_depth >= point_shadow_far_plane) {
        return 0.0;
    }

    vec3 light_direction =
    normalize(
        point_light_position
        - frag_position);

    float bias =
    max(
        0.08
        * (1.0
        - dot(normal, light_direction)),
        0.02);

    float view_distance =
    length(
        view_position
        - frag_position);

    float disk_radius =
    (1.0
    + view_distance
    / point_shadow_far_plane)
    / 25.0;

    float shadow = 0.0;

    for (int i = 0; i < 20; ++i) {
        float closest_depth =
        texture(
            point_shadow_map,
            frag_to_light
            + sample_offsets[i]
            * disk_radius)
        .r;

        closest_depth *=
        point_shadow_far_plane;

        if (current_depth - bias
        > closest_depth) {
            shadow += 1.0;
        }
    }

    shadow /= 20.0;

    return shadow;
}

void main() {
    vec3 normal =
    normalize(Normal);

    // POINT LIGHT

    vec3 point_direction =
    normalize(
        point_light_position
        - FragPos);

    float point_diffuse =
    max(
        dot(
            normal,
            point_direction),
        0.0);

    float point_distance =
    length(
        point_light_position
        - FragPos);

    float point_attenuation =
    1.0
    / (1.0
    + 0.045 * point_distance
    + 0.0075
    * point_distance
    * point_distance);

    float point_shadow =
    calculate_point_shadow(
        FragPos,
        normal);

    vec3 point_result =
    (1.0 - point_shadow)
    * point_diffuse
    * point_attenuation
    * point_light_color
    * 2.0;

    // SPOT LIGHT

    vec3 spot_direction =
    normalize(
        spot_light_position
        - FragPos);

    float theta =
    dot(
        spot_direction,
        normalize(
            -spot_light_direction));

    float inner_cutoff =
    cos(radians(12.5));

    float outer_cutoff =
    cos(radians(17.5));

    float epsilon =
    inner_cutoff
    - outer_cutoff;

    float spot_intensity =
    clamp(
        (theta - outer_cutoff)
        / epsilon,
        0.0,
        1.0);

    float spot_diffuse =
    max(
        dot(
            normal,
            spot_direction),
        0.0);

    float spot_distance =
    length(
        spot_light_position
        - FragPos);

    float spot_attenuation =
    1.0
    / (1.0
    + 0.045 * spot_distance
    + 0.0075
    * spot_distance
    * spot_distance);

    vec3 spot_result =
    spot_diffuse
    * spot_intensity
    * spot_attenuation
    * spot_light_color
    * 1.5;

    vec3 ambient =
    0.30
    * object_color;

    vec3 result =
    ambient
    + (point_result
    + spot_result)
    * object_color;

    FragColor =
    vec4(result, 1.0);
}