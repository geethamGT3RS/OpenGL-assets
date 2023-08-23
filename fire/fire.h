#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int NUM_PARTICLES = 45;
const int FIRE = 180;

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float life;
} Particle;

Particle particles[NUM_PARTICLES];
Particle fire[FIRE];

void initParticle() {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        particles[i].x = 0.4*(float)rand()/RAND_MAX;
        particles[i].y = 0.4*(float)rand()/RAND_MAX;
        particles[i].z = 0.0;
        particles[i].vx =  -0.002*cos(i*360/NUM_PARTICLES) ;
        particles[i].vy =  -0.002*sin(i*360/NUM_PARTICLES);
        particles[i].vz =  0.05/(cos(i*360/NUM_PARTICLES)*cos(i*360/NUM_PARTICLES)) ;
        particles[i].life = 1.0f;
    }
}
void updateParticle() {
    for (int i = 0; i < NUM_PARTICLES; ++i) {
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;
        particles[i].z += particles[i].vz;
        particles[i].life -= 0.005f;

        if (particles[i].z >= 0.3f) {
            particles[i].x = 0.4*(float)rand()/RAND_MAX;
            particles[i].y = 0.4*(float)rand()/RAND_MAX;
            particles[i].z = 0.0f;
            particles[i].vx =  -0.002*cos(i*360/NUM_PARTICLES) ;
            particles[i].vy =  -0.002*sin(i*360/NUM_PARTICLES);
            particles[i].vz =  0.05/(cos(i*360/NUM_PARTICLES)*cos(i*360/NUM_PARTICLES)) ;
            particles[i].life = 1.0f;
        }
    }
}

void drawParticle() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < NUM_PARTICLES; ++i) {
        float alpha = particles[i].life;
        glColor4f(1.0f, 0.6+particles[i].z, 0.0f, alpha);

        glPushMatrix();
        glTranslatef(particles[i].x, particles[i].y, particles[i].z);
        glRotatef(i,0.0,0.0,1.0);
        glScalef(0.15,0.15,1);
        glutSolidIcosahedron();
        glEnd();
        glPopMatrix();
    }
    glDisable(GL_BLEND);
}
void initExplosion() {
    for (int i = 0; i < FIRE; ++i) {
        fire[i].x = 0.0f;
        fire[i].y = 0.0f;
        fire[i].vx = 0.01*sin(i*360/FIRE)*((float)rand() / (float)RAND_MAX);
        fire[i].vy = 0.01*cos(i*360/FIRE)*((float)rand() / (float)RAND_MAX);
        fire[i].life = 1.0f;
    }
}
void updateExplosion() {
    for (int i = 0; i < FIRE; ++i) {
        fire[i].x += fire[i].vx;
        fire[i].y += fire[i].vy;
        fire[i].life -= 0.001f;
        if (sqrt((fire[i].y)*(fire[i].y)+(fire[i].x)*(fire[i].x))>2.0f) {
            fire[i].x = 0.0f;
            fire[i].y = 0.0f;
            fire[i].vx = 0.01*sin(i*360/FIRE)*((float)rand() / (float)RAND_MAX);
            fire[i].vy = 0.01*cos(i*360/FIRE)*((float)rand() / (float)RAND_MAX);
            fire[i].life = 1.0f;
        }
    }
}
void drawExplosion() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float color,alpha;
    for (int i = 0; i < FIRE; ++i) {
        alpha = fire[i].life;
        if (i%2==0){
            color = 0.7*(float)rand() / (float)RAND_MAX;
            glColor4f(1.0,color,0.0,alpha);
        }else{
            color = 0.8*((float)rand() / (float)RAND_MAX);
            glColor4f(color,color,color,alpha+0.5);
        }

        glPushMatrix();
        glTranslatef(fire[i].x, fire[i].y, 0.0);
        glScalef(0.5,0.5,4.0);
        glRotatef(i,0.0,0.0,1.0);
        glutSolidIcosahedron();
        glPopMatrix();
    }
    glDisable(GL_BLEND);
}