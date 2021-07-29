#ifndef SHADER_H
#define SHADER_H
#include <algorithm>
#include <memory>

#include "gl_util.h"
#include "light.h"
#include "object.h"
#include "program.h"
#include "texture.h"

struct Shader {
  Shader(const char* vertex_shader, const char* fragment_shader,
         const char* object_file, const char* texture_file)
      : program_(vertex_shader, fragment_shader),
        object_(object_file),
        texture_(texture_file) {
    initTransformation();
  }

  // Initialize the model, view and projection matrix.
  void initTransformation() {
    model_ = glm::mat4(1.0f);
    // TODO: allow user to change view using the mouse or keyboard.
    glm::vec3 look_from = glm::vec3(1.5f, 1.5f, 1.5f);
    glm::vec3 look_at = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    view_ = glm::lookAt(look_from, look_at, up);

    model_view_ = view_ * model_;

    float field_of_view = 50.0f;
    float aspect_ratio = 4.0f / 3.0f;
    float near_z = 0.01f, far_z = 100.0f;
    projection_ = glm::perspective(glm::radians(field_of_view), aspect_ratio,
                                   near_z, far_z);

    MVP_ = projection_ * model_view_;
  }

  void bindTransformation() {
    GLuint model_view_matrix_id =
        glGetUniformLocation(program_.id(), "model_view");

    glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, &model_view_[0][0]);
    GLuint projection_matrix_id =
        glGetUniformLocation(program_.id(), "projection");
    glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, &projection_[0][0]);

    GLuint MVP_matrix_id = glGetUniformLocation(program_.id(), "MVP");
    glUniformMatrix4fv(MVP_matrix_id, 1, GL_FALSE, &MVP_[0][0]);
  }

  void bindLight(glm::vec3 light_position_world_space, glm::vec3 color) {
    light_ = std::make_unique<Light>(light_position_world_space, color);
    light_->bind(program_.id(), view_);
  }

  void display() {
    program_.bind();
    texture_.bind(program_.id(), "texture_sampler");
    bindTransformation();
    bindLight(glm::vec3(5.0, 4.0, 6.0), glm::vec3(1.0, 1.0, 1.0));
    object_.bind(program_.id());
    object_.display();
    // clean up the vertex array attributes.
    object_.unbind();
  }

 private:
  Program program_;
  Object object_;
  Texture texture_;
  std::unique_ptr<Light> light_;

  glm::mat4 model_;
  glm::mat4 model_view_;
  glm::mat4 view_;
  glm::mat4 projection_;
  glm::mat4 MVP_;
};

struct CheckBoardShader {
  CheckBoardShader()
      : program_("blinn_phong/checkboard.vs", "blinn_phong/checkboard.fs") {
    float x1 = -0.9, x2 = 0.9, y1 = -0.9, y2 = 0.9;

    vertices_.emplace_back(x2, y1, -1.0);
    vertices_.emplace_back(x1, y2, -1.0);
    vertices_.emplace_back(x1, y1, -1.0);

    vertices_.emplace_back(x2, y1, -1.0);
    vertices_.emplace_back(x2, y2, -1.0);
    vertices_.emplace_back(x1, y2, -1.0);

    initVAO();
    initVBO();
  }

  void initVAO() {
    glGenVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);
  }

  void initVBO() {
    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3),
                 &vertices_[0], GL_STATIC_DRAW);
  }

  void bind(GLuint program_id) {
    // Bind vertices buffer.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glVertexAttribPointer(0,         // attribute 0.
                          3,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void*)0   // array buffer offset
    );
  }

  void unbind() { glDisableVertexAttribArray(0); }

  void display() {
    program_.bind();
    bind(program_.id());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawArrays(GL_TRIANGLES, 0, vertices_.size());
    glDisable(GL_BLEND);
    unbind();
  }

  ~CheckBoardShader() {
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteVertexArrays(1, &vertex_array_id_);
  }

 private:
  Program program_;
  std::vector<glm::vec3> vertices_;
  GLuint vertex_buffer_;
  GLuint vertex_array_id_;
};

#endif