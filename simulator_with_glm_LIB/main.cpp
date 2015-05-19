/* 
 * File:   main.cpp
 * Author: Ying Lu 
 *
 * Created on November 2nd, 2014
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include "Body_sphere.h"
#include "Simulation.h" 

using namespace std;

int main( ) 
{
    // number of spheres N = 100;
    int N = 100;       int MAX_STEP = 100;
    double mass = 0.1;  double radius = 0.09;
    double px, py, pz;
    double P[N][3];
    glm::vec3 pos, prev_pos;
    int i, j;

    // Initialize simulation structure
    Simulation sim;
    sim.Step_Size = 0.005;
    sim.Step_Counter = 0;
    sim.Num_Bodies = 0;
    sim.Num_Spheres = 0;
    sim.Num_Contacts = 0;

    for(i=0; i<N; i++)
        for(j=0; j<3; j++)
            P[i][j] = 0.0;
    
    // add body
    for(i=0; i<N; i++)
    {
        Sphere sphere;
        sphere.Radius = radius; 
        sphere.Mass = mass;
        setMassInertiaMatrix(sphere);
        setQuaternion(sphere, 1.0, 0.0, 0.0, 0.0);
        setL_vel(sphere, 0.0, 0.0, 0.0);
        setA_vel(sphere, 0.0, 0.0, 0.0);
        setFext(sphere, 0.0, 0.0, -9.8*mass);
        setText(sphere, 0.0, 0.0, 0.0);
        sphere.Mu = 0.55;
        sphere.IsStaticBody = false;
        sphere.Bounding_Radius = 1.1*radius;

        bool checkSphere = true;
        while (checkSphere)
        {
            checkSphere = false;
            // [-1.8, 1.8] --> [-18, 18]  --> [0, 36]
            px = ((rand()%37) - 18.0) * 0.1;
            py = ((rand()%37) - 18.0) * 0.1;
            // [0.5, 4.0] --> [5, 40]  --> [0, 35]
            pz = ((rand()%36) + 5.0) * 0.1;
            pos = glm::vec3(px, py, pz);
            for (j=0; j<i; j++)
            {
                prev_pos = glm::vec3(P[j][0], P[j][1], P[j][2]);
                double dist = glm::length(pos - prev_pos);
                if(dist - 2 * radius < 0.2)
                {
                    checkSphere = true;
                }
            }
        }
        for(j=0; j<3; j++)
            P[i][j] = pos[j];
        setPosition(sphere, px, py, pz);
        sim_addSphere(sim, sphere);
    }

    /*
    for(i=0; i<N; i++)
    {
        for(j=0; j<3; j++)
        {
            cout << P[i][j] << ", ";
        }
        cout << endl;
    }
    */

    cout << "Start Simulation ..." << endl;
    sim_step(sim);

    for (i=0; i<MAX_STEP; i++)
    {
        cout <<"Step : " << i << endl;
        sim_step(sim);
    }
    cout << "Simulation DONE." << endl;
    sim_printBodies(sim);
    return 0;
}

