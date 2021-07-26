#ifndef PROGRAM_H
#define PROGRAM_H
#include "gl_util.h"

struct Program {
  Program(const char* vertex_shader, const char* fragment_shader) {
    program_id_ = loadShaders(vertex_shader, fragment_shader);
  }
  GLuint id() { return program_id_; }
  ~Program() { glDeleteProgram(program_id_); }
  void bind() { glUseProgram(program_id_); }

 private:
  GLuint program_id_;
};

#endif