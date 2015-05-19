#ifndef LCPDYNAMICS_H
#define	LCPDYNAMICS_H
/* 
 * File:   lcpDynamics.h
 * Author: Ying Lu 
 *
 * Created on November 3, 2014
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "Contact.h"
#include "Body_sphere.h"
using namespace std;

// functions
vector<double> lcpDynamics(vector<Contact> &contacts, vector<Sphere> &spheres, int &num_contacts,  int &num_spheres, double h); 

glm::mat3 rot(glm::vec3 k, double theta); 
glm::mat3 hat(glm::vec3 k); 

#endif	/* LCPDYNAMICS_H */

