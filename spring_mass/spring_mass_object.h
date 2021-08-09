#ifndef SPRING_MASS_H
#define SPRING_MASS_H

#include "util/gl_util.h"
#include "util/object.h"

struct SpringMassObject : public Object {
  SpringMassObject() {}
  void bind(GLuint program_id) override {}
  void unbind() override {}
  void display() override {}
  ~SpringMassObject() override {}
};

#endif