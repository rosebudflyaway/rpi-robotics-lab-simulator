#ifndef SIMULATION_H
#define	SIMULATION_H

/* 
 * File:   Simulation.h
 * Author: Ying Lu 
 *
 * Created on September 3, 2014
 */

#include <vector>
#include "Body_sphere.h"
#include "CollisionDetection.h"
#include "Contact.h"
#include <time.h>
#include <cmath>
#include <sstream>
#include <string>


typedef struct Simulation{
    Simulation(): Step_Size(0.01), Step_Counter(0), Num_Bodies(0), Num_Spheres(0), Num_Contacts(0)
    {
    }

    double Step_Size; 
    int Step_Counter; 
    int Num_Bodies;
    int Num_Spheres; 
    vector<Sphere> Sphere_Bodies;
    int Num_Contacts;
    vector<Contact> Contacts;
}Simulation;

bool sim_addSphere(Simulation &sim, Sphere &sphere);
bool sim_removeSphere(Simulation &sim, int bodyID); 

void sim_step(Simulation &sim);
void sim_printBodies(Simulation &sim);
void sim_printPositions(Simulation &sim);

// auxiliary function: convert double to string 
string d2s(double d);

#endif	/* SIMULATION_H */

