#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Pos;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vec3 pos = (model * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    Normal = normalize((model * vec4(aNormal, 1.0)).xyz - pos);
    Pos = (model * vec4(aPos, 1.0)).xyz;
}
