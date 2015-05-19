/*
 * sphere_on_sphere_types.h
 *
 * Code generation for function 'sphere_on_sphere'
 *
 * C source code generated on: Sat Oct 18 11:57:31 2014
 *
 */

#ifndef __SPHERE_ON_SPHERE_TYPES_H__
#define __SPHERE_ON_SPHERE_TYPES_H__

/* Type Definitions */
typedef struct
{
    char_T name[4];
    char_T type[7];
    real_T bodyID;
    real_T bodyContactID;
    real_T bodyDynamicID;
    boolean_T dynamic;
    boolean_T active;
    real_T mass;
    real_T u[3];
    real_T quat[4];
    real_T J[9];
    real_T nu[6];
    real_T Fext[6];
    real_T Aext[6];
    real_T mu;
    real_T numJoints;
    boolean_T visible;
    real_T color[3];
    real_T facealpha;
    real_T edgealpha;
    real_T AABB_min[3];
    real_T AABB_max[3];
    boolean_T collides;
    real_T radius;
    real_T num_sphere_verts;
    real_T height;
    real_T plane_normal[3];
    real_T num_verts;
    real_T num_edges;
    real_T num_faces;
} b_struct_T;
#ifndef struct_sqW2AeKmSFihGYYeOmxr4i
#define struct_sqW2AeKmSFihGYYeOmxr4i
typedef struct sqW2AeKmSFihGYYeOmxr4i
{
    char_T name[4];
    char_T type[7];
    real_T bodyID;
    real_T bodyContactID;
    real_T bodyDynamicID;
    boolean_T dynamic;
    boolean_T active;
    real_T mass;
    real_T u[3];
    real_T quat[4];
    real_T J[9];
    real_T nu[6];
    real_T Fext[6];
    real_T Aext[6];
    real_T mu;
    real_T numJoints;
    boolean_T visible;
    real_T color[3];
    real_T facealpha;
    real_T edgealpha;
    real_T AABB_min[3];
    real_T AABB_max[3];
    boolean_T collides;
    real_T radius;
    real_T num_sphere_verts;
    real_T height;
    real_T plane_normal[3];
    real_T num_verts;
    real_T num_edges;
    real_T num_faces;
} d_struct_T;
#else
typedef struct sqW2AeKmSFihGYYeOmxr4i d_struct_T;
#endif
typedef struct
{
    real_T time;
    real_T step;
    real_T MAX_STEP;
    boolean_T gravity;
    real_T gravityVector[3];
    boolean_T jointCorrection;
    boolean_T record;
    real_T record_fileID;
    boolean_T FRICTION;
    real_T num_fricdirs;
    real_T num_bodies;
    real_T num_jointConstraints;
    real_T num_activeJointBodies;
    real_T num_activeBodies;
    real_T num_dynamicBodies;
    real_T epsilon;
    real_T figure;
    boolean_T draw;
    boolean_T drawContacts;
    boolean_T drawBoundingBoxes;
    boolean_T drawJoints;
    real_T h;
} struct_T;
#ifndef struct_sqW2AeKmSFihGYYeOmxr4i_size
#define struct_sqW2AeKmSFihGYYeOmxr4i_size
typedef struct sqW2AeKmSFihGYYeOmxr4i_size
{
    int32_T type[2];
} struct_T_size;
#else
typedef struct sqW2AeKmSFihGYYeOmxr4i_size struct_T_size;
#endif

#endif
/* End of code generation (sphere_on_sphere_types.h) */
