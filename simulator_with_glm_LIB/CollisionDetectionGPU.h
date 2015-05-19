#ifndef COLLISION_DETECTION_GPU_H
#define	COLLISION_DETECTION_GPU_H

/* 
 * File:   CollisionDetectionGPU.h
 * Author: Dave Kotfis
 *
 * Created on November 11, 2014
 */


//TODO: Figure out how to avoid doing this
#undef isnan
#undef isinf
#include <glm/glm.hpp>

#include "Body_sphere.h"
#include "Contact.h"

// find an arbitraty tangent to a normalized vector n
extern "C" void findContactsGPU(Contact* contacts, Sphere* spheres, int num_contacts, int num_spheres);

#endif	/* COLLISION_DETECTION_GPU_H */

