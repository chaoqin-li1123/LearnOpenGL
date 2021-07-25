#include "gl_util.hpp"

GLuint program_id;
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
      loadShaders("shaders/color_cube.vert", "shaders/color_cube.frag");
  glUseProgram(program_id);
}

void initVertexBuffer() {
  vertex_number = 36;
  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glVertexAttribPointer(0,         // attribute 0.
                        3,         // size
                        GL_FLOAT,  // type
                        GL_FALSE,  // normalized?
                        0,         // stride
                        (void *)0  // array buffer offset
  );
}

void initColorBuffer() {
  static GLfloat g_color_buffer_data[3 * 36] = {};
  for (int v = 0; v < 12 * 3; v++) {
    g_color_buffer_data[3 * v + 0] =
        (g_vertex_buffer_data[3 * v + 0] + 1.0) / 2.0;
    g_color_buffer_data[3 * v + 1] =
        (g_vertex_buffer_data[3 * v + 1] + 1.0) / 2.0;
    g_color_buffer_data[3 * v + 2] =
        (g_vertex_buffer_data[3 * v + 2] + 1.0) / 2.0;
  }
  GLuint color_buffer;
  glGenBuffers(1, &color_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
               g_color_buffer_data, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,         // attribute 1.
                        3,         // size
                        GL_FLOAT,  // type
                        GL_FALSE,  // normalized?
                        0,         // stride
                        (void *)0  // array buffer offset
  );
}

void initTransformation() {
  glm::vec3 look_from = glm::vec3(4.0f, 4.0f, 3.0f);
  glm::vec3 look_at = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 view = glm::lookAt(look_from, look_at, up);

  float fov = 50.0f;
  float aspect_ratio = 4.0f / 3.0f;
  float near_z = 1.0f, far_z = 100.0f;
  glm::mat4 projection =
      glm::perspective(glm::radians(fov), aspect_ratio, near_z, far_z);

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

int main(int argc, char **argv) {
  GLFWwindow *window = initWindow();
  initDepth();
  initShaders();
  initVertexArray();
  initVertexBuffer();
  initColorBuffer();
  initTransformation();

  do {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    display();

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  }  // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);
  glfwTerminate();
  return 0;
}