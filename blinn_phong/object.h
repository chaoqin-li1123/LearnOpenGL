#ifndef OBJECT_H
#define OBJECT_H
#include <cstddef>

#include "gl_util.h"

struct Object {
  Object(const char *obj) {
    loadOBJ(obj, vertices_, uvs_, normals_);
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

    glGenBuffers(1, &uv_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_);
    glBufferData(GL_ARRAY_BUFFER, uvs_.size() * sizeof(glm::vec2), &uvs_[0],
                 GL_STATIC_DRAW);

    glGenBuffers(1, &normal_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
    glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3),
                 &normals_[0], GL_STATIC_DRAW);
  }

  void bind(GLuint program_id) {
    // Bind VAO.

    // Bind vertices buffer..
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glVertexAttribPointer(0,         // attribute 0.
                          3,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void *)0  // array buffer offset
    );
    // Bind uv(texture index) buffer.
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_);
    glVertexAttribPointer(1,         // attribute 1.
                          2,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void *)0  // array buffer offset
    );
    // Bind vertex normal buffer.
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
    glVertexAttribPointer(2,         // attribute 1.
                          3,         // size
                          GL_FLOAT,  // type
                          GL_FALSE,  // normalized?
                          0,         // stride
                          (void *)0  // array buffer offset
    );
  }

  void unbind() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
  }

  void display() { glDrawArrays(GL_TRIANGLES, 0, vertices_.size()); }

  ~Object() {
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteBuffers(1, &uv_buffer_);
    glDeleteBuffers(1, &normal_buffer_);
    glDeleteVertexArrays(1, &vertex_array_id_);
  }

 private:
  std::vector<glm::vec3> vertices_;
  std::vector<glm::vec2> uvs_;
  std::vector<glm::vec3> normals_;
  GLuint vertex_buffer_;
  GLuint normal_buffer_;
  GLuint uv_buffer_;
  GLuint vertex_array_id_;
};

#endif