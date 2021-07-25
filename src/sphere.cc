#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cstdlib>

double rand_double() { return (double)rand() / RAND_MAX; }
double angle = 0.0;
constexpr GLuint SET_MATERIAL = 1;

void rotateLight() {
  glPushMatrix();
  GLfloat light_pos[4]{1.0, 1.0, 1.0, 0.0};
  glRotated(angle, 0, 0, 1.0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glPopMatrix();
  angle += 1.0;
}

void initProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, 1.0, 2.0, -3.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void setMaterial() {
  glNewList(SET_MATERIAL, GL_COMPILE);
  GLfloat material_specular[4]{};
  for (int i = 0; i < 4; i++) {
    material_specular[i] = rand_double();
  }
  GLfloat material_shininess[1]{50.0};
  glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
  glEndList();
}

void init() {
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  setMaterial();
  initProjection();
}

void display() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  rotateLight();
  glCallList(SET_MATERIAL);
  glutSolidSphere(1.0, 20, 15);
  glFlush();
}

void mouse(int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN) {
        glutIdleFunc(display);
      }
      break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN) {
        glutIdleFunc(display);
      }
      break;
    default:
      break;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("spheres");
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMainLoop();
}