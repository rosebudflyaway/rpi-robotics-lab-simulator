/*
 * sphere_on_sphere_mex.c
 *
 * Code generation for function 'sphere_on_sphere'
 *
 * C source code generated on: Sat Oct 18 11:57:31 2014
 *
 */

/* Include files */
#include "mex.h"
#include "sphere_on_sphere_api.h"
#include "sphere_on_sphere_initialize.h"
#include "sphere_on_sphere_terminate.h"

/* Type Definitions */

/* Function Declarations */
static void sphere_on_sphere_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

/* Variable Definitions */
emlrtContext emlrtContextGlobal = { true, false, EMLRT_VERSION_INFO, NULL, "sphere_on_sphere", NULL, false, NULL, false, 1, false };

/* Function Definitions */
static void sphere_on_sphere_mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Temporary copy for mex outputs. */
  mxArray *outputs[1];
  int n = 0;
  int nOutputs = (nlhs < 1 ? 1 : nlhs);
  /* Check for proper number of arguments. */
  if(nrhs != 0) {
    mexErrMsgIdAndTxt("emlcoder:emlmex:WrongNumberOfInputs","0 inputs required for entry-point 'sphere_on_sphere'.");
  } else if(nlhs > 1) {
    mexErrMsgIdAndTxt("emlcoder:emlmex:TooManyOutputArguments","Too many output arguments for entry-point 'sphere_on_sphere'.");
  }
  /* Module initialization. */
  sphere_on_sphere_initialize(&emlrtContextGlobal);
  /* Call the function. */
  sphere_on_sphere_api((const mxArray**)outputs);
  /* Copy over outputs to the caller. */
  for (n = 0; n < nOutputs; ++n) {
    plhs[n] = emlrtReturnArrayR2009a(outputs[n]);
  }
  /* Module finalization. */
  sphere_on_sphere_terminate();
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /* Initialize the memory manager. */
  mexAtExit(sphere_on_sphere_atexit);
  emlrtClearAllocCount(&emlrtContextGlobal, 0, 0, NULL);
  /* Dispatch the entry-point. */
  sphere_on_sphere_mexFunction(nlhs, plhs, nrhs, prhs);
}
/* End of code generation (sphere_on_sphere_mex.c) */
