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
uniform vec3 object_color;

void main() {
    vec3 normal = normalize(Normal);

    vec3 light_direction =
    normalize(point_light_position - FragPos);

    float diffuse_strength =
    max(dot(normal, light_direction), 0.0);

    float distance =
    length(point_light_position - FragPos);

    float attenuation =
    1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);

    vec3 ambient =
    0.15 * point_light_color;

    vec3 diffuse =
    diffuse_strength * point_light_color;

    vec3 result =
    (ambient + diffuse * attenuation) * object_color;

    FragColor = vec4(result, 1.0);
}