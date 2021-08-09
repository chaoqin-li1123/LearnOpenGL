#ifndef CHECK_BOARD_SHADER_H
#define CHECK_BOARD_SHADER_H

#include "checkboard_object.h"
#include "util/gl_util.h"
#include "util/program.h"

struct CheckboardShader {
  CheckboardShader()
      : program_({"checkboard/checkboard.vs", "checkboard/checkboard.fs"},
                 {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}) {}

  void display() {
    program_.bind();
    object_.bind(program_.id());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    object_.display();
    glDisable(GL_BLEND);
    object_.unbind();
  }

 private:
  Program program_;
  CheckboardObject object_;
};

#endif