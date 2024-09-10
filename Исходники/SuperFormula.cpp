double RationalSuperShape2D :: XiSquare5D(
        const vector < Vector2d, aligned_allocator< Vector2d> > Data,
        MatrixXd &alpha,
        VectorXd &beta,
        int functionused,
        bool update) {
    //five dimensional optimization: a, b, n1, n2, n3 are optimized
    VectorXd dj; dj = VectorXd::Zero(5);
    Matrix3d Tr,Rot;
    //functions pointer
    double (RationalSuperShape2D ::*pt2ConstMember)(const Vector2d P, vector<double> &Dffinal) = NULL;
    switch (functionused){
    case 1 :{ pt2ConstMember = &RationalSuperShape2D :: ImplicitFunction1; }break;
    case 2 :{ pt2ConstMember = &RationalSuperShape2D :: ImplicitFunction2; }break;
    case 3 :{ pt2ConstMember = &RationalSuperShape2D :: ImplicitFunction3; }break;
    default : pt2ConstMember = &RationalSuperShape2D :: ImplicitFunction1;
    }
    vector<double> Df;
    double x, y, tht, ChiSquare(1e15), f(0),
            x0(Get_xoffset()),y0(Get_yoffset()),tht0(Get_thtoffset());
    //clean memory
    if ( update ) {
        alpha.setZero();
        beta.setZero();
    }
    //evaluate ChiSquare, components for the beta and matrix alpha
    ChiSquare=0;
    //First define inverse translation T-1
    Tr.setZero();
    Rot.setZero();
    Tr << 1 , 0 , -x0 ,
            0 , 1 , -y0 ,
            0 , 0 , 1;
    //Then define inverse rotation, i.e. transposed rotation
    Rot << cos(tht0) , sin(tht0) , 0 ,
            -sin(tht0) , cos(tht0) , 0 ,
            0 , 0 , 1;
    //summation of squared potentials
    for(size_t i=0; i<Data.size(); i++ ){
        double DfDr;
        //global inverse transform is T * R
        Vector2d dum(Data[i]);
        Vector3d dum2(dum[0],dum[1],1);
        //apply inverse transform
        Vector3d dum3 ( Rot * (Tr * dum2));
        Vector2d P( dum3[0], dum3[1]); //2D point in canonical referential
        //get partial derivatives for canonical point
        x = P[0]; y = P[1];
        // avoid division by 0 ==> numerical stability
        if (P.norm()<EPSILON) continue; // avoids division by zero
        tht = atan2(y,x); if( tht<0) tht+=2.*M_PI;
        //theta = Arctan(Y/X)

        //avoid non differentiable cases
        f = (*this.*pt2ConstMember)(P, Df); // call to the implicit function
        //
        //compute elements beta[i][0] and alpha[i][j]
        //
        //==> requires partial derivatives!!
        DfDr = Df[2]; //Df/Dr stored at index 2 in array Df during the call to ImplicitFunction1-2-3
        // F1 = R-PL ==> DfDr = 1. ;
        // F2 = 1-PL/R ==> DfDr = PL/R\B2 ;
        // F3 = log ( R\B2/PSL) ==> DfDr = 2/R
        dj.setZero();
        //df/da = df/dr * dr/da
        dj[0] = DfDr * DrDa(tht) ;
        //df/db = df/dr * dr/db
        dj[1] = DfDr * DrDb(tht) ;
        //df/dn1 = df/dr * dr/dn1
        dj[2] = DfDr * DrDn1(tht);
        //df/dn2 = df/dr * dr/dn2
        dj[3] = DfDr * DrDn2(tht);
        //df/dn3 = df/dr * dr/dn3
        dj[4] = DfDr * DrDn3(tht);
        ChiSquare += f*f;
        if(update){
            //gradient beta
            for(int k=0;k<5; k++)
            {
                beta[k] -= f * dj[k];
            }
            //compute approximation of Hessian matrix
            for(int k=0; k<5; k++)
                for(int j=0; j<5; j++)
                    alpha(k,j) += dj[k]*dj[j];
        }
    }//for all vertices
    return ChiSquare;
}