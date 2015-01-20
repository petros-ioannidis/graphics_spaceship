#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../headers/spaceship.h"
#include "../headers/star.h"
#include "../headers/asteroid.h"

typedef struct{
    float x;
    float y;
    float z;
    float dist_x;
    float dist_y;
    float dist_z;
}Camera;

int time_, frame=0, base_time=0;
unsigned int seed;
extern int pause;

float sun_position[] = { 0.0f, 0.0f, -900.0f, 0.0f};

Spaceship space_ship;
Camera camera;

void Setup()  
{ 

    glEnable( GL_CULL_FACE );

    glShadeModel( GL_SMOOTH );

    glEnable(GL_DEPTH_TEST);
    glDepthFunc( GL_LEQUAL );      
    glClearDepth(1.0); 		      



    // polygon rendering mode and material properties
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    // Black background
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void spawn_galaxy()
{

    float sun_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f};
    float sun_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f};
    float sun_spec[] = { 1.0f, 1.0f, 1.0f, 1.0f};

    space_ship.x = 0.0f;
    space_ship.y = 0.0f;
    space_ship.z = -20.0f;
    space_ship.speed_x = 0.0f;
    space_ship.speed_y = 0.0f;
    space_ship.speed_z = 0.0f;

    camera.x = 0.0f;
    camera.y = 0.0f;
    camera.z = 0.0f;
    camera.dist_x = 0.0f;
    camera.dist_y = 0.0f;
    camera.dist_z = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_spec);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, sun_position);

    glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //the body of the spaceship
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -10.0f);
    //glRotatef(90, 0.0, 1.0 ,0.0);
    spaceship();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sun_position[0], sun_position[1], sun_position[2]);
    sun();

    glTranslatef(sun_position[0] - STAR_DISTANCE_X, sun_position[1] + STAR_DISTANCE_Y, sun_position[2] - STAR_DISTANCE_Z);
    srand(seed);
    stars(2000, 0);
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0.0f, 0.0f, -40.0f);
    srand(time(NULL));
    draw_asteroid(space_ship.x, space_ship.y);
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
    if( !pause ){
        space_ship.x += space_ship.speed_x;
        space_ship.y += space_ship.speed_y;
        space_ship.z += space_ship.speed_z;
    }

    //count the fps
    frame++;
    time_ = glutGet(GLUT_ELAPSED_TIME);
    
    if(time_ - base_time > 1000){
        fps = frame*1000.0/(time_ - base_time);
        sprintf(fps_str,"fps: %f\n", fps);
        base_time = time_;
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

    glTranslatef(0.0f, 0.0f, +space_ship.z + camera.dist_z);
    glRotatef(camera.x, 1.0, 0.0 ,0.0);
    glRotatef(camera.y, 0.0, 1.0 ,0.0);
    glRotatef(camera.z, 0.0, 0.0 ,1.0);
    glTranslatef(0.0f, 0.0f, -space_ship.z - camera.dist_z);
    glTranslatef(0.0f, 0.0f, camera.dist_z);

    glPushMatrix();
    glTranslatef(space_ship.x, space_ship.y, space_ship.z);
    //glRotatef(90, 0.0, 1.0 ,0.0);
    //the body of the spaceship
    spaceship();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(sun_position[0], sun_position[1], sun_position[2]);
    sun();
    glLightfv(GL_LIGHT0, GL_POSITION, sun_position);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(sun_position[0] - STAR_DISTANCE_X, sun_position[1] + STAR_DISTANCE_Y, sun_position[2] - STAR_DISTANCE_Z);
    srand(seed);
    stars(5000, 0);
    glPopMatrix();

    if( spaceship_coll_asteroid(space_ship) ){
        pause = 1;
        glMatrixMode( GL_PROJECTION );
        glPushMatrix();
        glLoadIdentity();
        glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        gluOrtho2D(0, w, h, 0);
        glMatrixMode( GL_MODELVIEW );

        glPushMatrix();
        glLoadIdentity();
        glRasterPos2i(w/2,h/2);
        strncpy(fps_str, "You lose!", 32);
        for(i = 0; i < strlen(fps_str); i++)
            glutBitmapCharacter(font ,fps_str[i]);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    glPushMatrix();
    //glTranslatef(200.0f, 0.0f, -20.0f);
    srand(time(NULL));
    draw_asteroid(space_ship.x, space_ship.y);
    glPopMatrix();

    
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
    gluPerspective(60.0, aspect, 1.0, -2000.0);
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
        case 'q':
            camera.dist_z += -1.0f;
            break;
        case 'e':
            camera.dist_z += 1.0f;
            break;
        case 'p':
            pause = !pause;
            break;
        }
}

void arrow_keys_handling(int a_keys, int x, int y)
{
    if( !pause ){
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
}

int main(int argc, char* argv[])
{ 
    seed = 10;
    srand(seed);
    // initialize GLUT library state
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);


    // Define the main window size and initial position 
    // ( upper left corner, boundaries included )
    glutInitWindowSize(1600, 1000);
    glutInitWindowPosition(50,50);

    // Create and label the main window
    glutCreateWindow("spaceship");

    // Configure various properties of the OpenGL rendering context
    Setup();

    // Callbacks for the GL and GLUT events:

    load_asteroid("./asteroid.obj");
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
