/* 
 * File:   Body_sphere.cpp
 * Author: Ying Lu 
 * 
 * Created on Novermber 2nd, 2014 
 */

#include "Body_sphere.h"
#include <glm/glm.hpp>
#include <cmath>
#include <stdlib.h>

using namespace std; 

void setMassInertiaMatrix(Sphere &sphere)
{
    glm::mat3 mass_matrix = glm::mat3(1.0f);
    glm::mat3 mass_inverse_matrix = glm::mat3(1.0f);
    glm::mat3 inertia_matrix = glm::mat3(1.0f);

	int i, j;
	for(i=0; i<3; i++)
	{
	   for(j=0; j<3; j++)
	    {
			sphere.Mass_Inertia_Matrix[i][j] = 0.0;
	    }
	}
    for(i=0; i<3; i++)
    {
        mass_matrix[i][i] = sphere.Mass;
        mass_inverse_matrix[i][i] = 1.0/sphere.Mass;
        inertia_matrix[i][i] = 2.0/5.0*sphere.Mass * sphere.Radius * sphere.Radius; 
        sphere.Mass_Inertia_Matrix[i][i] = sphere.Mass;
        sphere.Mass_Inertia_Matrix[i+3][i+3] = 2.0/5.0 * sphere.Mass * sphere.Radius * sphere.Radius;
    }


    sphere.Mass_Matrix = mass_matrix;
    sphere.Mass_Inverse_Matrix = mass_inverse_matrix;
    sphere.Inertia_Matrix = inertia_matrix;
}
 
void setPosition(Sphere &sphere, double x, double y, double z) {
    sphere.U[0] = x;  sphere.U[1] = y;  sphere.U[2] = z; 
}
void setQuaternion(Sphere &sphere, double a, double i, double j, double k) {
    sphere.Quat[0]=a;  sphere.Quat[1]=i;  sphere.Quat[2]=j;  sphere.Quat[3]=k;
}
void setR_rot(Sphere& sphere, glm::mat3 r) { sphere.R_rot = r; }
void setL_vel( Sphere& sphere, double x, double y, double z) {
    sphere.L_vel[0]=x;  sphere.L_vel[1]=y;  sphere.L_vel[2]=z; 
}
void setA_vel(Sphere& sphere, double x, double y, double z) {
    sphere.A_vel[0]=x; sphere.A_vel[1]=y; sphere.A_vel[2]=z;
}
void setFext(Sphere& sphere, double Fx, double Fy, double Fz) {
    sphere.Fext[0]=Fx; sphere.Fext[1]=Fy; sphere.Fext[2]=Fz; 
}
void setText(Sphere& sphere, double Tx, double Ty, double Tz ) {
    sphere.Text[0]=Tx; sphere.Text[1]=Ty; sphere.Text[2]=Tz;
}

void applyAext(Sphere &sphere, double dt)
{
    // v = v + F / m  * t
    sphere.L_vel += (float)(1.0/sphere.Mass) * (sphere.Fext)  * (float)dt;
    //sphere.L_vel[2] += sphere.Fext[3]* dt; 
}
// Uses current velocities to update position vector U and quaternion Quat. 
void stepDynamics(Sphere& sphere, double dt) {
    /*
    glm::vec3 U = sphere.U;
    glm::vec3 L_vel = sphere.L_vel;
    glm::vec3 A_vel = sphere.A_vel;
    */
    glm::vec4 Quat = sphere.Quat;

    // Update position
    //U += dt * L_vel;
    glm::vec3 U = sphere.U;
    glm::vec3 L_vel = sphere.L_vel;
    L_vel *= dt;
    U += L_vel;
    sphere.U = U;

    // Update rotation 
    // glm::vec3 w = sphere.A_vel * dt;
    glm::vec3 w; 
    glm::vec3 A_vel = sphere.A_vel;
    A_vel *= dt;
    w = A_vel;

    double wn = glm::length(w);              // Normalized
    if (wn != 0) {
        // Quat multiply current Quat
        glm::vec4 q = Quat; 
        glm::vec4 r = glm::vec4(0.0);
        r[0] = -cos(wn/2);
        r[1] = (w[0]/wn)*sin(wn/2);
        r[2] = (w[1]/wn)*sin(wn/2);
        r[3] = (w[2]/wn)*sin(wn/2);
        
        glm::vec4 v = glm::vec4(0.0);
        v[0] = q[0]*r[0] - q[1]*r[1] - q[2]*r[2] - q[3]*r[3]; 
        v[1] = q[0]*r[1] + r[0]*q[1] + q[2]*r[3] - q[3]*r[2];
        v[2] = q[0]*r[2] + r[0]*q[2] + q[3]*r[1] - q[1]*r[3];
        v[3] = q[0]*r[3] + r[0]*q[3] + q[1]*r[2] - q[2]*r[1]; 
        

       // Quat = v/norm(v,2); // Remember to normalize. 
       Quat = glm::normalize(v);
       sphere.Quat = Quat; 
    }
}

void sphere_print(Sphere &sphere) {
    cout << "------------------------\n"; 
    //    cout << ":: Body: " << sphere.Name << endl;
    cout << ":: Mass: " << sphere.Mass << endl; 
    cout << ":: Radius: " << sphere.Radius << endl; 
    cout << ":: U: [" << sphere.U[0] << ", " << sphere.U[1] << ", " << sphere.U[2] << "]" << endl;
    cout << ":: Quat: [" << sphere.Quat[0] << ", " << sphere.Quat[1]<<", "<< sphere.Quat[2]<<", "<< sphere.Quat[3]<<"]"<<endl;
    cout << ":: L_vel: [" << sphere.L_vel[0]<<", "<< sphere.L_vel[1]<<", "<< sphere.L_vel[2] << "]" << endl;
    cout << ":: A_vel: [" << sphere.A_vel[0]<<", "<< sphere.A_vel[1]<<", "<< sphere.A_vel[2] << "]" << endl;
    cout << ":: Fext: [" << sphere.Fext[0]<<", "<< sphere.Fext[1]<<", "<< sphere.Fext[2] <<"]" << endl;
    cout << ":: Text: [" << sphere.Text[0]<<", "<< sphere.Text[1]<<", "<< sphere.Text[2] <<"]" << endl;
    cout << ":: Mu: " << sphere.Mu << endl; 
    cout << ":: IsStatic: " << sphere.IsStaticBody << endl;
}

void sphere_printPosition(Sphere &sphere) {
    cout << "Position is: " << sphere.U[0] << ", "  << sphere.U[1] << ", "  << sphere.U[2] << endl;
    //printf("%12.4f, %12.4f, %12.4f\n", sphere.U[0], sphere.U[1], sphere.U[2]);
}
