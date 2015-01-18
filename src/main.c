#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>
#include "../headers/spaceship.h"
#include "../headers/star.h"

typedef struct{
    float x;
    float y;
    float z;
}Camera;

GLuint asteroid;

float test = 270;
int time, frame=0, base_time=0;
unsigned int seed;

float sun_position[] = { 0.0f, 0.0f, -900.0f, 0.0f};

Spaceship space_ship;
Camera camera;

void load_asteroid(char *fname)
{
    FILE *fp;
    int read;
    float x[2],y[2],z[2];
    int pos[3] = {0, 0, 0};
    char ch[2];
    float v[10000][3];
    float vn[10000][3];

    asteroid = glGenLists(1);

    fp = fopen(fname, "r");
    if(fp == NULL){
        fprintf(stderr, "Couldn't load asteroid file\n");
        exit(-1);
    }

    glPointSize(2.0);
    glNewList(asteroid, GL_COMPILE);

    while(!(feof(fp))){
        read = fscanf(fp, "%c%c %f %f %f\n", &ch[0], &ch[1], &x[0], &y[0], &z[0]);
        if(read == 5 && ch[0] == 'v' && ch[1] == 'n'){
            //printf("%c%c %f %f %f\n", ch[1][0], ch[1][1], x[1], y[1], z[1]);
            vn[pos[0]][0] = x[0];
            vn[pos[0]][1] = y[0];
            vn[pos[0]][2] = z[0];
            pos[0]++;
            printf("%c%c %f %f %f\n", ch[0],ch[1], x[0], y[0], z[0]);
            //glVertex3f(x, y, z);
        }
        else if(read == 5 && ch[0]=='v'){
            printf("k\n");
            v[pos[1]][0] = x[0];
            v[pos[1]][1] = y[0];
            v[pos[1]][2] = z[0];
            pos[1]++;
            printf("%c %f %f %f\n", ch[0], x[0], y[0], z[0]);
            //glVertex3f(x, y, z);
        }
    }

    printf("1\n");
    
    fseek(fp, SEEK_SET, 0);
    while(1){
        read = fscanf(fp, "%c %f//%f %f//%f %f//%f\n", &ch[0], &x[0], &x[1], &y[0], &y[1], &z[0], &z[1]);
        if(ch[0] == 'f' && read == 7){
            printf("stop %d\n", read);
            break;
        }
    }

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    while(!feof(fp)){
        if(ch[0] == 'f'){
            printf("%c %f//%f %f//%f %f//%f\n", ch[0], x[0], x[1], y[0], y[1], z[0], z[1]);
            glNormal3f(vn[(int)x[1] - 1][0], vn[(int)x[1] - 1][1], vn[(int)x[1] - 1][2]);
            glVertex3f(v[(int)x[0] - 1][0], v[(int)x[0] - 1][1], v[(int)x[0] - 1][2]);
            printf("%f %f %f\n", vn[(int)x[1] - 1][0], vn[(int)x[1] - 1][1], vn[(int)x[1] - 1][2]);
            printf("%f %f %f\n", v[(int)x[0] - 1][0], v[(int)x[0] - 1][1], v[(int)x[0] - 1][1]);

            glNormal3f(vn[(int)y[1] - 1][0], vn[(int)y[1] - 1][1], vn[(int)y[1] - 1][2]);
            glVertex3f(v[(int)y[0] - 1][0], v[(int)y[0] - 1][1], v[(int)y[0] - 1][2]);
            printf("%f %f %f\n", vn[(int)y[1] - 1][0], vn[(int)y[1] - 1][1], vn[(int)y[1] - 1][2]);
            printf("%f %f %f\n", v[(int)y[0] - 1][0], v[(int)y[0] - 1][1], v[(int)y[0] - 1][1]);

            glNormal3f(vn[(int)z[1] - 1][0], vn[(int)z[1] - 1][1], vn[(int)z[1] - 1][2]);
            glVertex3f(v[(int)z[0] - 1][0], v[(int)z[0] - 1][1], v[(int)z[0] - 1][2]);
            printf("%f %f %f\n", vn[(int)z[1] - 1][0], vn[(int)z[1] - 1][1], vn[(int)z[1] - 1][2]);
            printf("%f %f %f\n", v[(int)z[0] - 1][0], v[(int)z[0] - 1][1], v[(int)z[0] - 1][1]);
            pos[2]++;
        }
        read = fscanf(fp, "%c %f//%f %f//%f %f//%f\n", &ch[0], &x[0], &x[1], &y[0], &y[1], &z[0], &z[1]);
    }
    glEnd();
    glPopMatrix();
    
    glEndList();
    fclose(fp);
    printf("%d %d %d\n", pos[0], pos[1], pos[2]);
}

void draw_asteroid()
{
    glPushMatrix();
    glScalef(0.1f, 0.1f, 0.1f);
    glColor4f(1.0f, 0.5f, 0.3f, 1.0f);
    glCallList(asteroid);
    glPopMatrix();
} 

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
    space_ship.z = -10.0f;
    space_ship.speed_x = 0.0f;
    space_ship.speed_y = 0.0f;
    space_ship.speed_z = 0.0f;

    camera.x = 0.0f;
    camera.y = 0.0f;
    camera.z = 0.0f;

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
    //glRotatef(test, 0.0, 1.0 ,0.0);
    glRotatef(90, 0.0, 1.0 ,0.0);
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
    glTranslatef(0.0f, 0.0f, -40.0f);
    draw_asteroid();
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
    glRotatef(camera.x, 1.0, 0.0 ,0.0);
    glRotatef(camera.y, 0.0, 1.0 ,0.0);
    glRotatef(camera.z, 0.0, 0.0 ,1.0);
    glPushMatrix();
    glTranslatef(space_ship.x, space_ship.y, space_ship.z);
    glRotatef(90, 0.0, 1.0 ,0.0);
    //glRotatef(test, 0.0, 1.0 ,0.0);
    //glRotatef(90, 0.0, 0.0 ,0.0);
    spaceship();
    glPopMatrix();
    test += 8.0f;

    glPushMatrix();
    glTranslatef(sun_position[0], sun_position[1], sun_position[2]);
    sun();
    
    glTranslatef(sun_position[0] - STAR_DISTANCE_X, sun_position[1] + STAR_DISTANCE_Y, sun_position[2] - STAR_DISTANCE_Z);
    srand(seed);
    stars(5000, 0);
    glPopMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, sun_position);

    glPushMatrix();
    glTranslatef(200.0f, 0.0f, -20.0f);
    draw_asteroid();
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
    seed = 10;
    srand(seed);
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
