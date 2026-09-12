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
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0);
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

uniform vec3 object_color;

void main() {
    vec3 normal = normalize(Normal);

    // POINT LIGHT
    vec3 point_direction =
    normalize(point_light_position - FragPos);

    float point_diffuse =
    max(dot(normal, point_direction), 0.0);

    float point_distance =
    length(point_light_position - FragPos);

    float point_attenuation =
    1.0 / (1.0 + 0.09 * point_distance
    + 0.032 * point_distance * point_distance);

    vec3 point_result =
    point_diffuse * point_attenuation * point_light_color;

    // SPOT LIGHT
    vec3 spot_direction =
    normalize(spot_light_position - FragPos);

    float theta =
    dot(spot_direction, normalize(-spot_light_direction));

    float inner_cutoff = cos(radians(12.5));
    float outer_cutoff = cos(radians(17.5));

    float epsilon = inner_cutoff - outer_cutoff;

    float spot_intensity =
    clamp((theta - outer_cutoff) / epsilon, 0.0, 1.0);

    float spot_diffuse =
    max(dot(normal, spot_direction), 0.0);

    vec3 spot_result =
    spot_diffuse * spot_intensity * spot_light_color;

    vec3 ambient =
    0.10 * object_color;

    vec3 result =
    ambient
    + (point_result + spot_result) * object_color;

    FragColor = vec4(result, 1.0);
}