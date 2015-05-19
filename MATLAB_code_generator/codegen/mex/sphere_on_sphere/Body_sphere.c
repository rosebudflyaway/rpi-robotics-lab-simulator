/*
 * Body_sphere.c
 *
 * Code generation for function 'Body_sphere'
 *
 * C source code generated on: Sat Oct 18 11:57:31 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sphere_on_sphere.h"
#include "Body_sphere.h"
#include "Body.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */

void Body_sphere(d_struct_T *body_data, struct_T_size *body_elems_sizes)
{
    b_struct_T expl_temp;
    char_T t0_name[4];
    int32_T i;
    char_T t0_type[7];
    real_T t0_u[3];
    real_T t0_quat[4];
    real_T t0_J[9];
    real_T t0_nu[6];
    real_T t0_Fext[6];
    real_T t0_Aext[6];
    real_T t0_color[3];
    real_T t0_AABB_min[3];
    real_T t0_AABB_max[3];
    real_T t0_plane_normal[3];
    static const char_T cv4[6] = { 's', 'p', 'h', 'e', 'r', 'e' };
    static const real_T y[9] = { 1.6, 0.0, 0.0, 0.0, 1.6, 0.0, 0.0, 0.0, 1.6 };
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  RPI-MATLAB-Simulator */
    /*  http://code.google.com/p/rpi-matlab-simulator/ */
    /*  */
    Body(&expl_temp);
    for (i = 0; i < 4; i++) {
        t0_name[i] = expl_temp.name[i];
    }
    for (i = 0; i < 7; i++) {
        t0_type[i] = expl_temp.type[i];
    }
    for (i = 0; i < 3; i++) {
        t0_u[i] = expl_temp.u[i];
    }
    for (i = 0; i < 4; i++) {
        t0_quat[i] = expl_temp.quat[i];
    }
    for (i = 0; i < 9; i++) {
        t0_J[i] = expl_temp.J[i];
    }
    for (i = 0; i < 6; i++) {
        t0_nu[i] = expl_temp.nu[i];
        t0_Fext[i] = expl_temp.Fext[i];
        t0_Aext[i] = expl_temp.Aext[i];
    }
    for (i = 0; i < 3; i++) {
        t0_color[i] = expl_temp.color[i];
        t0_AABB_min[i] = expl_temp.AABB_min[i];
        t0_AABB_max[i] = expl_temp.AABB_max[i];
        t0_plane_normal[i] = expl_temp.plane_normal[i];
    }
    for (i = 0; i < 4; i++) {
        body_data->name[i] = t0_name[i];
    }
    body_elems_sizes->type[0] = 1;
    body_elems_sizes->type[1] = 7;
    for (i = 0; i < 7; i++) {
        body_data->type[i] = t0_type[i];
    }
    body_data->bodyID = 0.0;
    body_data->bodyContactID = 0.0;
    body_data->bodyDynamicID = 0.0;
    body_data->dynamic = TRUE;
    body_data->active = FALSE;
    body_data->mass = 1.0;
    for (i = 0; i < 3; i++) {
        body_data->u[i] = t0_u[i];
    }
    for (i = 0; i < 4; i++) {
        body_data->quat[i] = t0_quat[i];
    }
    for (i = 0; i < 9; i++) {
        body_data->J[i] = t0_J[i];
    }
    for (i = 0; i < 6; i++) {
        body_data->nu[i] = t0_nu[i];
        body_data->Fext[i] = t0_Fext[i];
        body_data->Aext[i] = t0_Aext[i];
    }
    body_data->mu = 0.5;
    body_data->numJoints = 0.0;
    body_data->visible = TRUE;
    for (i = 0; i < 3; i++) {
        body_data->color[i] = t0_color[i];
    }
    body_data->facealpha = 0.7;
    body_data->edgealpha = 1.0;
    for (i = 0; i < 3; i++) {
        body_data->AABB_min[i] = t0_AABB_min[i];
        body_data->AABB_max[i] = t0_AABB_max[i];
    }
    body_data->collides = TRUE;
    body_data->radius = 1.0;
    body_data->num_sphere_verts = 7.0;
    body_data->height = 1.0;
    for (i = 0; i < 3; i++) {
        body_data->plane_normal[i] = t0_plane_normal[i];
    }
    body_data->num_verts = 0.0;
    body_data->num_edges = 0.0;
    body_data->num_faces = 0.0;
    body_elems_sizes->type[0] = 1;
    body_elems_sizes->type[1] = 6;
    for (i = 0; i < 6; i++) {
        body_data->type[i] = cv4[i];
    }
    body_data->radius = 2.0;
    for (i = 0; i < 9; i++) {
        body_data->J[i] = y[i];
    }
}

