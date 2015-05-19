/* 
 * File:   main.cpp
 * Author: Jedediyah Williams
 *
 * Created on November 10, 2012, 4:34 PM
 * Modified on October 22, 2012, 3:07 PM
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>



#include "Simulation.h" 
#include "SimulatorDefenitions.h" //TODO: change it to SimulatorDefinitions.h 
using namespace std;

// Main routine.
int main( ) 
{
    // define a simulation
    static Simulation SIM;

    // number of spheres N = 100;
    int N = 100;
    int MAX_STEP = 500;
    int i = 0;
    int j = 0;

    double mass = 0.1;
    double radius = 0.09;
    double pos[N][3];
    double vel[N][6];
    double v1, v2, v3, v4, v5, v6;
    char ch;

    // TODO Change this to get the directory of 
    ifstream posFile("/home/ying/Documents/lockheed/rpi-robotics-lab-simulator/profiling_sphere/pos.txt", ios::in);
    while(posFile.good())
    {
        posFile>> v1 >> ch >> v2 >> ch >> v3;
        //cout << v1 << ", " << v2 << ", " << v3 << endl;
        pos[i][0] = v1;
        pos[i][1] = v2;
        pos[i][2] = v3;
        i++;
        if(i == N)
            break;
    }
    posFile.close();

    i=0;
    ifstream velFile("/home/ying/Documents/lockheed/rpi-robotics-lab-simulator/profiling_sphere/vel.txt", ios::in);
    while(velFile.good())
    {
        velFile>> v1 >> ch >> v2 >> ch >> v3 >> ch >> v4 >> ch >> v5 >> ch >> v6;
        //cout << v1 << ", " << v2 << ", " << v3 << ", " << v4 << ", " << v5 << ", " << v6 << endl;
        vel[i][0] = v1;
        vel[i][1] = v2;
        vel[i][2] = v3;
        vel[i][3] = v4;
        vel[i][4] = v5;
        vel[i][5] = v6;
        vel[i][2] = v2 - 1.6;
        i++;
        if(i==N)
            break;
    }
    velFile.close();


    // add body
    for(i=0; i<N; i++)
    {
        Body_sphere sphere;
        sphere.setName("sphere");
        sphere.setRadius(radius);
        sphere.setMass(mass);
        sphere.setPosition(pos[i][0], pos[i][1], pos[i][2]);
        sphere.setQuaternion(1.0, 0.0, 0.0, 0.0);
        sphere.setVelocity(vel[i][0], vel[i][1], vel[i][2], vel[i][3], vel[i][4], vel[i][5]);
        sphere.setFext(0.0, 0.0, -9.8*mass, 0.0, 0.0, 0.0);
        sphere.setMu(0.5);
        sphere.setStatic(false);
        sphere.setBoundingRadius(1.1*radius);
        SIM.addBody(sphere);
    }

    SIM.setRun(true); 
    cout << SIM.num_spheres() << endl;  
    //cout << "Print body information before start simulation" << endl;
    //SIM.printBodies();
    cout << "Start Simulation ..." << endl;


    for (i=0; i<MAX_STEP; i++)
    {
        SIM.step();
    }
    cout << "Simulation DONE." << endl;
    //SIM.printBodies();
    return 0;
}

