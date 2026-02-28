#version 330 core

uniform mat4 view;
uniform uint ch;

in vec3 normal;

out uvec4 color;

void main() {
    vec3 pos = (view * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    vec3 back = (view * vec4(normal, 1.0)).xyz;
    color = uvec4(max(dot(back - pos, vec3(0.0, 0.0, 1.0)), 0.0f) * vec3(1.0f, 1.0f, 1.0f) * 255.0f, ch);
}
