#ifndef PROGRAM_H
#define PROGRAM_H
#include "gl_util.h"

struct Program {
  Program(std::vector<const char*> shader_files,
          std::vector<GLenum> shader_types) {
    std::vector<GLuint> shader_ids;
    for (size_t i = 0; i < shader_files.size(); i++) {
      shader_ids.push_back(loadShader(shader_files[i], shader_types[i]));
    }
    program_id_ = glCreateProgram();
    for (GLuint shader_id : shader_ids) {
      glAttachShader(program_id_, shader_id);
    }
    linkProgram();

    for (GLuint shader_id : shader_ids) {
      glDetachShader(program_id_, shader_id);
    }

    for (GLuint shader_id : shader_ids) {
      glDeleteShader(shader_id);
    }
    glPatchParameteri(GL_PATCH_VERTICES, 3);
  }

  GLuint id() { return program_id_; }
  ~Program() { glDeleteProgram(program_id_); }
  void bind() { glUseProgram(program_id_); }

 private:
  GLuint loadShader(const char* shader_file, GLenum shader_type) {
    printf("Loading shader : %s\n", shader_file);
    GLuint shader_id = glCreateShader(shader_type);
    std::string shader_source_str = readFile(shader_file);
    const char* shader_source_cstr = shader_source_str.c_str();
    glShaderSource(shader_id, 1, &shader_source_cstr, NULL);
    compileShader(shader_id);
    return shader_id;
  }

  void compileShader(GLuint shader_id) {
    glCompileShader(shader_id);
    // Error handling.
    GLint result = GL_FALSE;
    int error_info_length;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &error_info_length);
    if (error_info_length > 0) {
      std::string error_msg(error_info_length + 1, '\0');
      glGetShaderInfoLog(shader_id, error_info_length, NULL, &error_msg[0]);
      printf("%s\n", &error_msg[0]);
      exit(-1);
    }
    if (result != GL_TRUE) exit(-1);
  }

  void linkProgram() {
    glLinkProgram(program_id_);
    GLint result = GL_FALSE;
    int error_info_length;
    glGetProgramiv(program_id_, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &error_info_length);
    if (error_info_length > 0) {
      std::string error_msg(error_info_length + 1, '\0');
      glGetProgramInfoLog(program_id_, error_info_length, NULL, &error_msg[0]);
      printf("%s\n", &error_msg[0]);
    }
    if (result != GL_TRUE) exit(-1);
  }

  GLuint program_id_;
};

#endif