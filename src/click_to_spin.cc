#include <GL/glut.h>

constexpr int INIT_WIDTH = 400;
constexpr int INIT_HEIGHT = 400;
int cur_w, cur_h;

void setViewportAndOrtho() {
    glViewport(0, 0, cur_w, cur_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D(-0.5* cur_w, 0.5*cur_w, -0.5*cur_h, 0.5*cur_h);   
}

void init() {
    cur_w = INIT_WIDTH, cur_h = INIT_HEIGHT;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    setViewportAndOrtho();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(-0.25*cur_w, -0.25*cur_h, 0.25*cur_w, 0.25*cur_h);
    glFlush();
}


void reshape(int w, int h) {
    cur_w = w, cur_h = h;
    setViewportAndOrtho();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                glColor3f(1.0, 0.0, 0.0);
                glRotatef(60.0, 0.0, 0.0, 1.0);
                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                glColor3f(0.0, 1.0, 0.0);
                glRotatef(-60.0, 0.0, 0.0, 1.0);
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(INIT_WIDTH, INIT_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ming");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}