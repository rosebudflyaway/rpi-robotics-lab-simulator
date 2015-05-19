#ifndef CONTACT_H
#define CONTACT_H 

/* contact struct, once collision detection detects a contact between bodies, 
   a contact struct will be added to the contact_list */ 

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Contact 
{
	int contact_ID;
	int body1_ID;
	int body2_ID;
	std::string body1_type;
	std::string body2_type;
	double psi;         // gap: + when there is gap; - when there is penetration 

	glm::vec3 normal;   // the normal for body1, it is (-1)*normal for body2
	glm::vec3 r1;       // vector from the COM of body1 to the contact point in world frame
};

#endif
