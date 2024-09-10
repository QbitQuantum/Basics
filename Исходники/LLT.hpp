void LLTUnb
( bool conjugate, const Matrix<F>& L, Matrix<F>& X, bool checkIfSingular )
{
    EL_DEBUG_CSE
    typedef Base<F> Real;
    const Int m = X.Height();
    const Int n = X.Width();

    const F* LBuf = L.LockedBuffer();
          F* XBuf = X.Buffer();
    const Int ldl = L.LDim();
    const Int ldx = X.LDim();

    if( conjugate )
        Conjugate( X );

    Int k=m-1;
    while( k >= 0 )
    {
        const bool in2x2 = ( k>0 && LBuf[(k-1)+k*ldl] != F(0) );
        if( in2x2 )
        {
            --k;
            // Solve the 2x2 linear systems via a 2x2 LQ decomposition produced
            // by the Givens rotation
            //    | L(k,k) L(k,k+1) | | c -conj(s) | = | gamma11 0 |
            //                        | s    c     |
            // and by also forming the bottom two entries of the 2x2 resulting
            // lower-triangular matrix, say gamma21 and gamma22
            //
            // Extract the 2x2 diagonal block, D
            const F delta11 = LBuf[   k +   k *ldl];
            const F delta12 = LBuf[   k +(k+1)*ldl];
            const F delta21 = LBuf[(k+1)+   k *ldl];
            const F delta22 = LBuf[(k+1)+(k+1)*ldl];
            // Decompose D = L Q
            Real c; F s;
            const F gamma11 = Givens( delta11, delta12, c, s );
            const F gamma21 =        c*delta21 + s*delta22;
            const F gamma22 = -Conj(s)*delta21 + c*delta22;
            if( checkIfSingular )
            {
                // TODO: Instead check if values are too small in magnitude
                if( gamma11 == F(0) || gamma22 == F(0) )
                    LogicError("Singular diagonal block detected");
            }
            for( Int j=0; j<n; ++j )
            {
                F* xBuf = &XBuf[j*ldx];
                // Solve against Q^T
                const F chi1 = xBuf[k  ];
                const F chi2 = xBuf[k+1];
                xBuf[k  ] =        c*chi1 + s*chi2;
                xBuf[k+1] = -Conj(s)*chi1 + c*chi2;

                // Solve against R^T
                xBuf[k+1] /= gamma22;
                xBuf[k  ] -= gamma21*xBuf[k+1];
                xBuf[k  ] /= gamma11;

                // Update x0 := x0 - L10^T x1
                blas::Axpy( k, -xBuf[k  ], &LBuf[k  ], ldl, xBuf, 1 );
                blas::Axpy( k, -xBuf[k+1], &LBuf[k+1], ldl, xBuf, 1 );
            }
        }
        else
        {
            if( checkIfSingular )
                if( LBuf[k+k*ldl] == F(0) )
                    LogicError("Singular diagonal entry detected");
            for( Int j=0; j<n; ++j )
            {
                F* xBuf = &XBuf[j*ldx];
                // Solve the 1x1 linear system
                xBuf[k] /= LBuf[k+k*ldl];

                // Update x0 := x0 - l10^T chi_1
                blas::Axpy( k, -xBuf[k], &LBuf[k], ldl, xBuf, 1 );
            }
        }
        --k;
    }
    if( conjugate )
        Conjugate( X );
}