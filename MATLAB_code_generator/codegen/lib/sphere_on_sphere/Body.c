/*
 * Body.c
 *
 * Code generation for function 'Body'
 *
 * C source code generated on: Sat Oct 18 11:59:48 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sphere_on_sphere.h"
#include "Body.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void Body(b_struct_T *B)
{
  int32_T i;
  static const char_T cv1[4] = { 'b', 'o', 'd', 'y' };

  static const char_T cv2[7] = { 'g', 'e', 'n', 'e', 'r', 'i', 'c' };

  static const int8_T iv1[4] = { 1, 0, 0, 0 };

  int8_T I[9];
  static const int8_T iv2[3] = { 0, 0, 1 };

  /*  Creates a body struct with default body properties */
  /*  The body struct */
  /* B = struct; */
  for (i = 0; i < 4; i++) {
    B->name[i] = cv1[i];
  }

  for (i = 0; i < 7; i++) {
    B->type[i] = cv2[i];
  }

  B->bodyID = 0.0;

  /*  Body's position in the simulation's vector of bodies */
  B->bodyContactID = 0.0;

  /*  Body's id for current time-step contact set */
  B->bodyDynamicID = 0.0;

  /*  TODO: duplicate of bodyContactID?  */
  /*  Physical properties */
  B->dynamic = TRUE;

  /*  Dynamic vs. static body  */
  B->active = FALSE;

  /*  An active body is one that is in dynamic interaction with  */
  /*    another body through contact or some other constraint.   */
  B->mass = 1.0;

  /*  Mass */
  for (i = 0; i < 3; i++) {
    B->u[i] = 0.0;
  }

  /*  Position of center of mass */
  for (i = 0; i < 4; i++) {
    B->quat[i] = (real_T)iv1[i];
  }

  /*  Quaternion rotation */
  for (i = 0; i < 9; i++) {
    I[i] = 0;
  }

  for (i = 0; i < 3; i++) {
    I[i + 3 * i] = 1;
  }

  for (i = 0; i < 9; i++) {
    B->J[i] = (real_T)I[i];
  }

  /*  Inertia tensor */
  /* B.v = zeros(3,1);       % Linear velocity */
  /* B.w = zeros(3,1);       % Angular velocity */
  for (i = 0; i < 6; i++) {
    B->nu[i] = 0.0;

    /*  Generalized velocity [v; w] */
    B->Fext[i] = 0.0;

    /*  External force */
    B->Aext[i] = 0.0;
  }

  /*  External acceleration */
  B->mu = 0.5;

  /*  Friction factor */
  /*  Joint-related properties */
  B->numJoints = 0.0;

  /*  Graphics properties  */
  B->visible = TRUE;

  /*  Graphics object for plotting the body */
  for (i = 0; i < 3; i++) {
    B->color[i] = (real_T)iv2[i];
  }

  /*  Color of body */
  B->facealpha = 0.7;
  B->edgealpha = 1.0;

  /*  Graphics object for plotting bounding box */
  /*  Collision detection properties */
  for (i = 0; i < 3; i++) {
    B->AABB_min[i] = 0.0;

    /*  Bounding box */
    B->AABB_max[i] = 0.0;
  }

  B->collides = TRUE;

  /*  If false, this body won't collide with any other bodies */
  /*  A list of bodyIDs of bodies not to do collision detection with */
  /*     %% Different bodies have different attributes, but for simplicity  */
  /*   we want all bodies to be represented by this struct.  Therefore we */
  /*   place all body attributes here, and let bodies pick and choose. */
  /*     %% Sphere attributes */
  B->radius = 1.0;
  B->num_sphere_verts = 7.0;

  /*  Decrease to improve graphics performance  */
  /*  (does not affect simulation result) */
  /*     %% Cylinder attributes */
  B->height = 1.0;

  /*     %% Plane attributes */
  for (i = 0; i < 3; i++) {
    B->plane_normal[i] = (real_T)iv2[i];
  }

  /*     %% Mesh attributes */
  B->num_verts = 0.0;
  B->num_edges = 0.0;
  B->num_faces = 0.0;

  /*  A Nx3 vector of N vertices relative to the COM of the body */
  /*  A Nx3 vector of N vertices in the world space */
  /*  A Ex [v1 v2 Enext Eopp face]   TODO: remove implicit columns Enext and face */
  /*  A Ex5 vector [v1 v2 f1 f2 a] where v1:first */
  /*  vert, v2: second vert, f1: first face, f2: */
  /*  second face, a: angle between faces */
  /*  A Ex6 vector of t vectors (always in local coords), perp to edge and planar to adjacent faces */
  /*  A Mx4 vector of M faces where each row contains: [v1 v2 v3 e1] */
  /*  A Mx3 vector of M face norms where each row contains [n1 n2 n3]  */
}

/* End of code generation (Body.c) */
