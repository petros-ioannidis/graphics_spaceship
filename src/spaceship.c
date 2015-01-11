#include <stdio.h>
#include <GL/glut.h>
#include "../headers/spaceship.h"

float turbing_r = 0;

void spaceship_turbine(void)
{
    /* this is the turbing along with the fan */

    /* the color of the turbine */
    glColor3f(1.0f, 0.5f, 0.3f);

    /* the main part of the turbine */
    glPushMatrix();
    glScalef(1.0f, 1.0f, 3.0f);
    glutSolidTorus(0.04f, 0.2f, 1000, 1000);
    glPopMatrix();
    
    /* the back part of the turbine */
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.12f);
    glScalef(1.0f, 1.0f, 0.15f);
    glutSolidSphere(0.20f, 100.0f, 100.0f);
    glPopMatrix();

    /* the fan of the turbine */
    glPushMatrix();
    glRotatef(turbing_r, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glScalef(1.0f, 0.05f, 0.20f);
    glutSolidSphere(0.2f, 100.0f, 100.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(90 + turbing_r, 0.0f, 0.0f, 1.0f);
    glScalef(1.0f, 0.05f, 0.20f);
    glutSolidSphere(0.2f, 100.0f, 100.0f);
    glPopMatrix();

    turbing_r += 50;
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

void spaceship_tail(void)
{
    /* the spaceship tail */
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
    glPushMatrix();

    spaceship_body();

    glPushMatrix();
    glTranslatef(-2.70f, 0.0f, 0.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glScalef(2.0f, 2.0f, 2.0f);
    spaceship_turbine();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.00f, 0.0f, 0.0f);
    glRotatef(270, 1.0f, 0.0f, 0.0f);
    glRotatef(-30, 0.0f, 1.0f, 0.0f);
    spaceship_tail();
    glPopMatrix();

    /* right wing */
    glPushMatrix();
    glTranslatef(-0.50f, -0.20f, 0.5f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    glRotatef(10, 1.0f, 0.0f, 0.0f);
    spaceship_wing();
    glPopMatrix();

    /* left wing */
    glPushMatrix();
    glTranslatef(-0.50f, -0.20f, -0.5f);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    glRotatef(-10, 0.0f, 1.0f, 0.0f);
    glRotatef(-10, 1.0f, 0.0f, 0.0f);
    spaceship_wing();
    glPopMatrix();

    /* right wing turbine */
    glPushMatrix();
    glTranslatef(-0.50f, -0.20f, 0.5f);
    glTranslatef(-0.10f, -0.40f, 0.80f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    spaceship_turbine();
    glPopMatrix();

    /* left wing turbine */
    glPushMatrix();
    glTranslatef(-0.50f, -0.20f, -0.5f);
    glTranslatef(-0.10f, -0.40f, -0.80f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    spaceship_turbine();
    glPopMatrix();

    glPopMatrix();
}
