#ifndef TEXTURE_H
#define TEXTURE_H
#include "gl_util.h"

struct Texture {
  Texture(const char* src) { id_ = loadDDS(src); }
  void bind(GLuint program_id, const char* texture_sampler_name) {
    GLuint texture_sampler_id =
        glGetUniformLocation(program_id, "texture_sampler");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id_);
    glUniform1i(texture_sampler_id, 0);
  }
  ~Texture() { glDeleteTextures(1, &id_); }

 private:
  GLuint id_;
};

#endif