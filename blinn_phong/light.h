#ifndef LIGHT_H
#define LIGHT_H
#include "gl_util.h"

struct Light {
  Light(glm::vec3 position_world_space, glm::vec3 color)
      : position_world_space_(position_world_space), color_(color) {}
  void bind(GLuint program_id_, glm::mat4 const& view) {
    position_camera_space_ = view * glm::vec4(position_world_space_, 1.0);
    GLuint light_position_id =
        glGetUniformLocation(program_id_, "light_position_camera_space");
    glUniform3f(light_position_id, position_camera_space_.x,
                position_camera_space_.y, position_camera_space_.z);
    GLuint light_color_id = glGetUniformLocation(program_id_, "light_color");
    glUniform3f(light_color_id, color_.x, color_.y, color_.z);
  }

 private:
  glm::vec4 position_camera_space_;
  glm::vec3 position_world_space_;
  glm::vec3 color_;
};
#endif