/* 
 * File:   lcpDynamics.h
 * Author: Ying Lu 
 *
 * Created on November 3, 2014
 */

#include "lcpDynamics.h"
#include "pgs.h"
#define GROUND -1
#define SPHERE 1

vector<double> lcpDynamics(vector<Contact> &contacts, vector<Sphere> &spheres, int &num_contacts, int &num_spheres, double h)
{

    int nd = 0;  // Number of friction directions in discretized friction cone
    int nb = num_spheres;
    int nc = num_contacts;
    int i, j, k;
    
    // declare 2d array 
    double M[6*nb][6*nb];
    double Minv[6*nb][6*nb];
    double Gn[6*nb][nc];
    double Gf[6*nb][nd*nc]; 
    double E[nd*nc][nc];

    double U[nc];
    double NU[6*nb];
    double FX[6*nb];
    double Pext[6*nb];
    double PSI[nc];

    // Initialize array to 0
    for(i=0; i<6*nb; i++)
    {
        for(j=0; j<6*nb; j++)
        {
            M[i][j] = 0.0;
            Minv[i][j] = 0.0;
        }
    }

    for(i=0; i<6*nb; i++)
        for(j=0; j<nc; j++)
            Gn[i][j] = 0.0;
    for(i=0; i<6*nb; i++)
        for(j=0; j<nd*nc; j++)
            Gf[i][j] = 0.0;
    for(i=0; i<nd*nc; i++)
        for(j=0; j<nc; j++)
            E[i][j] = 0.0;

    for(i=0; i<nc; i++)
    {
        U[i] = 0.0;
        PSI[i] = 0.0;
    }
    for(i=0; i<6*nb; i++)
    {
        NU[i] = 0.0;
        FX[i] = 0.0;
        Pext[i] = 0.0;
    }


    
    // Formulate dynamics 
    // M - mass matrix
    // SPHERES
    int bid;  
    int s;
    for (s=0; s<nb; s++) 
    {
        if ( spheres[s].ContactCount > 0 ) 
        { 
            // If sphere has active contacts; sphere.BodyIndex starts with 1,
            bid = spheres[s].BodyIndex; 
            for(i=6*bid-6; i<6*bid; i++)
            {
                for(j=6*bid-6; j<6*bid; j++)
                {
                    M[i][j] = 0.0;
                    Minv[i][j] = 0.0;
                }
            }

            for(i=6*bid-6; i<6*bid-3; i++)
            {
                M[i][i] = spheres[s].Mass_Matrix[i-(6*bid-6)][i-(6*bid-6)];
                M[i+3][i+3] = spheres[s].Inertia_Matrix[i-(6*bid-6)][i-(6*bid-6)];
                Minv[i][i] = 1.0 / (spheres[s].Mass_Matrix[i-(6*bid-6)][i-(6*bid-6)]);
                Minv[i+3][i+3] = 1.0/(spheres[s].Inertia_Matrix[i-(6*bid-6)][i-(6*bid-6)]);
            }

        }
    }

    /*
    cout << "------1  Inside lcpDynamics.cpp: here is matrix M" << endl;
    cout << "M" << endl;
    for(i=0; i<6*nb; i++)
    {
        for(j=0; j<6*nb; j++)
        {
            cout << M[i][j] << ", ";
        }
        cout << endl;
    }
    */

    
    // eg:  nc = 3; nd = 4
    // E = [1 0 0;
    //      1 0 0;
    //      1 0 0;
    //      1 0 0;
    //      0 1 0;
    //      0 1 0;
    //      0 1 0;
    //      0 1 0;
    //      0 0 1;
    //      0 0 1;
    //      0 0 1;
    //      0 0 1]
    if (nd > 0)
    {
        for (i=0; i<nc; i++)  // column
        {
            for(j=i*nd; j<(i+1)*nd; j++) // row
                E[j][i] = 1.0;
        }
    }
    
    // Gn, U, and b
    int cID, body1id, body2id;  
    glm::vec3 r1, r2, d, cross_rn, cross_rt;
    double Gn_i1[6], Gn_i2[6], Gf_i1[6], Gf_i2[6];

    for (i=0; i<nc; i++) 
    {
        if (contacts[i].body1_type == GROUND) 
        { 
            // GROUND VERSION
            Sphere body2; 
            body2 = spheres[contacts[i].body2];
            glm::vec3 normal = contacts[i].normal;
            glm::vec3 tangent = contacts[i].tangent;
            
            cID = contacts[i].contact_ID;  
            r2 = contacts[i].r2; 
            body2id = body2.BodyIndex; 
            cross_rn = glm::cross(r2, normal);

            // Gn_i2 = [normal; cross_rn]
            for(j=0; j<3; j++)
            {
                Gn_i2[j] = normal[j];
                Gn_i2[j+3] = cross_rn[j];
            }

            if (!body2.IsStaticBody)
            {
                for(j=0; j<6; j++)
                    Gn[6*body2id-6+j][cID] = Gn_i2[j];
            }

            // Gf
            if (nd > 0) 
            {
                for (j=0; j < nd; j++) 
                {   // For each friction direction
                    double angle = j/(double)nd * (2.0 * M_PI);
                    glm::mat3 rot_matrix = rot(normal, angle); 
                    //friend operator * for mat3 and vec3
                    d = rot_matrix * tangent; 
                    // Gf_i2 = [d; cross_rt]; there are nd such columns
                    cross_rt = glm::cross(r2, d);
                    for(k=0; k<3; k++)
                    {
                        Gf_i2[k] = d[k];
                        Gf_i2[k+3] = cross_rt[k];
                    }
                    // update each [d; r X d]; in together there are nd such columns for each contact
                    int p;
                    if ( !body2.IsStaticBody)
                    {
                        for(p=6*body2id-6; p<6*body2id; p++)
                        {
                            Gf[p][nd*cID+j] = Gf_i2[p];
                        }
                    }
                }
            }  // if(nd>0)

            /*
            cout << "This is Gf: " << endl;
            for(j=0; j<6*nb; j++)
            {
                for(k=0; k<nd*nc; k++)
                {
                    cout << Gf[j][k] << ", ";
                }
                cout << endl;
            }
            */

            if ( !body2.IsStaticBody) {
                for(k=0; k<3; k++)
                {
                    NU[6*body2id-6+k] = body2.L_vel[k];
                    NU[6*body2id-6+3+k] = body2.A_vel[k];
                }

                for(k=0; k<3; k++)
                {
                    FX[6*body2id-6+k] = body2.Fext[k];
                    FX[6*body2id-6+3+k] = body2.Text[k];
                    Pext[6*body2id-6+k] = body2.Fext[k] * h;
                    Pext[6*body2id-6+3+k] = body2.Text[k] * h;
                }
            }

            // U
            U[cID] = 0.5 * (0.5 * body2.Mu);
            PSI[cID] = contacts[i].psi;

            // print NU FX Pext
    
            /*
            cout << "------2  Inside lcpDynamics.cpp" << endl;
            cout <<"##############################" << endl;
            cout << "NU" << endl;
            for(k=0; k<6*nb; k++)
                cout << NU[k] << ",  " << endl;
            cout << endl;
            cout << "FX" << endl;
            for(k=0; k<6*nb; k++)
                cout << FX[k] << ",  " << endl;
            cout << endl;
            cout << "Pext" << endl;
            for(k=0; k<6*nb; k++)
                cout << Pext[k] << ",  " << endl;
            cout << endl;
            cout << "U" << endl;
            for(k=0; k<nc; k++)
                cout << U[k] << ",  " << endl;
            cout << endl;
            cout << "PSI" << endl;
            for(k=0; k<nc; k++)
                cout << PSI[k] << ",  " << endl;
            cout << endl;
            */

        } // if body1_type.TYPE == GROUND
        
        // Ground not involved 
        else 
        {
            cID = contacts[i].contact_ID;  
            r1 = contacts[i].r1;
            r2 = contacts[i].r2; 

            Sphere body1, body2; 
            body1 = spheres[contacts[i].body1];
            body2 = spheres[contacts[i].body2];
            
            body1id = body1.BodyIndex;
            body2id = body2.BodyIndex; 

            // Gn
            glm::vec3 cross_r1n, cross_r2n;
            cross_r1n = glm::cross(r1, -contacts[i].normal);
            cross_r2n = glm::cross(r2, contacts[i].normal);

            for(j=0; j<3; j++)
            {
                Gn_i1[j] = -contacts[i].normal[j];
                Gn_i1[j+3] = cross_r1n[j];
                
                Gn_i2[j] = contacts[i].normal[j];
                Gn_i2[j+3] = cross_r2n[j];
            }

            if (!body1.IsStaticBody)
            {
                for(j=0; j<6; j++)
                    Gn[6*body1id-6+j][cID] = Gn_i1[j];
            }
            
            if (!body2.IsStaticBody)
            {
                for(j=0; j<6; j++)
                    Gn[6*body2id-6+j][cID] = Gn_i2[j];
            }

            // Gf
            if (nd > 0) 
            {
                for (j=0; j < nd; j++) 
                {    
                    // For each friction direction
                    glm::mat3 rot_matrix = rot(contacts[i].normal, ((j)/(double)nd)*(2.*M_PI)); 
                    //friend operator * for mat3 and vec3
                    d = rot_matrix * contacts[i].tangent; 
                    // Gf_i1 = [d; cross_r1t]  Gf_i2 = [d; cross_r2t]
                    glm::vec3 cross_r1t, cross_r2t;
                    cross_r1t = glm::cross(r1, d);
                    cross_r2t = glm::cross(r2, d);

                    for(k=0; k<3; k++)
                    {
                        Gf_i1[k] = d[k];
                        Gf_i1[k+3] = cross_r1t[k];

                        Gf_i2[k] = d[k];
                        Gf_i2[k+3] = cross_r2t[k];
                    }

                    // update each [d; r cross d]; in total there are nd such columns for each contact
                    int p;
                    if ( !body1.IsStaticBody )
                    {
                        for(p=6*body1id-6; p<6*body1id; p++)
                        {
                            Gf[p][nd*cID+j] = Gf_i1[p];
                        }
                    }
                    if ( !body2.IsStaticBody )
                    {
                        for(p=6*body2id-6; p<6*body2id; p++)
                        {
                            Gf[p][nd*cID+j] = Gf_i2[p];
                        }
                    }

                }
            }

            if ( !body1.IsStaticBody) {
                for(k=0; k<3; k++)
                {
                    NU[6*body1id-6+k] = body1.L_vel[k];
                    NU[6*body1id-6+3+k] = body1.A_vel[k];
                }

                for(k=0; k<3; k++)
                {
                    FX[6*body1id-6+k] = body1.Fext[k];
                    FX[6*body1id-6+3+k] = body1.Text[k];
                    Pext[6*body1id-6+k] = body1.Fext[k] * h;
                    Pext[6*body1id-6+3+k] = body1.Text[k] * h;
                }
            }

            if ( !body2.IsStaticBody) {
                for(k=0; k<3; k++)
                {
                    NU[6*body2id-6+k] = body2.L_vel[k];
                    NU[6*body2id-6+3+k] = body2.A_vel[k];
                }

                for(k=0; k<3; k++)
                {
                    FX[6*body2id-6+k] = body2.Fext[k];
                    FX[6*body2id-6+3+k] = body2.Text[k];
                    Pext[6*body2id-6+k] = body2.Fext[k] * h;
                    Pext[6*body2id-6+3+k] = body2.Text[k] * h;
                }
            }

            // U
            U[cID] = 0.5 * (body1.Mu * body2.Mu);
            PSI[cID] = contacts[i].psi;
        }
    } // Done with submatrices


    // Construct A, b, and solve LCP 
    // double Minv[6*nb][6*nb]
    double MinvGn[6*nb][nc];
    double MinvGf[6*nb][nc*nd];
    double MinvPext[6*nb];

    double GntMinvGn[nc][nc];
    double GntMinvGf[nc][nc*nd];
    double GftMinvGn[nc*nd][nc];
    double GftMinvGf[nc*nd][nc*nd];

    int size_A = nc+(nc+nd)+nc;
    double A[size_A][size_A];
    double b[size_A];

    // Initialize A to zero 
    for(j=0; j<size_A; j++)
        for(k=0; k<size_A; k++)
            A[j][k] = 0.0;

    for(j=0; j<size_A; j++)
        b[j] = 0.0;

    // Compute MinvGn: 
    for(i=0; i<6*nb; i++)
    {
        for(j=0; j<nc; j++)
        {
            MinvGn[i][j] = 0.0;
            for(k=0; k<6*nb; k++)
            {
                MinvGn[i][j] +=  Minv[i][k] * Gn[k][j]; 
            }
        }
    }

    // Compute MinvGf: 
    for(i=0; i<6*nb; i++)
    {
        for(j=0; j<nc*nd; j++)
        {
            MinvGf[i][j] = 0.0;
            for(k=0; k<6*nb; k++)
                MinvGf[i][j] +=  Minv[i][k] * Gf[k][j];
        }
    }

    // Compute MinvPext: 
    for(i=0; i<6*nb; i++)
    {
        MinvPext[i] = 0.0;
        for(j=0; j<6*nb; j++)
            MinvPext[i] += Minv[i][j] * Pext[j];
    }


    // Compute Gn'*MinvGn   (A11)
    for(i=0; i<nc; i++)
    {
        for(j=0; j<nc; j++)
        {
            GntMinvGn[i][j] = 0.0;
            for(k=0; k<6*nb; k++)
            {
                GntMinvGn[i][j] += Gn[k][i] * MinvGn[k][j]; 
            }
            A[i][j] = GntMinvGn[i][j];
        }
    }

    // Compute Gn'MinvGf   (A12)
    for(i=0; i<nc; i++)
    {
        for(j=0; j<nc*nd; j++)
        {
            GntMinvGf[i][j] = 0.0;
            for(k=0; k<6*nb; k++)
            {
                GntMinvGf[i][j] += Gn[k][i] * MinvGf[k][j]; 
            }
            A[i][j+nc] = GntMinvGf[i][j];
        }
    }

    // Compute Gf'MinvGn  (A21)
    for(i=0; i<nc*nd; i++)
    {
        for(j=0; j<nc; j++)
        {
            GftMinvGn[i][j] = 0.0;
            for(k=0; k<6*nb; k++)
            {
                GftMinvGn[i][j] += Gf[k][i] * MinvGn[k][j]; 
            }
            
            A[i+nc][j] = GftMinvGn[i][j];
        }
    }

    // Compute Gf'MinvGf  (A22)
    for(i=0; i<nc*nd; i++)
    {
        for(j=0; j<nc*nd; j++)
        {
            GftMinvGf[i][j] = 0.0;
            for(k=0; k<6*nb; k++)
            {
                GftMinvGf[i][j] += Gf[k][i] * MinvGf[k][j]; 
            }
            A[i+nc][j+nc] = GftMinvGf[i][j];
        }
    }

    // update matrix A; there are 9 submatrices
    // A11 A12 A21 A22 already updated
    // A13  zero blocks
    //
    // A23 
    for(i=nc; i<nc+(nc+nd); i++)
    {
        for(j=nc+(nc+nd); j<size_A; j++)
        {
            A[i][j] = E[i-nc][j-nc-(nc+nd)];
        }
    }

    // A31 
    for(i=nc+(nc+nd); i<size_A; i++)
    {
        A[i][i-nc-(nc+nd)] = U[i-nc-(nc+nd)];
    }

    // A32
    for(i=nc+(nc+nd); i<size_A; i++)
    {
        for(j=nc; j<nc+(nc+nd); j++)
        {
            A[i][j] = -E[j-nc][i-nc-(nc+nd)];
        }
    }

    // A33  0 block
    // Construct vector b
    for(i=0; i<nc; i++)
    {
        double GntNU = 0.0;
        for(j=0; j<6*nb; j++)
        {
            GntNU += Gn[j][i] * (NU[j] + MinvPext[j]);
        }
        b[i] = GntNU + PSI[i] / h;
    }

    for(i=0; i<nc*nd; i++)
    {
        double GftNU = 0.0;
        for(j=0; j<6*nb; j++)
        {
            GftNU += Gf[j][i] * (NU[j] + MinvPext[j]);
        }
        b[i+nc] = GftNU;
    }

    
            
    /*
    cout << "------3  Inside lcpDynamics.cpp" << endl;
    // output matrix A and b 
    cout << "+++++++ 3.1  Inside lcpDynamics.cpp: here is matrix A" << endl;
    for(i=0; i<size_A; i++)
    {
        for(j=0; j<size_A; j++)
        {
            cout << A[i][j] << ", ";
        }
        cout << endl;
    }

    cout << "++++++++  3.2  Inside lcpDynamics.cpp: here is b" << endl;
    for(i=0; i<size_A; i++)
    {
        cout << b[i] << ", ";
    }
    cout << endl;
    */


    Solution solution;
    solution.prob_size = size_A;
    solution.max_iter = 200;
    solution.toler = 0.0001;

    vector<double> Avec;
    vector<double> bvec;
    vector<double> x0;

    for(i=0; i<size_A; i++)
    {
        for(j=0; j<size_A; j++)
        {
            Avec.push_back(A[i][j]);
        }
        bvec.push_back(b[i]);
        x0.push_back(0.0);
    }

    pgs(solution, Avec, bvec, x0);

    vector<double> xsoln = solution.xsoln;

    vector<double> pn;   // nc by 1
    vector<double> pf;   // nc*nd by 1
    vector<double> newNU; //6*nb by 1

    pn.assign(xsoln.begin(), xsoln.begin()+nc);
    pf.assign(xsoln.begin()+nc, xsoln.begin()+nc+nc*nd);

    /*
    cout << "This is pn and pf: " << endl;
    for(i=0; i<pn.size(); i++)
        cout << pn[i] << endl;

    for(i=0; i<pf.size(); i++)
        cout << pf[i] << endl;
    */



    // newNU = NU + MinvGn*Pn + MinvGf*Pf + MinvPext;
    for(i=0; i<6*nb; i++)
    {
       double MinvGnPn_element = 0.0;
       double MinvGfPf_element = 0.0;

       for(j=0; j<nc; j++)
           MinvGnPn_element += MinvGn[i][j] * pn[j];
       for(j=0; j<nc*nd; j++)
           MinvGfPf_element += MinvGf[i][j] * pf[j];

       double newNU_element = 0.0;
       newNU_element = NU[i] + MinvGnPn_element + MinvGfPf_element + MinvPext[i];
       newNU.push_back(newNU_element);
    }

    return newNU;
}

// Returns a 3x3 rotation matrix representing rotation of theta about axis k.  
glm::mat3 rot(glm::vec3 k, double theta) {
    // Normalize k 
    glm::vec3 norm_k, trans_k;
    norm_k = glm::normalize(k);
    glm::mat3 k_multi_kt;  
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            k_multi_kt[i][j] = norm_k[i] * norm_k[j];
    //glm::vec3 trans_norm_k = glm::transpose(norm_k);
    // From Peter Corke, replace "hat(k)*hat(k)" with "(k*k'-eye(3))"
    return glm::mat3(1.0) + (float)sin(theta)*hat(norm_k)+ (float)(1-cos(theta))*(k_multi_kt-glm::mat3(1.0));
}

// hat
// Returns the skew-symmetric matrix form of vector k
glm::mat3 hat(glm::vec3 k) {
    glm::mat3 khat = glm::mat3(0.0);
    khat[0][1] = -k[2];
    khat[0][2] =  k[1];
    khat[1][0] =  k[2];
    khat[2][2] = -k[0];
    khat[2][0] = -k[1];
    khat[2][1] =  k[0];
    return khat;  
}



