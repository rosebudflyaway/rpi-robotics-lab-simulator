/*
 * Simulator.c
 *
 * Code generation for function 'Simulator'
 *
 * C source code generated on: Sat Oct 18 11:59:48 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sphere_on_sphere.h"
#include "Simulator.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void Simulator(real_T varargin_1, struct_T *sim)
{
  int32_T i;
  static const real_T dv1[3] = { 0.0, 0.0, -9.81 };

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  RPI-MATLAB-Simulator */
  /*  http://code.google.com/p/rpi-matlab-simulator/ */
  /*  */
  /*  Creates a Simulator struct containing simulation properties */
  /*  The simulator struct */
  /* sim = struct();  */
  /*  Simulator properties */
  sim->time = 0.0;
  sim->step = 0.0;
  sim->MAX_STEP = 1.0E+9;
  sim->gravity = TRUE;
  for (i = 0; i < 3; i++) {
    sim->gravityVector[i] = dv1[i];
  }

  sim->jointCorrection = FALSE;
  sim->record = FALSE;
  sim->record_fileID = -1.0;
  sim->FRICTION = TRUE;
  sim->num_fricdirs = 7.0;

  /*  A function handle to a user function */
  /* sim.userData = struct;      % A struct for storing user data */
  /*  Body properties */
  sim->num_bodies = 0.0;

  /*  Function handles */
  /* sim.H_collision_detection = @collision_detection;  */
  /* sim.H_dynamics = @LCPdynamics; */
  /* sim.H_solver = @pathsolver;  */
  /*  Use PATH's courtesy license if one isn't set already. */
  /*      if isempty(getenv('PATH_LICENSE_STRING')) */
  /*          setenv('PATH_LICENSE_STRING','2069810742&Courtesy_License&&&USR&2013&14_12_2011&1000&PATH&GEN&31_12_2013&0_0_0&0&0_0'); */
  /*      end */
  /* sim.dynamics = struct; */
  sim->num_jointConstraints = 0.0;
  sim->num_activeJointBodies = 0.0;
  sim->num_activeBodies = 0.0;
  sim->num_dynamicBodies = 0.0;

  /*  Store solution error */
  /*  Collision detection properties */
  sim->epsilon = 0.05;

  /*  Graphics properties */
  sim->figure = 1.0;
  sim->draw = TRUE;
  sim->drawContacts = FALSE;
  sim->drawBoundingBoxes = FALSE;
  sim->drawJoints = FALSE;

  /*     %% Parse input arguments */
  sim->h = 0.01;
}

/* End of code generation (Simulator.c) */
