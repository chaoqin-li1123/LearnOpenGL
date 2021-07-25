#include "gl_util.hpp"

GLuint program_id;
GLuint texture_id;
GLuint vertex_buffer, uv_buffer;
int vertex_number;
GLuint vertex_array_id;

static constexpr GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f,
    -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,
    -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f,
    1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,
    1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f,
    1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f};

#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
void makeCheckImage(void) {
  int i, j, c;
  for (i = 0; i < checkImageHeight; i++) {
    for (j = 0; j < checkImageWidth; j++) {
      c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
      checkImage[i][j][0] = (GLubyte)c;
      checkImage[i][j][1] = (GLubyte)c;
      checkImage[i][j][2] = (GLubyte)c;
      checkImage[i][j][3] = (GLubyte)255;
    }
  }
}

void initDepth() {
  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);
}

void initVertexArray() {
  glGenVertexArrays(1, &vertex_array_id);
  glBindVertexArray(vertex_array_id);
}

void initShaders() {
  program_id =
      loadShaders("shaders/texture_cube.vert", "shaders/texture_cube.frag");
  glUseProgram(program_id);
}

void initVertexBuffer() {
  vertex_number = 36;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,         // attribute 0.
                        3,         // size
                        GL_FLOAT,  // type
                        GL_FALSE,  // normalized?
                        0,         // stride
                        (void *)0  // array buffer offset
  );
}

void initUVBuffer() {
  static GLfloat g_uv_buffer_data[2 * 36] = {
      0.000059f, 1.0f - 0.000004f, 0.000103f, 1.0f - 0.336048f,
      0.335973f, 1.0f - 0.335903f, 1.000023f, 1.0f - 0.000013f,
      0.667979f, 1.0f - 0.335851f, 0.999958f, 1.0f - 0.336064f,
      0.667979f, 1.0f - 0.335851f, 0.336024f, 1.0f - 0.671877f,
      0.667969f, 1.0f - 0.671889f, 1.000023f, 1.0f - 0.000013f,
      0.668104f, 1.0f - 0.000013f, 0.667979f, 1.0f - 0.335851f,
      0.000059f, 1.0f - 0.000004f, 0.335973f, 1.0f - 0.335903f,
      0.336098f, 1.0f - 0.000071f, 0.667979f, 1.0f - 0.335851f,
      0.335973f, 1.0f - 0.335903f, 0.336024f, 1.0f - 0.671877f,
      1.000004f, 1.0f - 0.671847f, 0.999958f, 1.0f - 0.336064f,
      0.667979f, 1.0f - 0.335851f, 0.668104f, 1.0f - 0.000013f,
      0.335973f, 1.0f - 0.335903f, 0.667979f, 1.0f - 0.335851f,
      0.335973f, 1.0f - 0.335903f, 0.668104f, 1.0f - 0.000013f,
      0.336098f, 1.0f - 0.000071f, 0.000103f, 1.0f - 0.336048f,
      0.000004f, 1.0f - 0.671870f, 0.336024f, 1.0f - 0.671877f,
      0.000103f, 1.0f - 0.336048f, 0.336024f, 1.0f - 0.671877f,
      0.335973f, 1.0f - 0.335903f, 0.667969f, 1.0f - 0.671889f,
      1.000004f, 1.0f - 0.671847f, 0.667979f, 1.0f - 0.335851f};
  glGenBuffers(1, &uv_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,         // attribute 1.
                        2,         // size
                        GL_FLOAT,  // type
                        GL_FALSE,  // normalized?
                        0,         // stride
                        (void *)0  // array buffer offset
  );
}

void initTexture() {
  makeCheckImage();
  glGenTextures(1, &texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void initTransformation() {
  glm::vec3 look_from = glm::vec3(4.0f, 4.0f, 3.0f);
  glm::vec3 look_at = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 view = glm::lookAt(look_from, look_at, up);

  float field_of_view = 50.0f;
  float aspect_ratio = 4.0f / 3.0f;
  float near_z = 1.0f, far_z = 100.0f;
  glm::mat4 projection = glm::perspective(glm::radians(field_of_view),
                                          aspect_ratio, near_z, far_z);

  glm::mat4 view_projection = projection * view;

  glm::mat4 model = glm::mat4(1.0f);

  glm::mat4 mvp = view_projection * model;

  GLuint matrix_id = glGetUniformLocation(program_id, "MVP");

  glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);
}

void display() { glDrawArrays(GL_TRIANGLES, 0, vertex_number); }

GLFWwindow *initWindow() {
  glewExperimental = true;  // Needed for core profile
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    exit(-1);
  }
  glfwWindowHint(GLFW_SAMPLES, 4);                // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE);  // We don't want the old OpenGL

  // Open a window and create its OpenGL context
  GLFWwindow *window = glfwCreateWindow(1024, 768, "Artist", NULL, NULL);

  glfwMakeContextCurrent(window);  // Initialize GLEW
  glewExperimental = true;         // Needed in core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    exit(-1);
  }
  return window;
}

void cleanup() {
  glDeleteBuffers(1, &vertex_buffer);
  glDeleteBuffers(1, &uv_buffer);
  glDeleteTextures(1, &texture_id);
  glDeleteProgram(program_id);
  glDeleteVertexArrays(1, &vertex_array_id);
  glfwTerminate();
}

int main(int argc, char **argv) {
  GLFWwindow *window = initWindow();
  initDepth();
  initShaders();
  initVertexArray();
  initVertexBuffer();
  initTexture();
  initUVBuffer();

  do {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    initTransformation();
    display();

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);
  cleanup();
  return 0;
}