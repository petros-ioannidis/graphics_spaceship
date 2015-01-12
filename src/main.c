#include <stdio.h>
#include <GL/glut.h>
#include "../headers/spaceship.h"

float sun_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f};
float sun_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f};
float sun_position[] = { 100.0f, 0.0f, 2.0f, 1.0f};

float test = 270;
int keys[256];

Spaceship space_ship;

void Setup()  
{ 

    glEnable( GL_CULL_FACE );

    glShadeModel( GL_SMOOTH );

    glEnable(GL_DEPTH_TEST);
    glDepthFunc( GL_LEQUAL );      
    glClearDepth(1.0); 		      

    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, sun_position);


    // polygon rendering mode and material properties
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Black background
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void spawn_galaxy()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //the body of the spaceship
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -10.0f);
    //glRotatef(test, 0.0, 1.0 ,0.0);
    glRotatef(90, 0.0, 1.0 ,0.0);
    spaceship();
    space_ship.x = 0.0f;
    space_ship.y = 0.0f;
    space_ship.z = -10.0f;
    space_ship.speed_x = 0.0f;
    space_ship.speed_y = 0.0f;
    space_ship.speed_z = 0.0f;
    glPopMatrix();

    glutSwapBuffers();
}

void Render()
{    
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //move the spaceship
    space_ship.x += space_ship.speed_x;
    space_ship.y += space_ship.speed_y;
    space_ship.z += space_ship.speed_z;

    //the body of the spaceship
    glPushMatrix();
    glTranslatef(space_ship.x, space_ship.y, space_ship.z);
    glRotatef(90, 0.0, 1.0 ,0.0);
    //glRotatef(test, 0.0, 1.0 ,0.0);
    //glRotatef(90, 0.0, 0.0 ,0.0);
    spaceship();
    glPopMatrix();
    test += 8.0f;


    glutSwapBuffers();
}

//-----------------------------------------------------------


void Resize(int w, int h)
{ 
    // define the visible area of the window ( in pixels )
    if (h==0) h=1;
    glViewport(0,0,w,h); 

    // Setup viewing volume

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();

    ////(02b)
    // L     R       B      T      N      F
    //glOrtho (-50.0f, 50.0f, -50.0f, 50.0f,-500.0f,500.0f);


    float aspect = (float)w/(float)h;             /// aspect ratio
    gluPerspective(60.0, aspect, 1.0, -200.0);
}

void keyboard_handling(unsigned char key, int x, int y)
{
    switch(key){
        case 27:
            exit(0);
        }
}

void arrow_keys_handling(int a_keys, int x, int y)
{
    switch(a_keys){
        case GLUT_KEY_UP:
            space_ship.speed_y += 0.01f;
            break;
        case GLUT_KEY_DOWN:
            space_ship.speed_y += -0.01f;
            break;
        case GLUT_KEY_RIGHT:
            space_ship.speed_x += 0.01f;
            break;
        case GLUT_KEY_LEFT:
            space_ship.speed_x += -0.01f;
            break;
    }
}

int main(int argc, char* argv[])
{ 
    // initialize GLUT library state
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);


    // Define the main window size and initial position 
    // ( upper left corner, boundaries included )
    glutInitWindowSize(1600, 1000);
    glutInitWindowPosition(50,50);

    // Create and label the main window
    glutCreateWindow("spaceship");

    // Configure various properties of the OpenGL rendering context
    Setup();

    // Callbacks for the GL and GLUT events:

    // The rendering function 
    glutDisplayFunc(spawn_galaxy);
    glutReshapeFunc(Resize);
    glutIdleFunc(Render);
    glutKeyboardFunc(keyboard_handling);
    glutSpecialFunc(arrow_keys_handling);
    //Enter main event handling loop
    glutMainLoop();
    return 0;


}
