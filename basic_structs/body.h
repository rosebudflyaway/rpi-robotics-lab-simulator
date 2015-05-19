#ifndef BODY_H
#define BODY_H 

/* body struct, once collision detection  */ 
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Body 
{
	int body_ID;
    std::string body_type;

    double mass;
    glm::mat3 mass_matrix;         // 3x3 matrix in body frame 
    glm::mat3 inverse_mass_matrix; // 3x3 inverse of mass matrix 
    glm::mat3 inertia_matrix;      // 3x3 inertia matrix 
    
    glm::vec3 position;
    glm::vec3 linear_vel;
    glm::vec3 angular_vel;
    glm::vec4 quaternion;
    glm::mat3 rotation_matrix;   // 3x3 rotation matrix 

    glm::vec3 external_force;
    glm::vec3 external_torque;
    
    double mu;                   // frictional coefficient related to the body 
    int    dynamic;              // 0--static body;  1--dynamic body
    double bounding_radius;      // used for broad-phase collision detection   
};

#endif