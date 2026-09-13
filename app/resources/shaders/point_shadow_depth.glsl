//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 FragPos;

uniform mat4 model;
uniform mat4 shadow_matrix;

void main() {
    FragPos =
    vec3(
    model
    * vec4(aPos, 1.0));

    gl_Position =
    shadow_matrix
    * vec4(FragPos, 1.0);
}

//#shader fragment
#version 330 core

in vec3 FragPos;

uniform vec3 light_position;
uniform float far_plane;

void main() {
    float light_distance =
    length(
        FragPos
        - light_position);

    light_distance /=
    far_plane;

    gl_FragDepth =
    light_distance;
}