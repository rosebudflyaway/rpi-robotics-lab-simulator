/* 
 * File:   lcp_nsqp.h
 * Author: carser
 *
 * Created on November 11, 2012, 9:45 PM
 */

#ifndef LCP_NSQP_H
#define	LCP_NSQP_H

extern "C"
{
/* Siconos-Numerics version 2.1.1, Copyright INRIA 2005-2007.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.	
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr 
*/
/*!\file lcp_nsqp.h
 *
 * This subroutine allows the resolution of LCP (Linear Complementary Problem).\n
 * Try \f$(z,w)\f$ such that:\n
 * \f$
 *  \left\lbrace
 *   \begin{array}{l}
 *    w - M z = q\\
 *    0 \le z \perp w \ge 0\\
 *   \end{array}
 *  \right.
 * \f$
 *
 * where M is an (\f$nn \times nn\f$)-matrix, q , w and z nn-vectors.
 */
 /*!\fn void lcp_nsqp( int *nn , double *vec , double *qq , double *z , double *w , int *info , int *iparamLCP , double *dparamLCP )
 *
 * lcp_nsqp use a quadratic programm formulation for solving an non symmetric LCP
 *
 * Generic lcp parameters:\n
 *
 * \param nn      On enter, an integer which represents the dimension of the system.
 * \param vec     On enter, a (\f$nn \times nn\f$)-vector of doubles which contains the components of the matrix with a fortran storage.
 * \param qq      On enter, a nn-vector of doubles which contains the components of the right hand side vector.
 * \param z       On return, a nn-vector of doubles which contains the initial solution and returns the solution of the problem.
 * \param w       On return, a nn-vector of doubles which contains the solution of the problem.
 * \param info    On return, an integer which returns the termination value:\n
 *                0 : convergence  / minimization sucessfull\n
 *                1 : Too Many iterations\n
 * 	          2 : Accuracy insuficient to satisfy convergence criterion\n
 *                5 : Length of working array insufficient\n
 *                Other : The constraints are inconstent\n
 *
 * Specific NSQP parameters:\n
 * 
 * \param iparamLCP    On enter/return, a vector of integers (not used here).
 * \param dparamLCP    On enter/return, a vector of doubles:\n
 *                     - dparamLCP[0] = tol   On enter, the tolerance required.
 *
 * \author Vincent Acary
 * \ingroup SiconosNSQP
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void ql0001_( int *m , int *me , int *mmax , int *n , int *nmax , int *mnn , 
	      double *c , double *d , double *a , double *b , double *xl , double *xu ,
	      double *x , double *u , int *iout , int *ifail , int *iprint , double *war ,
	      int *lwar , int *iwar , int *liwar , double *eps );

void lcp_nsqp( int *nn , double *vec , double *qq , double *z , double *w , int *info , int *iparamLCP , double *dparamLCP ){


    int i, j;
   
    int n=*nn, nmax;
    int m, me, mmax, mnn;
     
    double *Q, *A;
    double *p, *b, *xl, *xu;
 
    double *lambda,tol;
    
    int lwar, liwar, iout, un;
    int *iwar;
    double *war;

    tol   = dparamLCP[0];

    /* / m :        total number of constraints.*/
    m=n;
    /* / me :       number of equality constraints.*/
    me=0;
    /* /  mmax :     row dimension of a. mmax must be at least one and greater than m.*/
    mmax = m+1;
    /* /n :        number of variables.
    //nmax :     row dimension of C. nmax must be greater or equal to n.*/
    nmax =n;
    /* /mnn :      must be equal to m + n + n.	*/
    mnn = m+n+n;
    
    for (i=0;i<n;i++)
	{
	z[i]=0.0;
	w[i]=0.0;
	}
    


    /* / Creation of objective function matrix Q and the the constant vector of the objective function p*/

    Q= (double *)malloc(nmax*nmax*sizeof(double));
    for (i=0;i<n;i++)
	{
	for (j=0;j<n;j++) Q[j*n+i] =(vec[j*n+i]+vec[i*n+j]);
	}
    /* /for (i=0;i<n*n;i++)	printf("Q[%i] = %g\n",i,Q[i]);*/

    p= (double *)malloc(nmax*sizeof(double));
    for (i=0;i<n;i++)
	p[i]=qq[i] ;
    /* /for (i=0;i<n;i++)	printf("p[%i] = %g\n",i,p[i]);*/

    /* / Creation of the data matrix of the linear constraints, A and  the constant data of the linear constraints b*/
    A= (double *)malloc(mmax*nmax*sizeof(double));
    for (i=0;i<m;i++)
	{
	for (j=0;j<n;j++) A[j*mmax+i] = vec[j*n+i];
	}
	
    /* /for (i=0;i<mmax*mmax;i++)	printf("A[%i] = %g\n",i,A[i]);*/
    
    b= (double *)malloc(mmax*sizeof(double));
    for (i=0;i<m;i++) b[i]=qq[i] ;    
    
    /* /for (i=0;i<m;i++)	printf("b[%i] = %g\n",i,b[i]);*/
   
    /* / Creation of the the lower and upper bounds for the variables.*/
    xu= (double *)malloc(n*sizeof(double));
    for (i=0;i<n;i++) xu[i]=1e300 ;
    xl= (double *)malloc(n*sizeof(double));
    for (i=0;i<n;i++) xl[i]=0.0 ;
  
    /* / on return, lambda contains the lagrange multipliers.*/
    lambda= (double *)malloc(mnn*sizeof(double));
    for (i=0;i<mnn;i++) lambda[i]=0.0 ;

    /* /   integer indicating the desired output unit number,*/
    iout=6;

    /* /   output control.*/
    un=1;
    
    /* / real working array. */
    lwar = 3*nmax*nmax/2 + 10*nmax + 2*mmax;
    war= (double *)malloc(lwar*sizeof(double));
    /* / integer working array. */
    liwar = n ;
    iwar= (int *)malloc(liwar*sizeof(int));
    iwar[0]=1; 
    
    
    /* / call ql0001_*/
    ql0001_(&m, &me, &mmax, &n, &nmax, &mnn, Q, p, A, b, xl, xu,
	    z, lambda, &iout, info , &un, war, &lwar, iwar, &liwar, &tol);
    
    /* /    printf("tol = %10.4e\n",*tol);
    // for (i=0;i<mnn;i++)printf("lambda[%i] = %g\n",i,lambda[i]);
    // for (i=0;i<n;i++)printf("z[%i] = %g\n",i,z[i]);
	      
    // getting the multiplier due to the lower bounds*/
    for (i=0;i<n;i++) w[i]=lambda[m+i] ;    
    
    /* / memory freeing*/

    free(Q);
    free(p);
    free(A);
    free(b);
    free(xu);
    free(xl);
    free(lambda);
    free(iwar);
    free(war);
}


}



#endif	/* LCP_NSQP_H */

