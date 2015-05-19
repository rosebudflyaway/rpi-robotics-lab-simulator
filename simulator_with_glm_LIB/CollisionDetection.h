#ifndef COLLISIONDETECTION_H
#define	COLLISIONDETECTION_H

/* 
 * File:   CollisionDetection.h
 * Author: Ying Lu 
 *
 * Created on November 3, 2014
 */


#include "Body_sphere.h"
#include "Contact.h"
#include <vector>

// find an arbitraty tangent to a normalized vector n
glm::vec3 arbitraryTangent(glm::vec3 n);
void findContacts(vector<Contact> &contacts, vector<Sphere> &spheres, int &num_contacts, int &num_spheres);

#endif	/* COLLISIONDETECTION_H */

