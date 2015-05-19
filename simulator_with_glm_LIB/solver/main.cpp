/* 
 * File:   main.cpp
 * Author: Ying Lu 
 *
 * Created on November 2nd, 2014
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "pgs.h"
using namespace std;

// Main routine.
int main( ) 
{
    int i = 0;
    int j = 0;

    double v1, v2;
    char ch;
    vector<double> Avec;
    vector<double> q;
    vector<double> soln;

    ifstream in("/home/ying/Documents/lockheed/RPISim_cpp_Jed/glm_test/solver/MM.txt", ios::in);
    int lineNum = 0;
    while(in.good())
    {
        lineNum++; 
        //cout << "The line number is: " << lineNum << endl;

        if(lineNum >108)
            break;

        for(i=0; i<107; i++)
        {
            in >> v1 >> ch;
            Avec.push_back(v1);
        }
        in >> v1;
        Avec.push_back(v1);
    }
    in.close();


    lineNum=0;
    ifstream qFile("/home/ying/Documents/lockheed/RPISim_cpp_Jed/glm_test/solver/q_soln.txt", ios::in);
    while(qFile.good())
    {
        lineNum++;
        if(lineNum > 108)
            break;
        qFile>> v1 >> ch >> v2;
        //cout << v1 << ", " << v2 << ", " << v3 << ", " << v4 << ", " << v5 << ", " << v6 << endl;
        q.push_back(v1);
        soln.push_back(v2);
    }
    qFile.close();


    /*
    cout << "The length of Avec vector is: " << Avec.size() << endl;
    cout << "The length of qvec vector is: " << q.size() << endl;
    cout << "The length of soln_vec vector is: " << soln.size() << endl;
    */


    Solution solution;
    solution.prob_size =  108;
    solution.max_iter = 200;
    solution.toler = 1e-12;
    
    vector<double> x0;
    for(i=0; i<solution.prob_size; i++)
        x0.push_back(0.0);

    pgs(solution, Avec, q, x0);

    cout << "The total iteration number is: "  << solution.iter << endl;
    cout << "The error is: "  << solution.error << endl;

    vector<double> x = solution.xsoln;

    cout << "The soultion size is: "  << x.size() << endl;
    for(i=0; i<x.size(); i++)
        cout << x[i] << ", ";
    cout << endl;

    return 0;
}

