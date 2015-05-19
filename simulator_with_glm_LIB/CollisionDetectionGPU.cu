/* 
 * File:   CollisionDetectionGPU.cpp
 * Author: Ying Lu
 * GPU Extension by Dave Kotfis
 * 
 * Created on November 11, 2014
 */


#include "CollisionDetectionGPU.h"

#include <cuda.h>

#define GROUND -1
#define SPHERE  1

__host__ __device__ glm::vec3 arbitrary_tangent(glm::vec3 n) {

  glm::vec3 Y = glm::vec3(0.0);   Y[1] = 1.0;
  glm::vec3 Z = glm::vec3(0.0);   Z[2] = 1.0;
  glm::vec3 T;

  if (abs(glm::dot(n, Z)) < 0.7)
    T = glm::cross(n, Z);
  else
    T = glm::cross(n, Y);

  return glm::normalize(T);
}

__host__ __device__ void collide_sphere_plane(Sphere sphere, int side, Contact contact) {

}

__device__ void collide_sphere_sphere(Sphere sphere1, Sphere sphere2, Contact contact) {
  if ( sphere1.IsStaticBody && sphere2.IsStaticBody)
    return; 
  double Radius1 = sphere1.Radius;
  double Radius2 = sphere2.Radius;
  glm::vec3 U1 = sphere1.U;
  glm::vec3 U2 = sphere2.U;
            
  // Check bounding sphere
  glm::vec3 n = U2 - U1;
  double n_norm = glm::length(n);
  double psi = 0.0;
  psi = n_norm - Radius1 - Radius2; 
  if ( psi< sphere1.Bounding_Radius - Radius1 + sphere2.Bounding_Radius - Radius2 ) {
    n = glm::normalize(n);

    glm::vec3 t = arbitrary_tangent(n);
    glm::vec3 r1 =  n*(float)Radius1;
    glm::vec3 r2 = -n*(float)Radius2;

    // update the new contact structure here
    //contact.contact_ID = cID;
    contact.body1_type = SPHERE;
    contact.body2_type = SPHERE;
    //contact.body1 = sphere1;
    //contact.body2 = sphere2;
    contact.normal = n;
    contact.tangent = t;
    contact.r1 = r1;
    contact.r2 = r2;
    contact.psi = psi;
    //cID++;

    if ( !sphere1.IsStaticBody ) 
      {
        sphere1.ContactCount++;  
        if (sphere1.BodyIndex < 0) {
          //sphere1.BodyIndex = bID;
          //bID++;
        }
      }
    if ( !sphere2.IsStaticBody ) 
      {
        sphere2.ContactCount++;  
        if (sphere2.BodyIndex < 0) {
          //sphere2.BodyIndex = bID;
          //bID++;
        }
      }
  }
}

__global__ void collide_spheres(Sphere* device_spheres, Contact* device_contacts, int num_spheres) {
  //TODO; How can we improve memory coherency here?
  int idx = blockDim.x * blockIdx.x + threadIdx.x;
  int s1 = idx / num_spheres;
  int s2 = idx % num_spheres;

  if (s1 < num_spheres && s2 < num_spheres) {
    collide_sphere_sphere(device_spheres[s1], device_spheres[s2], device_contacts[idx]);
  }
}

extern "C" void findContactsGPU(Contact* contacts, Sphere* spheres, int num_contacts, int num_spheres) 
{
    int cID = 0;         // The contact ID 
    int bID = 1;         // The body ID, for indexing; NOTE: here bID starts with 1

    //Package up data and send to the GPU
    Contact* device_contacts;
    cudaMalloc((void**)&device_contacts, num_contacts*sizeof(Contact));

    Sphere* device_spheres;
    cudaMalloc((void**)&device_spheres, num_spheres*sizeof(Sphere));
    cudaMemcpy(device_spheres, spheres, num_spheres*sizeof(Sphere), cudaMemcpyHostToDevice);

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
            glm::vec3 t = arbitrary_tangent(n);

            glm::vec3 r1 = n;                                                           // r1 for ground
            glm::vec3 r2 = (float)(-1.0*Radius) * n;
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

            //contacts.push_back(c);
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
            glm::vec3 t = arbitrary_tangent(n);
            glm::vec3 r1 = n; 
            glm::vec3 r2 = (float)(-1.0*Radius) * n;

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
            //contacts.push_back(c);
            num_contacts++;
            spheres[s].ContactCount++; 
            
            if (spheres[s].BodyIndex < 0) 
            {
                spheres[s].BodyIndex = bID;
                bID++;
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

            glm::vec3 t = arbitrary_tangent(n);
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

            //contacts.push_back(c);
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
    // TODO: Replace loops with kernel call to collide_spheres
    for (int s1=0; s1<num_spheres; s1++) 
    {
        for (int s2=s1+1; s2<num_spheres; s2++) 
        {
          Contact c;
          //collide_sphere_sphere(spheres[s1], spheres[s2], c);

          //contacts.push_back(c);
          num_contacts++;

        } // inward for loop
    } // outward for loop

    //Copy contact data back from GPU
    cudaMemcpy(contacts, device_contacts, num_contacts*sizeof(Contact), cudaMemcpyDeviceToHost);

    //Cleanup CUDA
    cudaFree(device_spheres);
    cudaFree(device_contacts);

} // end of function findContacts


