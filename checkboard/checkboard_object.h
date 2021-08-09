#ifndef CHECKBOARD_H
#define CHECKBOARD_H
#include "util/object.h"

struct CheckboardObject : public Object {
  CheckboardObject() {
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
  void bind(GLuint program_id) override {
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
  void unbind() override { glDisableVertexAttribArray(0); }
  void display() override { glDrawArrays(GL_TRIANGLES, 0, vertices_.size()); }
  ~CheckboardObject() override {
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteVertexArrays(1, &vertex_array_id_);
  }

 private:
  void initVAO() {
    glCreateVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);
  }

  void initVBO() {
    glCreateBuffers(1, &vertex_buffer_);
    glNamedBufferStorage(vertex_buffer_, vertices_.size() * sizeof(glm::vec3),
                         &vertices_[0], GL_MAP_READ_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
  }
  std::vector<glm::vec3> vertices_;
  GLuint vertex_buffer_;
  GLuint vertex_array_id_;
};

#endif