void b_Body_sphere(d_struct_T *body_data, struct_T_size *body_elems_sizes)
{
    b_struct_T expl_temp;
    char_T t1_name[4];
    int32_T i;
    char_T t1_type[7];
    real_T t1_u[3];
    real_T t1_quat[4];
    real_T t1_J[9];
    real_T t1_nu[6];
    real_T t1_Fext[6];
    real_T t1_Aext[6];
    real_T t1_color[3];
    real_T t1_AABB_min[3];
    real_T t1_AABB_max[3];
    real_T t1_plane_normal[3];
    static const char_T cv5[6] = { 's', 'p', 'h', 'e', 'r', 'e' };
    static const real_T y[9] = { 0.00625, 0.0, 0.0, 0.0, 0.00625, 0.0, 0.0, 0.0, 0.00625 };
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*  RPI-MATLAB-Simulator */
    /*  http://code.google.com/p/rpi-matlab-simulator/ */
    /*  */
    Body(&expl_temp);
    for (i = 0; i < 4; i++) {
        t1_name[i] = expl_temp.name[i];
    }
    for (i = 0; i < 7; i++) {
        t1_type[i] = expl_temp.type[i];
    }
    for (i = 0; i < 3; i++) {
        t1_u[i] = expl_temp.u[i];
    }
    for (i = 0; i < 4; i++) {
        t1_quat[i] = expl_temp.quat[i];
    }
    for (i = 0; i < 9; i++) {
        t1_J[i] = expl_temp.J[i];
    }
    for (i = 0; i < 6; i++) {
        t1_nu[i] = expl_temp.nu[i];
        t1_Fext[i] = expl_temp.Fext[i];
        t1_Aext[i] = expl_temp.Aext[i];
    }
    for (i = 0; i < 3; i++) {
        t1_color[i] = expl_temp.color[i];
        t1_AABB_min[i] = expl_temp.AABB_min[i];
        t1_AABB_max[i] = expl_temp.AABB_max[i];
        t1_plane_normal[i] = expl_temp.plane_normal[i];
    }
    for (i = 0; i < 4; i++) {
        body_data->name[i] = t1_name[i];
    }
    body_elems_sizes->type[0] = 1;
    body_elems_sizes->type[1] = 7;
    for (i = 0; i < 7; i++) {
        body_data->type[i] = t1_type[i];
    }
    body_data->bodyID = 0.0;
    body_data->bodyContactID = 0.0;
    body_data->bodyDynamicID = 0.0;
    body_data->dynamic = TRUE;
    body_data->active = FALSE;
    body_data->mass = 1.0;
    for (i = 0; i < 3; i++) {
        body_data->u[i] = t1_u[i];
    }
    for (i = 0; i < 4; i++) {
        body_data->quat[i] = t1_quat[i];
    }
    for (i = 0; i < 9; i++) {
        body_data->J[i] = t1_J[i];
    }
    for (i = 0; i < 6; i++) {
        body_data->nu[i] = t1_nu[i];
        body_data->Fext[i] = t1_Fext[i];
        body_data->Aext[i] = t1_Aext[i];
    }
    body_data->mu = 0.5;
    body_data->numJoints = 0.0;
    body_data->visible = TRUE;
    for (i = 0; i < 3; i++) {
        body_data->color[i] = t1_color[i];
    }
    body_data->facealpha = 0.7;
    body_data->edgealpha = 1.0;
    for (i = 0; i < 3; i++) {
        body_data->AABB_min[i] = t1_AABB_min[i];
        body_data->AABB_max[i] = t1_AABB_max[i];
    }
    body_data->collides = TRUE;
    body_data->radius = 1.0;
    body_data->num_sphere_verts = 7.0;
    body_data->height = 1.0;
    for (i = 0; i < 3; i++) {
        body_data->plane_normal[i] = t1_plane_normal[i];
    }
    body_data->num_verts = 0.0;
    body_data->num_edges = 0.0;
    body_data->num_faces = 0.0;
    body_elems_sizes->type[0] = 1;
    body_elems_sizes->type[1] = 6;
    for (i = 0; i < 6; i++) {
        body_data->type[i] = cv5[i];
    }
    body_data->radius = 0.25;
    for (i = 0; i < 9; i++) {
        body_data->J[i] = y[i];
    }
}
/* End of code generation (Body_sphere.c) */
