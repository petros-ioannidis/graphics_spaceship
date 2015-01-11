#include <stdio.h>
#include <GL/glut.h>
#include "../headers/spaceship.h"


void spaceship_body(void)
{
    /* the spaceship body consists of a scaled sphere */
    glTranslatef(2.0f, 0.0f, -6.0f);
    glColor3f(0.5f, 0.2f, 0.7f);
    glScalef(2.5f, 1.0f, 1.0f);
    glutSolidSphere(1.0f, 100.0f, 100.0f);
}

void spaceship(void)
{
    spaceship_body();
}
