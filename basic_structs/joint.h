#ifndef JOINT_H
#define JOINT_H 

/* joint struct, add joint type to the system once there 
exists bilateral joint between two bodies  */ 

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Joint
{
	int joint_ID;
	std::string joint_type;   // revolute, prismatic, spherical, etc
    
    int body1_ID;
	int body2_ID;
    std::string body1_type;
	std::string body2_type;
	
	glm::vec3 joint_origin;   // the initial position of the joint in world frame 
	glm::vec3 joint_axis;     // the initial direction of the joint axis in world frame 
};
#endif