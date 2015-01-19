#ifndef ASTEROID_H
#define ASTEROID_H

typedef struct{
    float position[3];
    float speed;
    float rotation;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float ang_speed;
    float radius;
    float scale;
}Asteroid;

void load_asteroid(char *);
void draw_asteroid();
int test_collision(float x_left, float y_down, float z_front, float x_right, float y_up, float z_back);
#endif
