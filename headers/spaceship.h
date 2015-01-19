#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

typedef struct{
    float x;
    float y;
    float z;
    float speed_x;
    float speed_y;
    float speed_z;
}Spaceship;

/* create the turbine of the spaceship */
void spaceship_turbine(void);
/* create the side wing of the spaceship */
void spaceship_wing(void);
/* create the tail of the spaceship */
void spaceship_tail(void);
/* create the body of the spaceship */
void spaceship_body(void);
/* create the spaceship */
void spaceship(void);
int spaceship_coll_asteroid(Spaceship space_ship);
#endif
