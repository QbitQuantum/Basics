void LUTUnb
( bool conjugate,
  const Matrix<F>& U,
        Matrix<F>& X,
  bool checkIfSingular )
{
    EL_DEBUG_CSE
    typedef Base<F> Real;
    const Int m = X.Height();
    const Int n = X.Width();
    if( conjugate )
        Conjugate( X );

    const F* UBuf = U.LockedBuffer();
          F* XBuf = X.Buffer();
    const Int ldu = U.LDim();
    const Int ldx = X.LDim();

    Int k=0;
    while( k < m )
    {
        const bool in2x2 = ( k+1<m && UBuf[(k+1)+k*ldu] != F(0) );
        if( in2x2 )
        {
            // Solve the 2x2 linear systems via a 2x2 QR decomposition produced
            // by the Givens rotation
            //    | c        s | | U(k,  k) | = | gamma11 | 
            //    | -conj(s) c | | U(k+1,k) |   | 0       |
            //
            // and by also forming the right two entries of the 2x2 resulting
            // upper-triangular matrix, say gamma12 and gamma22
            //
            // Extract the 2x2 diagonal block, D
            const F delta11 = UBuf[ k   + k   *ldu];
            const F delta12 = UBuf[ k   +(k+1)*ldu];
            const F delta21 = UBuf[(k+1)+ k   *ldu];
            const F delta22 = UBuf[(k+1)+(k+1)*ldu];
            // Decompose D = Q R
            Real c; F s;
            const F gamma11 = Givens( delta11, delta21, c, s );
            const F gamma12 =        c*delta12 + s*delta22;
            const F gamma22 = -Conj(s)*delta12 + c*delta22;
            if( checkIfSingular )
            {
                // TODO: Check if sufficiently small instead
                if( gamma11 == F(0) || gamma22 == F(0) )
                    LogicError("Singular diagonal block detected");
            }
            for( Int j=0; j<n; ++j )
            {
                F* xBuf = &XBuf[j*ldx];

                // Solve against R^T
                xBuf[k  ] /= gamma11;
                xBuf[k+1] -= gamma12*xBuf[k];
                xBuf[k+1] /= gamma22;

                // Solve against Q^T
                const F chi1 = xBuf[k  ];
                const F chi2 = xBuf[k+1];
                xBuf[k  ] = c*chi1 - Conj(s)*chi2;
                xBuf[k+1] = s*chi1 +       c*chi2;

                // Update x2 := x2 - U12^T x1
                blas::Axpy
                ( m-(k+2), -xBuf[k  ],
                  &UBuf[ k   +(k+2)*ldu], ldu, &xBuf[k+2], 1 );
                blas::Axpy
                ( m-(k+2), -xBuf[k+1],
                  &UBuf[(k+1)+(k+2)*ldu], ldu, &xBuf[k+2], 1 );
            }
            k += 2;
        }
        else
        {
            if( checkIfSingular )
            {
                // TODO: Check if sufficiently small instead
                if( UBuf[k+k*ldu] == F(0) )
                    LogicError("Singular diagonal entry detected");
            }
            for( Int j=0; j<n; ++j )
            {
                F* xBuf = &XBuf[j*ldx];
                xBuf[k] /= UBuf[k+k*ldu];
                blas::Axpy
                ( m-(k+1), -xBuf[k], &UBuf[k+(k+1)*ldu], ldu, &xBuf[k+1], 1 );
            }
            k += 1;
        }
    }
    if( conjugate )
        Conjugate( X );
}