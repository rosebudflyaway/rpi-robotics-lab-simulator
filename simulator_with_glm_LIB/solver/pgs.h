#ifndef PGS_H
#define PGS_H
/* 
 * File:     pgs.h
 * Author:   Ying Lu
 *
 * created on November 2nd, 2014
 */

#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <cmath>
#include <vector>

using namespace std;


typedef struct Solution{
    // constructor 
    Solution():prob_size(10000), max_iter(200), toler(0.0001), iter(0), error(0.0)
    {
    }

    // input variables
    int prob_size;
    int max_iter; 
    double toler;

    // The output variables 
    vector<double> xsoln;
    int iter;
    double error;
    vector<double> convergence; // convergence at each iteration 
}Solution;

void pgs(Solution &solution, vector<double> A, vector<double> b, vector<double> x0);
double vec_multiply_vec(vector<double> v1, vector<double> v2);
vector<double> evaluate_LCP(vector<double> A, vector<double> x, vector<double> b);

#endif
