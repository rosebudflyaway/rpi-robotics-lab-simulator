/*
 * sphere_on_sphere_terminate.c
 *
 * Code generation for function 'sphere_on_sphere_terminate'
 *
 * C source code generated on: Sat Oct 18 11:57:31 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sphere_on_sphere.h"
#include "sphere_on_sphere_terminate.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */

void sphere_on_sphere_atexit(void)
{
    emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void sphere_on_sphere_terminate(void)
{
    emlrtLeaveRtStack(&emlrtContextGlobal);
}
/* End of code generation (sphere_on_sphere_terminate.c) */
