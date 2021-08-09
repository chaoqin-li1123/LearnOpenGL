#ifndef OBJECT_H
#define OBJECT_H
#include <algorithm>
#include <cstddef>
#include <map>

#include "util/gl_util.h"

struct Object {
  virtual void bind(GLuint program_id) = 0;

  virtual void unbind() = 0;

  virtual void display() = 0;

  virtual ~Object() = default;
};

#endif