#version 330 core
// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
  
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
out vec3 fragment_color;
  
void main(){
  // Output position of the vertex, in clip space : MVP * position
  gl_Position =  MVP * vec4(vertex_position,1);
  fragment_color = vertex_color;
}