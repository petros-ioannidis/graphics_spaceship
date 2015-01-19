#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "../headers/asteroid.h"

GLuint asteroid_;
static Asteroid asteroid;

void load_asteroid(char *fname)
{
    FILE *fp;
    int read;
    float x[2],y[2],z[2];
    int pos[3] = {0, 0, 0};
    char ch[2];
    float v[10000][3];
    float vn[10000][3];

    asteroid_ = glGenLists(1);

    fp = fopen(fname, "r");
    if(fp == NULL){
        fprintf(stderr, "Couldn't load asteroid file\n");
        exit(-1);
    }

    glPointSize(2.0);
    glNewList(asteroid_, GL_COMPILE);

    while(!(feof(fp))){
        read = fscanf(fp, "%c%c %f %f %f\n", &ch[0], &ch[1], &x[0], &y[0], &z[0]);
        if(read == 5 && ch[0] == 'v' && ch[1] == 'n'){
            //printf("%c%c %f %f %f\n", ch[1][0], ch[1][1], x[1], y[1], z[1]);
            vn[pos[0]][0] = x[0];
            vn[pos[0]][1] = y[0];
            vn[pos[0]][2] = z[0];
            pos[0]++;
            //glVertex3f(x, y, z);
        }
        else if(read == 5 && ch[0]=='v'){
            v[pos[1]][0] = x[0];
            v[pos[1]][1] = y[0];
            v[pos[1]][2] = z[0];
            pos[1]++;
            //glVertex3f(x, y, z);
        }
    }

    
    fseek(fp, SEEK_SET, 0);
    while(1){
        read = fscanf(fp, "%c %f//%f %f//%f %f//%f\n", &ch[0], &x[0], &x[1], &y[0], &y[1], &z[0], &z[1]);
        if(ch[0] == 'f' && read == 7){
            break;
        }
    }

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    while(!feof(fp)){
        if(ch[0] == 'f'){
            glNormal3f(vn[(int)x[1] - 1][0], vn[(int)x[1] - 1][1], vn[(int)x[1] - 1][2]);
            glVertex3f(v[(int)x[0] - 1][0], v[(int)x[0] - 1][1], v[(int)x[0] - 1][2]);

            glNormal3f(vn[(int)y[1] - 1][0], vn[(int)y[1] - 1][1], vn[(int)y[1] - 1][2]);
            glVertex3f(v[(int)y[0] - 1][0], v[(int)y[0] - 1][1], v[(int)y[0] - 1][2]);

            glNormal3f(vn[(int)z[1] - 1][0], vn[(int)z[1] - 1][1], vn[(int)z[1] - 1][2]);
            glVertex3f(v[(int)z[0] - 1][0], v[(int)z[0] - 1][1], v[(int)z[0] - 1][2]);
            pos[2]++;
        }
        read = fscanf(fp, "%c %f//%f %f//%f %f//%f\n", &ch[0], &x[0], &x[1], &y[0], &y[1], &z[0], &z[1]);
    }
    glEnd();
    glPopMatrix();
    
    glEndList();
    fclose(fp);
}

void draw_asteroid()
{
    static int num_of_asteroids = 0;
    float mat_ambient[] ={ 0.0f,0.0f,0.0f,1.0f };
    float mat_diffuse[] ={ 0.1f,0.1f,0.1f,1.0f};
    float mat_specular[] ={0.0f,0.0f,0.0f,1.0f };
    float shine = 32.0f ;

    if( asteroid.position[2] > 0.0f && num_of_asteroids == 1){
        num_of_asteroids = 0;
    }
    else if( num_of_asteroids == 0 ){
        asteroid.position[0] = 0.0f;
        asteroid.position[1] = 0.0f;
        asteroid.position[2] = -400.0f;
        asteroid.rotation_x = 0.5f;
        asteroid.rotation_y = 1.0f;
        asteroid.rotation_z = 0.2f;
        asteroid.scale = 0.001;
        asteroid.radius = 657.0f*asteroid.scale;
        asteroid.speed = 0.7f;
        asteroid.ang_speed = 0.7f;
        num_of_asteroids = 1;
    }

    if( num_of_asteroids ){
        asteroid.position[2] += asteroid.speed;
        asteroid.rotation += asteroid.ang_speed;
        glPushMatrix();

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shine);
        glColor4f(0.8f, 0.8f, 0.8f, 1.0f);

        glTranslatef( asteroid.position[0], asteroid.position[1], asteroid.position[2] );
        glScalef(asteroid.scale, asteroid.scale, asteroid.scale);
        glRotatef(asteroid.rotation, asteroid.rotation_x, asteroid.rotation_y, asteroid.rotation_z);
        glCallList(asteroid_);
        glPopMatrix();
    }
} 

int test_collision(float x_left, float y_down, float z_front, float x_right, float y_up, float z_back)
{
    float dist_squared = asteroid.radius * asteroid.radius;

    if( asteroid.position[0] < x_left )
        dist_squared -= (asteroid.position[0] - x_left) * (asteroid.position[0] - x_left);
    else if( asteroid.position[0] > x_right )
        dist_squared -= (asteroid.position[0] - x_left) * (asteroid.position[0] - x_left);

    if( asteroid.position[1] < y_down )
        dist_squared -= (asteroid.position[1] - y_down) * (asteroid.position[1] - y_down);
    else if( asteroid.position[1] > y_up )
        dist_squared -= (asteroid.position[1] - y_up) * (asteroid.position[1] - y_up);

    if( asteroid.position[2] < z_front )
        dist_squared -= (asteroid.position[2] - z_front) * (asteroid.position[2] - z_front);
    else if( asteroid.position[2] > z_back )
        dist_squared -= (asteroid.position[2] - z_back) * (asteroid.position[2] - z_back);

    return dist_squared > 0;
            
}
