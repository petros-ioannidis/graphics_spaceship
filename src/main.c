#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include "../headers/spaceship.h"

typedef struct{
    float x;
    float y;
    float z;
}Camera;

float sun_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f};
float sun_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f};
float sun_position[] = { 0.0f, 200.0f, -200.0f, 1.0f};

float test = 270;
int time, frame=0, base_time=0;

Spaceship space_ship;
Camera camera;

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
    space_ship.x = 0.0f;
    space_ship.y = 0.0f;
    space_ship.z = -10.0f;
    space_ship.speed_x = 0.0f;
    space_ship.speed_y = 0.0f;
    space_ship.speed_z = 0.0f;

    camera.x = 0.0f;
    camera.y = 0.0f;
    camera.z = 0.0f;

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
    glPopMatrix();

    glutSwapBuffers();
}

void Render()
{    
    float fps;
    char fps_str[32];
    int i;
    void * font =  GLUT_BITMAP_TIMES_ROMAN_24; 
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //move the spaceship
    space_ship.x += space_ship.speed_x;
    space_ship.y += space_ship.speed_y;
    space_ship.z += space_ship.speed_z;

    //count the fps
    frame++;
    time = glutGet(GLUT_ELAPSED_TIME);
    
    if(time - base_time > 1000){
        fps = frame*1000.0/(time - base_time);
        sprintf(fps_str,"fps: %f\n", fps);
        base_time = time;
        frame = 0;
    }

    //render the fps on screen
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(0, w, h, 0);
    glMatrixMode( GL_MODELVIEW );

    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(10,h - 100);
    for(i = 0; i < strlen(fps_str); i++)
        glutBitmapCharacter(font ,fps_str[i]);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    //the body of the spaceship
    glPushMatrix();
    glTranslatef(space_ship.x, space_ship.y, space_ship.z);
    glRotatef(camera.x, 1.0, 0.0 ,0.0);
    glRotatef(90 + camera.y, 0.0, 1.0 ,0.0);
    glRotatef(camera.z, 0.0, 0.0 ,1.0);
    //glRotatef(test, 0.0, 1.0 ,0.0);
    //glRotatef(90, 0.0, 0.0 ,0.0);
    spaceship();
    glPopMatrix();
    test += 8.0f;


    glFlush();
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
        case 'w':
            camera.x += 1.0f;
            break;
        case 's':
            camera.x += -1.0f;
            break;
        case 'd':
            camera.y += 1.0f;
            break;
        case 'a':
            camera.y += -1.0f;
            break;
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
