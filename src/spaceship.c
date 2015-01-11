#include <stdio.h>
#include <GL/glut.h>
#include "../headers/spaceship.h"

float test = 0;

void spaceship_turbine(void)
{
    /* this is the turbing along with the fan */
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.3f);
    glScalef(1.0f, 1.0f, 3.0f);
    glutSolidTorus(0.04f, 0.2f, 1000, 1000);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    glScalef(3.0f, 0.7f, 0.7f);
    glutSolidSphere(0.05f, 100.0f, 100.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(90, 0.0f, 0.0f, 1.0f);
    glScalef(3.0f, 0.7f, 0.7f);
    glutSolidSphere(0.05f, 100.0f, 100.0f);
    glPopMatrix();
}

void spaceship_wing(void)
{
    /* the spaceship side wings */
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.6f);
    glScalef(6.5f, 0.5f, 1.8f);
    glutSolidCone(0.1f, 1.0f, 3, 3);
    glPopMatrix();
}

void spaceship_body(void)
{
    /* the spaceship body consists of a scaled sphere */
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.6f);
    glScalef(2.5f, 1.0f, 1.0f);
    glutSolidSphere(1.0f, 100.0f, 100.0f);
    glPopMatrix();
}

void spaceship(void)
{
    spaceship_body();
    glTranslatef(-4.0f, 0.0f, 0.0f);
    glRotatef(test, 1.0, 0.0 , 0.0);
    spaceship_turbine();
    test += 13.4;
}
