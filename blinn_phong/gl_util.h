#ifndef GL_UTIL_H
#define GL_UTIL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <glm/ext.hpp>
#include <iostream>
#include <sstream>
#include <vector>

GLuint loadShaders(const char *vertex_file_path,
                   const char *fragment_file_path);

bool loadOBJ(const char *path, std::vector<glm::vec3> &out_vertices,
             std::vector<glm::vec2> &out_uvs,
             std::vector<glm::vec3> &out_normals);

#define FOURCC_DXT1 0x31545844  // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844  // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844  // Equivalent to "DXT5" in ASCII

GLuint loadDDS(const char *imagepath);

#endif