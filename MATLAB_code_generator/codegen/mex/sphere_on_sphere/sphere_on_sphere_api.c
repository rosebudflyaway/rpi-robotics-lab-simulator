/*
 * sphere_on_sphere_api.c
 *
 * Code generation for function 'sphere_on_sphere_api'
 *
 * C source code generated on: Sat Oct 18 11:57:31 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sphere_on_sphere.h"
#include "sphere_on_sphere_api.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static const mxArray *emlrt_marshallOut(const struct_T *u);

/* Function Definitions */

static const mxArray *emlrt_marshallOut(const struct_T *u)
{
    const mxArray *y;
    const mxArray *b_y;
    const mxArray *m0;
    const mxArray *c_y;
    const mxArray *d_y;
    const mxArray *e_y;
    const mxArray *f_y;
    static const int32_T iv3[1] = { 3 };
    real_T (*pData)[];
    int32_T i;
    const mxArray *g_y;
    const mxArray *h_y;
    const mxArray *i_y;
    static const int32_T iv4[2] = { 1, 0 };
    const mxArray *j_y;
    const mxArray *k_y;
    const mxArray *l_y;
    const mxArray *m_y;
    static const int32_T iv5[2] = { 0, 0 };
    const mxArray *n_y;
    const mxArray *o_y;
    static const int32_T iv6[2] = { 0, 0 };
    const mxArray *p_y;
    static const int32_T iv7[2] = { 0, 0 };
    const mxArray *q_y;
    static const int32_T iv8[2] = { 0, 0 };
    const mxArray *r_y;
    const mxArray *s_y;
    const mxArray *t_y;
    const mxArray *u_y;
    const mxArray *v_y;
    static const int32_T iv9[2] = { 0, 0 };
    const mxArray *w_y;
    const mxArray *x_y;
    const mxArray *y_y;
    const mxArray *ab_y;
    const mxArray *bb_y;
    const mxArray *cb_y;
    const mxArray *db_y;
    static const int32_T iv10[2] = { 0, 0 };
    const mxArray *eb_y;
    y = NULL;
    emlrtAssign(&y, mxCreateStructMatrix(1, 1, 0, NULL));
    b_y = NULL;
    m0 = mxCreateDoubleScalar(u->time);
    emlrtAssign(&b_y, m0);
    emlrtAddField(y, b_y, "time", 0);
    c_y = NULL;
    m0 = mxCreateDoubleScalar(u->step);
    emlrtAssign(&c_y, m0);
    emlrtAddField(y, c_y, "step", 0);
    d_y = NULL;
    m0 = mxCreateDoubleScalar(u->MAX_STEP);
    emlrtAssign(&d_y, m0);
    emlrtAddField(y, d_y, "MAX_STEP", 0);
    e_y = NULL;
    m0 = mxCreateLogicalScalar(u->gravity);
    emlrtAssign(&e_y, m0);
    emlrtAddField(y, e_y, "gravity", 0);
    f_y = NULL;
    m0 = mxCreateNumericArray(1, (int32_T *)&iv3, mxDOUBLE_CLASS, mxREAL);
    pData = (real_T (*)[])mxGetPr(m0);
    for (i = 0; i < 3; i++) {
        (*pData)[i] = u->gravityVector[i];
    }
    emlrtAssign(&f_y, m0);
    emlrtAddField(y, f_y, "gravityVector", 0);
    g_y = NULL;
    m0 = mxCreateLogicalScalar(u->jointCorrection);
    emlrtAssign(&g_y, m0);
    emlrtAddField(y, g_y, "jointCorrection", 0);
    h_y = NULL;
    m0 = mxCreateLogicalScalar(u->record);
    emlrtAssign(&h_y, m0);
    emlrtAddField(y, h_y, "record", 0);
    i_y = NULL;
    m0 = mxCreateCharArray(2, iv4);
    emlrtAssign(&i_y, m0);
    emlrtAddField(y, i_y, "record_directory", 0);
    j_y = NULL;
    m0 = mxCreateDoubleScalar(u->record_fileID);
    emlrtAssign(&j_y, m0);
    emlrtAddField(y, j_y, "record_fileID", 0);
    k_y = NULL;
    m0 = mxCreateLogicalScalar(u->FRICTION);
    emlrtAssign(&k_y, m0);
    emlrtAddField(y, k_y, "FRICTION", 0);
    l_y = NULL;
    m0 = mxCreateDoubleScalar(u->num_fricdirs);
    emlrtAssign(&l_y, m0);
    emlrtAddField(y, l_y, "num_fricdirs", 0);
    m_y = NULL;
    m0 = mxCreateNumericArray(2, (int32_T *)&iv5, mxDOUBLE_CLASS, mxREAL);
    emlrtAssign(&m_y, m0);
    emlrtAddField(y, m_y, "userFunction", 0);
    n_y = NULL;
    m0 = mxCreateDoubleScalar(u->num_bodies);
    emlrtAssign(&n_y, m0);
    emlrtAddField(y, n_y, "num_bodies", 0);
    o_y = NULL;
    m0 = mxCreateNumericArray(2, (int32_T *)&iv6, mxDOUBLE_CLASS, mxREAL);
    emlrtAssign(&o_y, m0);
    emlrtAddField(y, o_y, "bodies", 0);
    p_y = NULL;
    m0 = mxCreateNumericArray(2, (int32_T *)&iv7, mxDOUBLE_CLASS, mxREAL);
    emlrtAssign(&p_y, m0);
    emlrtAddField(y, p_y, "contacts", 0);
    q_y = NULL;
    m0 = mxCreateNumericArray(2, (int32_T *)&iv8, mxDOUBLE_CLASS, mxREAL);
    emlrtAssign(&q_y, m0);
    emlrtAddField(y, q_y, "joints", 0);
    r_y = NULL;
    m0 = mxCreateDoubleScalar(u->num_jointConstraints);
    emlrtAssign(&r_y, m0);
    emlrtAddField(y, r_y, "num_jointConstraints", 0);
    s_y = NULL;
    m0 = mxCreateDoubleScalar(u->num_activeJointBodies);
    emlrtAssign(&s_y, m0);
    emlrtAddField(y, s_y, "num_activeJointBodies", 0);
    t_y = NULL;
    m0 = mxCreateDoubleScalar(u->num_activeBodies);
    emlrtAssign(&t_y, m0);
    emlrtAddField(y, t_y, "num_activeBodies", 0);
    u_y = NULL;
    m0 = mxCreateDoubleScalar(u->num_dynamicBodies);
    emlrtAssign(&u_y, m0);
    emlrtAddField(y, u_y, "num_dynamicBodies", 0);
    v_y = NULL;
    m0 = mxCreateNumericArray(2, (int32_T *)&iv9, mxDOUBLE_CLASS, mxREAL);
    emlrtAssign(&v_y, m0);
    emlrtAddField(y, v_y, "solution_error", 0);
    w_y = NULL;
    m0 = mxCreateDoubleScalar(u->epsilon);
    emlrtAssign(&w_y, m0);
    emlrtAddField(y, w_y, "epsilon", 0);
    x_y = NULL;
    m0 = mxCreateDoubleScalar(u->figure);
    emlrtAssign(&x_y, m0);
    emlrtAddField(y, x_y, "figure", 0);
    y_y = NULL;
    m0 = mxCreateLogicalScalar(u->draw);
    emlrtAssign(&y_y, m0);
    emlrtAddField(y, y_y, "draw", 0);
    ab_y = NULL;
    m0 = mxCreateLogicalScalar(u->drawContacts);
    emlrtAssign(&ab_y, m0);
    emlrtAddField(y, ab_y, "drawContacts", 0);
    bb_y = NULL;
    m0 = mxCreateLogicalScalar(u->drawBoundingBoxes);
    emlrtAssign(&bb_y, m0);
    emlrtAddField(y, bb_y, "drawBoundingBoxes", 0);
    cb_y = NULL;
    m0 = mxCreateLogicalScalar(u->drawJoints);
    emlrtAssign(&cb_y, m0);
    emlrtAddField(y, cb_y, "drawJoints", 0);
    db_y = NULL;
    m0 = mxCreateNumericArray(2, (int32_T *)&iv10, mxDOUBLE_CLASS, mxREAL);
    emlrtAssign(&db_y, m0);
    emlrtAddField(y, db_y, "contactGraphics", 0);
    eb_y = NULL;
    m0 = mxCreateDoubleScalar(u->h);
    emlrtAssign(&eb_y, m0);
    emlrtAddField(y, eb_y, "h", 0);
    return y;
}

void sphere_on_sphere_api(const mxArray *plhs[1])
{
    struct_T sim;
    /* Invoke the target function */
    sim = sphere_on_sphere();
    /* Marshall function outputs */
    plhs[0] = emlrt_marshallOut(&sim);
}
/* End of code generation (sphere_on_sphere_api.c) */
