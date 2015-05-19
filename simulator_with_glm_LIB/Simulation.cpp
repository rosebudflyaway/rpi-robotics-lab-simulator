/* 
 * File:   Simulation.cpp
 * Author: Ying Lu 
 * 
 * Created on September 3, 2014
 */

#include <iostream>
#include "Body_sphere.h"
#include "Simulation.h"
#include "CollisionDetection.h"
#include "lcpDynamics.h"

#define DEBUG 1


// Add SPHERE
bool sim_addSphere(Simulation &sim, Sphere &sphere) 
{
    sim.Num_Bodies++;
    sim.Num_Spheres++;
    sim.Sphere_Bodies.push_back(sphere);
    return true;
}

// REMOVE SPHERE
bool sim_removeSphere(Simulation &sim, int bodyID) 
{
    sim.Num_Bodies--;
    sim.Num_Spheres--;
    sim.Sphere_Bodies.erase(sim.Sphere_Bodies.begin() + bodyID);
    return true;
}


void sim_step(Simulation &sim) 
{ 
    // Collision detection 
    sim.Step_Counter++; 
    // clear contacts info before each collision detection 
    sim.Contacts.clear();
    sim.Num_Contacts = 0;
    findContacts(sim.Contacts, sim.Sphere_Bodies,  sim.Num_Contacts, sim.Num_Spheres);


    vector<double> newNU;
    newNU = lcpDynamics(sim.Contacts, sim.Sphere_Bodies, sim.Num_Contacts, sim.Num_Spheres, sim.Step_Size);


    /*
    for(int tmp =0; tmp < newNU.size(); tmp++)
        cout << newNU[tmp] << ", ";
    cout << endl;
    */

    

    int bID; 
    // Spheres
    for (int i=0; i<sim.Num_Spheres; i++) 
    {   
        if ( !sim.Sphere_Bodies[i].IsStaticBody ) 
        {
            if ( sim.Sphere_Bodies[i].ContactCount > 0 ) 
            { 
                bID = sim.Sphere_Bodies[i].BodyIndex;  
                setL_vel(sim.Sphere_Bodies[i],  newNU[6*bID-6], newNU[6*bID-5], newNU[6*bID-4]);
                setA_vel(sim.Sphere_Bodies[i],  newNU[6*bID-3], newNU[6*bID-2], newNU[6*bID-1]);
                // update the quaternion and normalize it!!!
                stepDynamics(sim.Sphere_Bodies[i], sim.Step_Size);
            } 
            else 
            {
                applyAext(sim.Sphere_Bodies[i], sim.Step_Size); 
                stepDynamics(sim.Sphere_Bodies[i], sim.Step_Size);
            }
        }
    }  
}

void sim_printBodies(Simulation &sim) 
{
    for (int i=0; i<sim.Num_Spheres; i++) 
    {   
        sphere_print(sim.Sphere_Bodies[i]);
    }
}

void sim_printPositions(Simulation &sim) 
{
    
    for (int i=0; i<sim.Num_Spheres; i++) 
    {   // Draw all Spheres
        sphere_printPosition(sim.Sphere_Bodies[i]);
    }
}
 

// Convert a double to a string
string d2s(double d) {
    std::stringstream ss;
    ss << d;
    return ss.str();
}


