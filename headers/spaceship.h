#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

/* body sphere dimensions */
static float body_radius = 1.0f;
static float body_scale_x = 2.5f;
static float body_scale_y = 1.0f;
static float body_scale_z = 1.0f;

/* turbine dimensions */
static float turbine_radius = 0.2f;
static float turbine_ring = 0.04f;
static float turbine_scale_x = 1.0f;
static float turbine_scale_y = 1.0f;
static float turbine_scale_z = 3.0f;

/* back of the turbine dimensions */
static float turbine_back_radius = 0.2f;
static float turbine_back_scale_x = 1.0f;
static float turbine_back_scale_y = 1.0f;
static float turbine_back_scale_z = 0.15f;

/* spaceship wing dimensions */
static float wing_base = 0.1f;
static float wing_height = 1.0f;
static float wing_scale_x = 6.5f;
static float wing_scale_y = 0.5f;
static float wing_scale_z = 1.8f;

/* spaceship tail dimensions */
static float tail_base = 0.1f;
static float tail_height = 1.0f;
static float tail_scale_x = 6.5f;
static float tail_scale_y = 0.5f;
static float tail_scale_z = 1.8f;

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
#endif
