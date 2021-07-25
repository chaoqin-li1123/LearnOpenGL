#version 330 core
layout(location = 0) in vec3 vertex_position_model_space;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal_model_space;

out vec3 vertex_position_camera_space;
// Texture coordinate.
out vec2 uv;
out vec3 normal_camera_space;


uniform mat4 model_view;
uniform mat4 projection;
uniform mat4 MVP;

void main(){  
    // Position of the vertex in camera space.
    vertex_position_camera_space =  (model_view * vec4(vertex_position_model_space,1.0)).xyz;
    // uv of the vertex.
    uv = vertex_uv;
    // Normal vector of the vertex in camera space.
    normal_camera_space = normalize((model_view * vec4(vertex_normal_model_space, 0.0)).xyz);

    gl_Position = MVP * vec4(vertex_position_model_space, 1.0);
}