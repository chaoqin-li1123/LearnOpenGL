#ifndef OBJECT_H
#define OBJECT_H
#include <algorithm>
#include <cstddef>

#include "gl_util.h"

static inline bool eq(float x1, float x2) { return std::abs(x1 - x2) < 1e-5; }

struct Object {
  Object(const char *obj) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    loadOBJ(obj, vertices, uvs, normals);
    indexVBO(vertices, uvs, normals);
  }

  void init() {
    initVAO();
    initVBO();
  }

  void indexVBO(std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs,
                std::vector<glm::vec3> &normals) {
    for (unsigned int i = 0; i < vertices.size(); i++) {
      unsigned int j = 0;
      for (; j < indexed_vertices_.size(); j++) {
        bool match = eq(indexed_vertices_[j].x, vertices[i].x) &&
                     eq(indexed_vertices_[j].y, vertices[i].y) &&
                     eq(indexed_vertices_[j].z, vertices[i].z) &&
                     eq(indexed_uvs_[j].x, uvs[i].x) &&
                     eq(indexed_uvs_[j].y, uvs[i].y) &&
                     eq(indexed_normals_[j].x, normals[i].x) &&
                     eq(indexed_normals_[j].y, normals[i].y) &&
                     eq(indexed_normals_[j].z, normals[i].z);
        if (match) break;
      }
      if (j != indexed_vertices_.size()) {
        indices.push_back(j);
      } else {
        indices.push_back(indexed_vertices_.size());
        indexed_vertices_.push_back(vertices[i]);
        indexed_uvs_.push_back(uvs[i]);
        indexed_normals_.push_back(normals[i]);
      }
    }
  }

  void initVAO() {
    glGenVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);
  }

  void initVBO() {
    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices_.size() * sizeof(glm::vec3),
                 &indexed_vertices_[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uv_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer_);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs_.size() * sizeof(glm::vec2),
                 &indexed_uvs_[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normal_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals_.size() * sizeof(glm::vec3),
                 &indexed_normals_[0], GL_STATIC_DRAW);

    glGenBuffers(1, &element_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(size_t),
                 &indices[0], GL_STATIC_DRAW);
  }

  void bind(GLuint program_id) {
    // Bind VAO.
    init();
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
  }

  void unbind() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
  }

  void display() {
    glDrawElements(GL_PATCHES,       // mode
                   indices.size(),   // count
                   GL_UNSIGNED_INT,  // type
                   (void *)0         // element array buffer offset
    );
  }

  ~Object() {
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteBuffers(1, &uv_buffer_);
    glDeleteBuffers(1, &normal_buffer_);
    glDeleteVertexArrays(1, &vertex_array_id_);
  }

 private:
  std::vector<glm::vec3> indexed_vertices_;
  std::vector<glm::vec2> indexed_uvs_;
  std::vector<glm::vec3> indexed_normals_;
  std::vector<unsigned int> indices;
  GLuint vertex_buffer_;
  GLuint normal_buffer_;
  GLuint uv_buffer_;
  GLuint element_buffer_;
  GLuint vertex_array_id_;
};

#endif