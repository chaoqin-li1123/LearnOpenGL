#ifndef TEXTURE_H
#define TEXTURE_H
#include "gl_util.h"

struct Texture {
  Texture(const char* src) { texture_id_ = loadDDS(src); }
  void bind(GLuint program_id, const char* texture_sampler_name) {
    glCreateSamplers(1, &sampler_id_);
    glBindSampler(0, sampler_id_);
    glBindTextureUnit(0, texture_id_);
    setSamplerParameter();
  }
  ~Texture() { glDeleteTextures(1, &texture_id_); }

 private:
  void setSamplerParameter() {
    glSamplerParameteri(sampler_id_, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_NEAREST);
    glSamplerParameteri(sampler_id_, GL_TEXTURE_MAG_FILTER,
                        GL_LINEAR_MIPMAP_NEAREST);
    glSamplerParameteri(sampler_id_, GL_TEXTURE_WRAP_S, GL_REPEAT);
  }
  GLuint texture_id_;
  GLuint sampler_id_;
};

#endif