#include <iostream>
#include "pgs.h"
#include <string>
#include <cmath>
#include <glm/glm.hpp>

using namespace std;
 
void pgs(Solution &solution, vector<double> A, vector<double> b, vector<double> x0)
{
    // This function would update the newNU property of solution, as well as iter and error 
    int maxIter = solution.max_iter;
    double toler = solution.toler;
    int prob_size = solution.prob_size;
    int iter = 0;
    double error = 1e12;

    // first convert A to problem_size X problem_size
    double matA[prob_size][prob_size];
    int i, j;
    for(i=0; i<prob_size; i++)
    {
        for(j=0; j<prob_size; j++)
        {
            matA[i][j] = A[i * prob_size + j];
        }
    }

    vector<double> x;
    vector<double> convergence;
    x = x0;
    double old_xi, xi, old_error;
    double Aix, Aii;
    double ri, dx;
    double project_xi, project_dxi;
    double eps = 1e-1;
    vector<double> Arow;

    while(iter <= maxIter)
    {
        iter = iter + 1;
        dx = 0.0;
        for (i = 0; i< prob_size; i++)
        {
            old_xi = x[i];

            Arow.clear();
            for(j=0; j<prob_size; j++)
                Arow.push_back(matA[i][j]);

            Aix = vec_multiply_vec(Arow, x); 
            ri  = b[i] + Aix;
            Aii = matA[i][i] + eps;

            project_xi = old_xi - (ri / Aii);
            xi = project_xi > 0.0 ? project_xi : 0.0;

            // check this update is valid
            x[i] = xi;

            // update dx
            project_dxi = abs(xi - old_xi);

            if(dx < project_dxi)
                dx = project_dxi;
        } // for loop
        old_error = error;
        vector<double> y = evaluate_LCP(A, x, b);
        error =  vec_multiply_vec(x, y);
        convergence.push_back(error);
        if(abs(error-old_error) / abs(old_error) < toler)
            break;
        if(abs(error) < toler)
            break;
        if(dx < eps)
            break;
    } // while loop

    solution.iter = iter;
    solution.error = error;
    solution.convergence = convergence;
    solution.xsoln = x;
}

double vec_multiply_vec(vector<double> v1, vector<double> v2)
{
    double result = 0.0;
    if(v1.size() != v2.size())
    {
        cout << "The two vector don't have equal length" << endl;
        return result; 
    }

    for(int i=0; i<v1.size(); i++)
    {
        result += v1[i] * v2[i];
    }
    return result;
}

vector<double> evaluate_LCP(vector<double> A, vector<double> x, vector<double> b)
{
    int prob_size = x.size();
    vector<double> y;
    for(int i=0; i<prob_size; i++)
    {
        double current = 0.0;
        for(int j=0; j<prob_size; j++)
        {
            current +=  A[i*prob_size +j] * x[j];
        }

        current += b[i];
        if(current <=0.0 )
            current = -1.0*current;
        y.push_back(current);
    }
    return y;
}
