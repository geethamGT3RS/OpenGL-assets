#include "fire.h"

#define PI 3.14159265358979323846

int mainWindow, simulationWindow;

float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
int lastMouseX = 0;
int lastMouseY = 0;

float cameraZ = 5.0f;
float cameraSpeed = 0.1f;

void keyboardHandler(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
    }
}
void specialKeyboardHandler(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: 
            cameraZ -= cameraSpeed;
            break;
        case GLUT_KEY_DOWN:
            cameraZ += cameraSpeed;
            break;
    }
    glutPostRedisplay();
}


void init() {

    GLfloat matAmbient[] = { 0.5f, 0.5f, 0.5f, 0.5f};
    GLfloat matDiffuse[] = {  0.5f, 0.5f, 0.5f, 0.5f};
    GLfloat matSpecular[] = { 0.5f, 0.5f, 0.5f, 0.5f};
    GLfloat matShininess[] = { 100.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat lightDiffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 0.0f, 5.0f, 1.0f };
    GLfloat lightPosition1[] = { 0.0f, 5.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void background(){
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);glVertex3f(-50.0f, -50.0f,-50.0f);       // Top-left vertex
            glColor3f(1.0f, 1.0f, 1.0f);glVertex3f(50.0f, -50.0f,-50.0f);        // Top-right vertex
            glColor3f(0.0f, 0.5f, 1.0f);glVertex3f(50.0f, 50.0f,-50.0f);         // Bottom-right vertex
            glColor3f(0.0f, 0.5f, 1.0f);glVertex3f(-50.0f, 50.0f,-50.0f);        // Bottom-left vertex
        glEnd();
    glPopMatrix();
}
void drawPit(){
    glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glScalef(0.2,0.2,0.2);
    glTranslatef(1,0.5,-2.5);
    glutSolidIcosahedron();
    glTranslatef(-1.0,0.0,0);
    glutSolidIcosahedron();
    glColor3f(0.6,0.6,0.6);
    glTranslatef(0.5,0.5,0);
    glutSolidIcosahedron();
    glTranslatef(0.0,-1.0,0);
    glutSolidIcosahedron();
    glPopMatrix();
}
void drawFire(){
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(-90,1.0,0.0,0.0);
    drawParticle();
    drawPit();
    glPopMatrix();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, cameraZ,  // Eye position
              0.0, 0.0, 0.0,  // Look-at point
              0.0, 1.0, 0.0); // Up direction
    background();
    drawFire();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
}

void motion(int x, int y) {
    rotationAngleX += (y - lastMouseY);
    rotationAngleY += (x - lastMouseX);
    lastMouseX = x;
    lastMouseY = y;
    glutPostRedisplay();
}

void update() {
    updateParticle();
    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(720, 400);

    glutCreateWindow("Msim");
    init();
    initParticle();
    initExplosion();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialKeyboardHandler);

    glEnable(GL_COLOR_MATERIAL);
    glutTimerFunc(0, update, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}

