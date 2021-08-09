#version 450 core

layout (location = 0) in vec4 position_mass;

layout (location = 1) in vec3 velocity;

layout (location = 2) in ivec4 connection;

void main() {
    gl_Position = vec4(position_mass.xyz, 1.0);
}