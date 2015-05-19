#ifndef BODY_SPHERE_H
#define	BODY_SPHERE_H
/* 
 * File:   Body_sphere.h
 * Author: Ying Lu 
 *
 * Created on November 2nd, 2014
 */

#include <iostream>
#include <string>
#include <glm/glm.hpp>


using namespace std;

typedef struct Sphere{
    // constructor
Sphere():/*Name("Body_Sphere"), Body_Type("sphere"), */Mass_Matrix(glm::mat3(1.0)), Mass_Inverse_Matrix(glm::mat3(1.0)), Inertia_Matrix(glm::mat3(1.0)), U(glm::vec3(0.0)), Quat(glm::vec4(1.0, 0.0, 0.0, 0.0)), R_rot(glm::mat3(1.0)), L_vel(glm::vec3(1.0)), A_vel(glm::vec3(1.0)), Fext(glm::vec3(0.0, 0.0, -9.8)), Text(glm::vec3(0.0)), Mu(0.5), IsStaticBody(false), Bounding_Radius(1.1), BodyIndex(-1), ContactCount(0)
    {
    }
    // property names start with CAPITAL letter
    //string Name;                          // Name of object
    //string Body_Type;                     // Body_Type = "sphere" here
    double Mass ;
    double Radius;

    glm::mat3 Mass_Matrix ;               // 3x3 mass matrix = mass * eye(3)
    glm::mat3 Mass_Inverse_Matrix;        // 3x3 inverse of mass matrix used for LCP formulation    
    glm::mat3 Inertia_Matrix;             // 3x3 inertia tensor 
    // TODO: change this to glm format?
    double Mass_Inertia_Matrix[6][6];     // 6x6 mass-inertia matrix
    glm::vec3 U;                          // Position [x y z]
    glm::vec4 Quat;                       // Quaternion [a i j k]
    glm::mat3 R_rot;                      // Rotation matrix
    glm::vec3 L_vel;                      // Linear Velocity as [Vx Vy Vz]
    glm::vec3 A_vel;                      // Angular Velocity as [Wx Wy Wz]
    glm::vec3 Fext ;                      // External force, [Fx Fy Fz]
    glm::vec3 Text ;                      // External torque, [Tx Ty Tz]
    double Mu ;                           // Friction "factor"
    bool IsStaticBody;                    // Dynamic or static body
    double Bounding_Radius;                              

    // dynamics variables 
    int BodyIndex ;
    int ContactCount;
}Sphere;
 
// Functions for struct Sphere
void setMassInertiaMatrix(Sphere &sphere);
void setPosition(Sphere &sphere, double x, double y, double z);
void setQuaternion(Sphere &sphere, double a, double i, double j, double k);
void setR_rot(Sphere &sphere, glm::mat3 r); 
void setL_vel(Sphere &sphere, double x, double y, double z);
void setA_vel(Sphere &sphere, double x, double y, double z);
void setFext(Sphere &sphere, double Fx, double Fy, double Fz);
void setText(Sphere &sphere, double Tx, double Ty, double Tz);
void applyAext(Sphere &sphere, double dt);

// Dynamics 
void stepDynamics(Sphere &sphere, double dt);

// Auxiliary methods
void sphere_print(Sphere &sphere);
void sphere_printPosition(Sphere &sphere);
#endif	/* BODY_SPHERE_H*/

