/* 
 * File:   CollisionDetection.cpp
 * Author: Ying Lu 
 * 
 * Created on November 3, 2014
 */

#include "CollisionDetection.h"
#include <iostream>
#include <glm/glm.hpp>
#include <cmath>

#define GROUND -1
#define SPHERE  1
using namespace std;


// Assumes that n is normalized 
glm::vec3 arbitraryTangent(glm::vec3 n) {

    glm::vec3 Y = glm::vec3(0.0);   Y[1] = 1.0;
    glm::vec3 Z = glm::vec3(0.0);   Z[2] = 1.0;
    glm::vec3 T;

    if (abs(glm::dot(n, Z)) < 0.7)
        T = glm::cross(n, Z);
    else 
        T = glm::cross(n, Y);

    return glm::normalize(T);
}

//void findContacts(Contact *Contacts, Body_sphere *spheres, int &num_bodies, int &num_spheres, int &num_unions, int &num_contacts) 
void findContacts(vector<Contact> &contacts, vector<Sphere> &spheres, int &num_contacts, int &num_spheres) 
{
    //cout << "Collision detection on " << num_spheres << " spheres..." << endl; 
    
    int cID = 0;         // The contact ID 
    int bID = 1;         // The body ID, for indexing; NOTE: here bID starts with 1
    
    // Init body ids
    for (int s=0; s<num_spheres; s++ ) 
    {  
        spheres[s].BodyIndex = -1; 
        spheres[s].ContactCount = 0;
    }
    
    // SPHERE-GROUND collision detection
    for (int s = 0; s < num_spheres; s++) 
    {
        if (!spheres[s].IsStaticBody) 
        {

            glm::vec3 U = spheres[s].U;
            double Radius = spheres[s].Radius;
            double psi = U[2] - Radius; // psi=height-radius
            if (psi > 0.5)
                continue; 
            glm::vec3 n = glm::vec3(0.0);
            n[2] = 1.0;               // Normal to sphere is always up (+z direction)
            glm::vec3 t = arbitraryTangent(n);

            glm::vec3 r1 = n;                                                           // r1 for ground
            glm::vec3 r2 = (float)(-1.0*Radius) * n;
            // glm::vec3 r2 = glm::vec3(-n[0]*Radius, -n[1]*Radius, -n[2]*Radius);      
            Contact c; 

            // update the new contact structure here
            c.contact_ID = cID;
            c.body1_type = GROUND;
            c.body2_type = SPHERE;
            c.body1 = -250;  // for ground 
            c.body2 = s;
            c.normal = n;
            c.tangent = t;
            c.r1 = r1;
            c.r2 = r2;
            c.psi = psi;
            cID++;

            contacts.push_back(c);
            num_contacts++;
            spheres[s].ContactCount++; 

            if (spheres[s].BodyIndex < 0) 
            {
                spheres[s].BodyIndex = bID;
                bID++;
            }
        } // if dynamic
    } // for loop
    
    // SPHERE-LEFT-RIGHT (in box) collision detection
    for (int s = 0; s < num_spheres; s++) 
    {
        if (!spheres[s].IsStaticBody) 
        {
            glm::vec3 U = spheres[s].U;
            double Radius = spheres[s].Radius;
            double left_gap = 0.0;   double right_gap = 0.0;  double psi = 0.0;
            glm::vec3 n = glm::vec3(0.0);
            left_gap = U[1] - Radius + 2.0;    // left_bound - (-2) 
            right_gap = 2.0 - (U[1] + Radius); // 2 - right_bound

            if(left_gap > 0.5 && right_gap > 0.5)
                continue;
            if(left_gap < 0.5) {
                psi = left_gap;
                n[1] = 1.0;
            }
            else {
                psi = right_gap;
                n[1] = -1.0;
            }
            glm::vec3 t = arbitraryTangent(n);
            glm::vec3 r1 = n; 
            glm::vec3 r2 = (float)(-1.0*Radius) * n;
            //r2 = -n * Radius;

            Contact c;
            // update the new contact structure here
            c.contact_ID = cID;
            c.body1_type = GROUND;
            c.body2_type = SPHERE;
            c.body1 = -250;  // for ground 
            c.body2 = s;
            c.normal = n;
            c.tangent = t;
            c.r1 = r1;
            c.r2 = r2;
            c.psi = psi;
            cID++;

            //contacts[num_contacts++] = c;
            contacts.push_back(c);
            num_contacts++;
            spheres[s].ContactCount++; 
            
            if (spheres[s].BodyIndex < 0) 
            {
                spheres[s].BodyIndex = bID;
                bID++;
                //num_bodies++;
            }

        } // if 
    } // for loop
    
    // SPHERE-FRONT-BACK (in box) collision detection
    for (int s = 0; s < num_spheres; s++) 
    {
        if (!spheres[s].IsStaticBody) 
        {
            glm::vec3 U = spheres[s].U;
            double Radius = spheres[s].Radius;
            double back_gap = 0.0;   double front_gap = 0.0;  double psi = 0.0;
            glm::vec3 n = glm::vec3(0.0);
            back_gap = U[0] - Radius + 2.0;     // back_bound - (-2) 
            front_gap = 2.0 - (U[0] + Radius); // 2 - front_bound

            if(back_gap > 0.5 && front_gap > 0.5)
                continue;
            if(back_gap < 0.5) {
                psi = back_gap;
                n[0] = 1.0;
            }
            else {
                psi = front_gap;
                n[0] = -1.0;
            }

            glm::vec3 t = arbitraryTangent(n);
            glm::vec3 r1 = n; 
            glm::vec3 r2 = (float)(-1*Radius) * n;

            Contact c;
            // update the new contact structure here
            c.contact_ID = cID;
            c.body1_type = GROUND;
            c.body2_type = SPHERE;
            c.body1 = -250;  // for ground 
            c.body2 = s;
            c.normal = n;
            c.tangent = t;
            c.r1 = r1;
            c.r2 = r2;
            c.psi = psi;
            cID++;

            contacts.push_back(c);
            num_contacts++;
            spheres[s].ContactCount++; 

            if (spheres[s].BodyIndex < 0) 
            {
                spheres[s].BodyIndex = bID;
                bID++;
            }
        }  // if 
    } // for

    // SPHERE-SPHERE collision detection
    for (int s1=0; s1<num_spheres; s1++) 
    {
        for (int s2=s1+1; s2<num_spheres; s2++) 
        {
            if ( spheres[s1].IsStaticBody && spheres[s2].IsStaticBody)
                continue; 
            double Radius1 = spheres[s1].Radius;
            double Radius2 = spheres[s2].Radius;
            glm::vec3 U1 = spheres[s1].U;
            glm::vec3 U2 = spheres[s2].U;
            
            // Check bounding sphere
            glm::vec3 n = U2 - U1;
            double n_norm = glm::length(n);
            double psi = 0.0;
            psi = n_norm - Radius1 - Radius2; 
            if ( psi< spheres[s1].Bounding_Radius - Radius1 + spheres[s2].Bounding_Radius - Radius2 ) 
            {
                n = glm::normalize(n);

                glm::vec3 t = arbitraryTangent(n);
                glm::vec3 r1 =  n*(float)Radius1;
                glm::vec3 r2 = -n*(float)Radius2;

                Contact c;
                // update the new contact structure here
                c.contact_ID = cID;
                c.body1_type = SPHERE;
                c.body2_type = SPHERE;
                c.body1 = s1;  // for ground 
                c.body2 = s2;
                c.normal = n;
                c.tangent = t;
                c.r1 = r1;
                c.r2 = r2;
                c.psi = psi;
                cID++;
                contacts.push_back(c);
                num_contacts++;

                if ( !spheres[s1].IsStaticBody ) 
                {
                    spheres[s1].ContactCount++;  
                    if (spheres[s1].BodyIndex < 0) {
                        spheres[s1].BodyIndex = bID;
                        bID++;
                        //num_bodies++;
                    }
                }
                if ( !spheres[s2].IsStaticBody ) 
                {
                    spheres[s2].ContactCount++;  
                    if (spheres[s2].BodyIndex < 0) {
                        spheres[s2].BodyIndex = bID;
                        bID++;
                        //num_bodies++;
                    }
                }

            } // contact
        } // inward for loop
    } // outward for loop

} // end of function findContacts


