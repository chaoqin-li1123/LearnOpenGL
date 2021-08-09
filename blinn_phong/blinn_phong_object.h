#ifndef BLINN_PHONG_OBJECT_H
#define BLINN_PHONG_OBJECT_H
#include <algorithm>
#include <cstddef>
#include <map>

#include "util/object.h"

struct BlinnPhongObject : public Object {
  BlinnPhongObject(const char *obj) {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    loadOBJ(obj, positions, uvs, normals);
    indexVBO(positions, uvs, normals);
    // Bind VAO.
    init();
  }

  void bind(GLuint program_id) override {
    // Bind vertices buffer..
    glVertexArrayVertexBuffer(vertex_array_id_, 0, vertex_buffer_, 0,
                              sizeof(Vertex));
    glVertexArrayAttribFormat(vertex_array_id_,  // vao
                              0,                 // attribute 0.
                              3,                 // size
                              GL_FLOAT,          // type
                              GL_FALSE,          // normalized?
                              offsetof(Vertex,
                                       position_)  // array buffer offset
    );
    glVertexArrayAttribFormat(vertex_array_id_,  // vao
                              1,                 // attribute 1.
                              2,                 // size
                              GL_FLOAT,          // type
                              GL_FALSE,          // normalized?
                              offsetof(Vertex,
                                       uv_)  // array buffer offset
    );
    glVertexArrayAttribFormat(vertex_array_id_,  // vao
                              2,                 // attribute 1.
                              3,                 // size
                              GL_FLOAT,          // type
                              GL_FALSE,          // normalized?
                              offsetof(Vertex,
                                       normal_)  // array buffer offset
    );
    glVertexArrayAttribBinding(vertex_array_id_, 0, 0);
    glVertexArrayAttribBinding(vertex_array_id_, 1, 0);
    glVertexArrayAttribBinding(vertex_array_id_, 2, 0);
    glBindVertexBuffer(0, vertex_buffer_, 0, sizeof(Vertex));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
  }

  void unbind() override {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
  }

  void display() override {
    glDrawElementsInstanced(GL_PATCHES,       // mode
                            indices.size(),   // count
                            GL_UNSIGNED_INT,  // type
                            (void *)0,        // element array buffer offset
                            2                 // instance count
    );
  }

  ~BlinnPhongObject() override {
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteVertexArrays(1, &vertex_array_id_);
  }

 private:
  struct Vertex {
    Vertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
        : position_{position}, uv_{uv}, normal_{normal} {}
    bool operator<(const Vertex that) const {
      return memcmp((void *)this, (void *)&that, sizeof(Vertex)) > 0;
    };
    glm::vec3 position_;
    glm::vec2 uv_;
    glm::vec3 normal_;
  };

  void indexVBO(std::vector<glm::vec3> &positions, std::vector<glm::vec2> &uvs,
                std::vector<glm::vec3> &normals) {
    std::map<Vertex, GLuint> vertex_index;
    for (unsigned int i = 0; i < positions.size(); i++) {
      Vertex vertex{positions[i], uvs[i], normals[i]};
      auto it = vertex_index.find(vertex);
      if (it != vertex_index.end()) {
        indices.push_back(it->second);
      } else {
        vertex_index[vertex] = vertices_.size();
        indices.push_back(vertices_.size());
        vertices_.push_back(vertex);
      }
    }
  }

  void init() {
    initVAO();
    initVBO();
  }

  void initVAO() {
    glCreateVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);
  }

  void initVBO() {
    glCreateBuffers(1, &vertex_buffer_);
    glNamedBufferStorage(vertex_buffer_, vertices_.size() * sizeof(Vertex),
                         &vertices_[0], GL_MAP_READ_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);

    glCreateBuffers(1, &element_buffer_);
    glNamedBufferStorage(element_buffer_, indices.size() * sizeof(GLuint),
                         &indices[0], GL_MAP_READ_BIT);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
  }

  std::vector<Vertex> vertices_;
  std::vector<GLuint> indices;
  GLuint vertex_buffer_;
  GLuint element_buffer_;
  GLuint vertex_array_id_;
};

#endif