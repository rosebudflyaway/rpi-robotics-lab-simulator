/* 
 * File:   Contact.cpp
 * Author: Ying Lu 
 * 
 * Created on November 3, 2014
 */

#include "Contact.h"
#include <iostream>
#include <string>
using namespace std;


void printContacts(Contact c) 
{
    cout << "contact ID: " << c.contact_ID << endl; 
    cout << "Body 1: " << c.body1 << endl;
    cout << "Body 2: " << c.body2 << endl;
    cout << "Normal: " << "[" << c.normal[0] << ", " << c.normal[1] << ", " << c.normal[2] << "]"<< endl; 
    cout << "Tangent: " << "[" << c.tangent[0] << ", " << c.tangent[1] << ", " << c.tangent[2] << "]"<< endl; 
    cout << "r1: " << "[" << c.r1[0] << ", " << c.r1[1] << ", " << c.r1[2] << "]"<< endl; 
    cout << "r2: " << "[" << c.r2[0] << ", " << c.r2[1] << ", " << c.r2[2] << "]"<< endl; 
    cout << "psi: " << c.psi << endl; 
}

