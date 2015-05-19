#ifndef CONTACT_H
#define	CONTACT_H

#include <glm/glm.hpp>
/* 
 * File:   Contact.h
 * Author: Ying Lu 
 *
 * Created on November 3, 2014
 */


typedef struct Contact {
    Contact():contact_ID(0), body1_type(-1), body2_type(-1), body1(-250), body2(-250), normal(glm::vec3(1.0)), tangent(glm::vec3(1.0)), r1(glm::vec3(1.0)), r2(glm::vec3(-1.0)), psi(10.0)
    {
    }
    // property fields inside contact
    int contact_ID;
    int body1_type;
    int body2_type;
    int body1;
    int body2;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 r1;
    glm::vec3 r2;
    double psi;
}Contact;

void printContacts(Contact c);

    
    


#endif	/* CONTACT_H */

