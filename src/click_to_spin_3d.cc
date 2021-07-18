#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int w = 900, h = 900;
constexpr int w_cnt = 3, h_cnt = 3;
double direction = 1.0;

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0, 1.0, 1.0);
  glShadeModel(GL_SMOOTH);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-5.0, 5.0, -5.0, 5.0, 1.5, 20.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-5.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  for (int i = 0; i < w_cnt; i++) {
    for (int j = 0; j < h_cnt; j++) {
      int w_interval = w / w_cnt, h_interval = h / h_cnt;
      glViewport(i * w_interval, j * h_interval, w_interval, h_interval);
      glRotatef(direction * 35.0, 0.0, 1.0, 0.0);
      glutWireTeapot(3.0);
    }
  }
  glutSwapBuffers();
}

void leftSpin() {
  direction = 1.0;
  glColor3f(1.0, 0.0, 0.0);
  glRotatef(20.0, 0.0, 1.0, 0.0);
  glutPostRedisplay();
}

void rightSpin() {
  direction = -1.0;
  glColor3f(0.0, 1.0, 0.0);
  glRotatef(-20.0, 0.0, 1.0, 0.0);
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) {
        glutIdleFunc(leftSpin);
      }
      break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN) {
        glutIdleFunc(rightSpin);
      }
      break;
    default:
      break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(w, h);
  glutInitWindowPosition(200, 200);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}