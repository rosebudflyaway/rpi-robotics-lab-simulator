/* 
 * File:   Contact.cpp
 * Author: Jedediyah Williams
 * 
 * Created on November 10, 2012, 11:08 PM
 */

#include "Contact.h"
#include <string>
using namespace arma;

Contact::Contact () { 
}
Contact::Contact(   int contact_ID,
                    int body1_type,
                    int body2_type,
                    int body1,
                    int body2,
                    mat normal,
                    mat tangent,
                    vec r1,
                    mat r2,
                    mat psi,
                    char *collision_type ) {
        
    this->contact_ID = contact_ID;
    this->body1_type = body1_type;
    this->body2_type = body2_type; 
    this->body1 = body1;
    this->body2 = body2;
    this->normal = normal; 
    this->tangent = tangent;
    this->r1 = r1;
    this->r2 = r2;  
    this->psi = psi;
    this->collision_type = collision_type; 
}

Contact::Contact(   int contact_ID,
                    int body1_type,
                    int body2_type,
                    int body1,
                    int body2,
                    mat normal,
                    mat tangent,
                    vec r1,
                    mat r2,
                    mat psi ) {
        
    this->contact_ID = contact_ID;
    this->body1_type = body1_type;
    this->body2_type = body2_type; 
    this->body1 = body1;
    this->body2 = body2;
    this->normal = normal; 
    this->tangent = tangent;
    this->r1 = r1;
    this->r2 = r2;  
    this->psi = psi;
    std::string colli_type_string = "body";
    char* colli_type =  (char*) colli_type_string.c_str();
    collision_type = colli_type; 
}

Contact::Contact(const Contact& orig) {
}

Contact::~Contact() {
}

void Contact::print() {
    cout << "contact ID: " << contact_ID << endl; 
    cout << "Body 1: " << body1 << endl;
    cout << "Body 2: " << body2 << endl;
    cout << "Normal: ";  normal.print();
    cout << "Tangent: "; tangent.print();
    cout << "r1: ";  r1.print(); 
    cout << "r2: ";  r2.print(); 
    cout << "psi: ";  psi.print(); 
    cout << "Collision type: " << collision_type << endl; 
}

