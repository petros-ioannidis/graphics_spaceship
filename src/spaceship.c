#include <stdio.h>
#include <GL/glut.h>
#include "../headers/spaceship.h"

/* body sphere dimensions */
float body_radius = 1.0f;
float body_scale_x = 2.5f;
float body_scale_y = 1.0f;
float body_scale_z = 1.0f;

/* turbine dimensions */
float turbine_radius = 0.2f;
float turbine_ring = 0.04f;
float turbine_scale_x = 1.0f;
float turbine_scale_y = 1.0f;
float turbine_scale_z = 3.0f;

/* back of the turbine dimensions */
float turbine_back_radius = 0.2f;
float turbine_back_scale_x = 1.0f;
float turbine_back_scale_y = 1.0f;
float turbine_back_scale_z = 0.15f;

/* spaceship wing dimensions */
float wing_base = 0.1f;
float wing_height = 1.0f;
float wing_scale_x = 6.5f;
float wing_scale_y = 0.5f;
float wing_scale_z = 1.8f;

/* spaceship tail dimensions */
float tail_base = 0.1f;
float tail_height = 1.0f;
float tail_scale_x = 6.5f;
float tail_scale_y = 0.5f;
float tail_scale_z = 1.8f;

float turbine_r = 0;

void spaceship_turbine(void)
{
    float mat_ambient[] ={0.25f, 0.25f, 0.25f, 1.0f  };
    float mat_diffuse[] ={0.4f, 0.4f, 0.4f, 1.0f };
    float mat_specular[] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
    float shine = 76.8f;
    /* this is the turbine along with the fan */

    /* the color of the turbine */

    /* the main part of the turbine */
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glColor3f(0.98f, 0.937f, 0.858f);
    glScalef(turbine_scale_x, turbine_scale_y, turbine_scale_z);
    glutSolidTorus(turbine_ring, turbine_radius, 100, 100);
    glPopMatrix();
    
    /* the back part of the turbine */
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glColor3f(0.68f, 0.637f, 0.558f);
    glTranslatef(0.0f, 0.0f, 0.12f);
    glScalef(turbine_back_scale_x, turbine_back_scale_y, turbine_back_scale_z);
    glutSolidSphere(turbine_back_radius, 100, 100);
    glPopMatrix();

    /* the fan of the turbine */
    glPushMatrix();
    glRotatef(turbine_r, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glScalef(1.0f, 0.05f, 0.20f);
    glutSolidSphere(0.2f, 100.0f, 100.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(90 + turbine_r, 0.0f, 0.0f, 1.0f);
    glScalef(1.0f, 0.05f, 0.20f);
    glutSolidSphere(0.2f, 100.0f, 100.0f);
    glPopMatrix();

    turbine_r += 1.0f;
}

void spaceship_wing(void)
{
    float mat_ambient[] ={ 0.0f,0.0f,0.0f,1.0f };
    float mat_diffuse[] ={ 0.1f,0.35f,0.1f,1.0f};
    float mat_specular[] ={0.45f,0.55f,0.45f,1.0f };
    float shine = 32.0f ;

    /* the spaceship side wings */
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glColor3f(0.007f, 0.615f, 0.454f);
    glScalef(wing_scale_x, wing_scale_y, wing_scale_z);
    glutSolidCone(wing_base, wing_height, 100, 100);
    glPopMatrix();
}

void spaceship_tail(void)
{
    float mat_ambient[] ={ 0.0f,0.0f,0.0f,1.0f };
    float mat_diffuse[] ={ 0.1f,0.35f,0.1f,1.0f};
    float mat_specular[] ={0.45f,0.55f,0.45f,1.0f };
    float shine = 32.0f ;

    /* the spaceship tail */
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glColor3f(0.007f, 0.615f, 0.454f);
    glScalef(tail_scale_x, tail_scale_y, tail_scale_z);
    glutSolidCone(tail_base, tail_height, 100, 100);
    glPopMatrix();
}

void spaceship_body(void)
{
    /* the spaceship body consists of a scaled sphere */

    float mat_ambient[] ={0.25f, 0.25f, 0.25f, 1.0f  };
    float mat_diffuse[] ={0.4f, 0.4f, 0.4f, 1.0f };
    float mat_specular[] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
    float shine = 76.8f;


    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
    glColor3f(0.0f, 1.0f, 0.6f);
    glScalef(body_scale_x, body_scale_y, body_scale_z);
    glutSolidSphere(body_radius, 100, 100);
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
