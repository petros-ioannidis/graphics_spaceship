#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include "../headers/spaceship.h"
#include "../headers/star.h"

extern int pause;

void sun(){
    GLfloat ambiref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat diffref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat emmiref[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat shine = 0.25f;
    float oscil_max = 20.0f;
    static float curr_sun_var = 0;
    static float speed_sun_var = 1.0f;

    if( !pause ){
        if(abs(curr_sun_var) > oscil_max)
            speed_sun_var = - speed_sun_var;
        curr_sun_var += speed_sun_var;
    }

    glCullFace(GL_FRONT);
    glColor4f(1.0f, 1.0f, 0.8f, 0.5 + 0.5*(oscil_max - curr_sun_var)/(2*oscil_max));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmiref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glutSolidSphere(100.0f + curr_sun_var, 30, 50);
    glCullFace(GL_BACK);

    glCullFace(GL_FRONT);
    glColor4f(1.0f, 1.0f, 0.8f, 0.5);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmiref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glutSolidSphere(90.0f, 30, 50);
    glCullFace(GL_BACK);
}

void star(){
    GLfloat ambiref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat diffref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat emmiref[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat shine = 0.25f;
    float oscil_max = 20.0f;
    static float curr_sun_var = 0;
    static float speed_sun_var = 0.010f;

    if( !pause ){
        if(abs(curr_sun_var) > oscil_max)
            speed_sun_var = - speed_sun_var;
        curr_sun_var += speed_sun_var;
    }

    glCullFace(GL_FRONT);
    glColor4f(1.0f, 1.0f, 0.8f, 0.5 + 0.5*(oscil_max - curr_sun_var)/(2*oscil_max));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmiref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glutSolidSphere(100.0f + curr_sun_var, 6, 6);
    glCullFace(GL_BACK);

    glCullFace(GL_FRONT);
    glColor4f(1.0f, 1.0f, 0.8f, 0.5);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emmiref);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glutSolidSphere(90.0f, 6, 6);
    glCullFace(GL_BACK);
}

void stars(int distance, int direction)
{
    int i = 0;
    int j = 0;
    int offset_x;
    int offset_y;
    int offset_z;

    int distance_x = 0;
    int distance_y = 0;
    int distance_z = 0;
    
    if(direction == 0)
        distance_x = distance;

    if(direction == 1)
        distance_y = distance;

    if(direction == 2)
        distance_z = distance;

    glPushMatrix();
    for(i = 0; i < LAYERS; i++)
    {
        glPushMatrix();
        for(j = 0; j < STARS; j++)
        {
            offset_x = rand()%distance;
            offset_y = rand()%distance;
            offset_z = rand()%distance;

            glPushMatrix();
            glTranslatef(offset_x, offset_y , offset_z);
            star();
            glPopMatrix();

            glTranslatef(distance_x, distance_y, distance_z);
        }
        glPopMatrix();
        glTranslatef(0.0f, -1.0*distance, 0.0f);
    }
    glPopMatrix();
}
