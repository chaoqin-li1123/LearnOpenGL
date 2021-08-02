#version 450 core
layout(location = 0) in vec3 vertex_position_model_space;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal_model_space;


out VS_OUT {
    out vec3 vertex_position_camera_space;
    out vec2 uv; // Texture coordinate.
    out vec3 normal_camera_space;
} vs_out;

out float view_distance;

uniform mat4 model_view;
uniform mat4 projection;
uniform mat4 MVP;

void main(){  
    // Position of the vertex in camera space.
    vs_out.vertex_position_camera_space =  (model_view * vec4(vertex_position_model_space,1.0)).xyz;
    // uv of the vertex.
    vs_out.uv = vertex_uv;
    // Normal vector of the vertex in camera space.
    vs_out.normal_camera_space = normalize((transpose(inverse(model_view)) * vec4(vertex_normal_model_space, 0.0)).xyz);

    gl_Position = MVP * vec4(vertex_position_model_space, 1.0);

    view_distance = length(vs_out.vertex_position_camera_space);
}