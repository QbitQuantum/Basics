    void NaturalSpline1<Real>::CreatePeriodicSpline ()
    {
        mB = new1<Real>( mNumSegments );
        mC = new1<Real>( mNumSegments );
        mD = new1<Real>( mNumSegments );

#if 1
        // Solving the system using a standard linear solver appears to be
        // numerically stable.
        const int size = 4 * mNumSegments;
        GMatrix<Real> mat( size, size );
        GVector<Real> rhs( size );
        int i, j, k;
        Real delta, delta2, delta3;
        for ( i = 0, j = 0; i < mNumSegments - 1; ++i, j += 4 )
        {
            delta = mTimes[i + 1] - mTimes[i];
            delta2 = delta * delta;
            delta3 = delta * delta2;

            mat[j + 0][j + 0] = ( Real )1;
            mat[j + 0][j + 1] = ( Real )0;
            mat[j + 0][j + 2] = ( Real )0;
            mat[j + 0][j + 3] = ( Real )0;
            mat[j + 1][j + 0] = ( Real )1;
            mat[j + 1][j + 1] = delta;
            mat[j + 1][j + 2] = delta2;
            mat[j + 1][j + 3] = delta3;
            mat[j + 2][j + 0] = ( Real )0;
            mat[j + 2][j + 1] = ( Real )1;
            mat[j + 2][j + 2] = ( ( Real )2 ) * delta;
            mat[j + 2][j + 3] = ( ( Real )3 ) * delta2;
            mat[j + 3][j + 0] = ( Real )0;
            mat[j + 3][j + 1] = ( Real )0;
            mat[j + 3][j + 2] = ( Real )1;
            mat[j + 3][j + 3] = ( ( Real )3 ) * delta;

            k = j + 4;
            mat[j + 0][k + 0] = ( Real )0;
            mat[j + 0][k + 1] = ( Real )0;
            mat[j + 0][k + 2] = ( Real )0;
            mat[j + 0][k + 3] = ( Real )0;
            mat[j + 1][k + 0] = ( Real ) - 1;
            mat[j + 1][k + 1] = ( Real )0;
            mat[j + 1][k + 2] = ( Real )0;
            mat[j + 1][k + 3] = ( Real )0;
            mat[j + 2][k + 0] = ( Real )0;
            mat[j + 2][k + 1] = ( Real ) - 1;
            mat[j + 2][k + 2] = ( Real )0;
            mat[j + 2][k + 3] = ( Real )0;
            mat[j + 3][k + 0] = ( Real )0;
            mat[j + 3][k + 1] = ( Real )0;
            mat[j + 3][k + 2] = ( Real ) - 1;
            mat[j + 3][k + 3] = ( Real )0;
        }

        delta = mTimes[i + 1] - mTimes[i];
        delta2 = delta * delta;
        delta3 = delta * delta2;

        mat[j + 0][j + 0] = ( Real )1;
        mat[j + 0][j + 1] = ( Real )0;
        mat[j + 0][j + 2] = ( Real )0;
        mat[j + 0][j + 3] = ( Real )0;
        mat[j + 1][j + 0] = ( Real )1;
        mat[j + 1][j + 1] = delta;
        mat[j + 1][j + 2] = delta2;
        mat[j + 1][j + 3] = delta3;
        mat[j + 2][j + 0] = ( Real )0;
        mat[j + 2][j + 1] = ( Real )1;
        mat[j + 2][j + 2] = ( ( Real )2 ) * delta;
        mat[j + 2][j + 3] = ( ( Real )3 ) * delta2;
        mat[j + 3][j + 0] = ( Real )0;
        mat[j + 3][j + 1] = ( Real )0;
        mat[j + 3][j + 2] = ( Real )1;
        mat[j + 3][j + 3] = ( ( Real )3 ) * delta;

        k = 0;
        mat[j + 0][k + 0] = ( Real )0;
        mat[j + 0][k + 1] = ( Real )0;
        mat[j + 0][k + 2] = ( Real )0;
        mat[j + 0][k + 3] = ( Real )0;
        mat[j + 1][k + 0] = ( Real ) - 1;
        mat[j + 1][k + 1] = ( Real )0;
        mat[j + 1][k + 2] = ( Real )0;
        mat[j + 1][k + 3] = ( Real )0;
        mat[j + 2][k + 0] = ( Real )0;
        mat[j + 2][k + 1] = ( Real ) - 1;
        mat[j + 2][k + 2] = ( Real )0;
        mat[j + 2][k + 3] = ( Real )0;
        mat[j + 3][k + 0] = ( Real )0;
        mat[j + 3][k + 1] = ( Real )0;
        mat[j + 3][k + 2] = ( Real ) - 1;
        mat[j + 3][k + 3] = ( Real )0;

        for ( i = 0, j = 0; i < mNumSegments; ++i, j += 4 )
        {
            rhs[j + 0] = mA[i];
            rhs[j + 1] = ( Real )0;
            rhs[j + 2] = ( Real )0;
            rhs[j + 3] = ( Real )0;
        }

        GVector<Real> coeff( size );
        bool solved = LinearSystem<Real>().Solve( mat, rhs, coeff );
        assertion( solved, "Failed to solve linear system\n" );
        WM5_UNUSED( solved );

        for ( i = 0, j = 0; i < mNumSegments; ++i )
        {
            j++;
            mB[i] = coeff[j++];
            mC[i] = coeff[j++];
            mD[i] = coeff[j++];
        }
#endif

#if 0
        // Solving the system using the equations derived in the PDF
        // "Fitting a Natural Spline to Samples of the Form (t,f(t))"
        // is ill-conditioned.  TODO: Find a way to row-reduce the matrix of the
        // PDF in a numerically stable manner yet retaining the O(n) asymptotic
        // behavior.

        // Compute the inverses M[i]^{-1}.
        const int numSegmentsM1 = mNumSegments - 1;
        Matrix4<Real>* invM = new1<Matrix4<Real> >( numSegmentsM1 );

        Real delta;
        int i;
        for ( i = 0; i < numSegmentsM1; i++ )
        {
            delta = mTimes[i + 1] - mTimes[i];
            Real invDelta1 = ( ( Real )1 ) / delta;
            Real invDelta2 = invDelta1 / delta;
            Real invDelta3 = invDelta2 / delta;

            Matrix4<Real>& invMi = invM[i];
            invMi[0][0] = ( Real )1;
            invMi[0][1] = ( Real )0;
            invMi[0][2] = ( Real )0;
            invMi[0][3] = ( Real )0;
            invMi[1][0] = ( ( Real )( -3 ) ) * invDelta1;
            invMi[1][1] = ( ( Real )3 ) * invDelta1;
            invMi[1][2] = ( Real )( -2 );
            invMi[1][3] = delta;
            invMi[2][0] = ( ( Real )3 ) * invDelta2;
            invMi[2][1] = ( ( Real )( -3 ) ) * invDelta2;
            invMi[2][2] = ( ( Real )3 ) * invDelta1;
            invMi[2][3] = ( Real )( -2 );
            invMi[3][0] = -invDelta3;
            invMi[3][1] = invDelta3;
            invMi[3][2] = -invDelta2;
            invMi[3][3] = invDelta1;
        }

        // Matrix M[n-1].
        delta = mTimes[i + 1] - mTimes[i];
        Real delta2 = delta * delta;
        Real delta3 = delta2 * delta;
        Matrix4<Real> lastM
        (
            ( Real )1, ( Real )0, ( Real )0, ( Real )0,
            ( Real )1, delta, delta2, delta3,
            ( Real )0, ( Real )1, ( ( Real )2 )*delta, ( ( Real )3 )*delta2,
            ( Real )0, ( Real )0, ( Real )1, ( ( Real )3 )*delta
        );

        // Matrix L.
        Matrix4<Real> LMat
        (
            ( Real )0, ( Real )0, ( Real )0, ( Real )0,
            ( Real )1, ( Real )0, ( Real )0, ( Real )0,
            ( Real )0, ( Real )1, ( Real )0, ( Real )0,
            ( Real )0, ( Real )0, ( Real )1, ( Real )0
        );

        // Vector U.
        Vector<4, Real> U( ( Real )1, ( Real )0, ( Real )0, ( Real )0 );

        // Initialize P = L and Q = f[n-2]*U.
        Matrix4<Real> P = LMat;

        const int numSegmentsM2 = mNumSegments - 2;
        Vector<4, Real> Q = mA[numSegmentsM2] * U;

        // Compute P and Q.
        for ( i = numSegmentsM2; i >= 0; --i )
        {
            // Matrix L*M[i]^{-1}.
            Matrix4<Real> LMInv = LMat * invM[i];

            // Update P.
            P = LMInv * P;

            // Update Q.
            if ( i > 0 )
            {
                Q = mA[i - 1] * U + LMInv * Q;
            }
            else
            {
                Q = mA[numSegmentsM1] * U + LMInv * Q;
            }
        }

        // Final update of P.
        P = lastM - P;

        // Compute P^{-1}.
        Matrix4<Real> invP = P.Inverse();

        // Compute K[n-1].
        Vector<4, Real> coeff = invP * Q;
        mB[numSegmentsM1] = coeff[1];
        mC[numSegmentsM1] = coeff[2];
        mD[numSegmentsM1] = coeff[3];

        // Back substitution for the other K[i].
        for ( i = numSegmentsM2; i >= 0; i-- )
        {
            coeff = invM[i] * ( mA[i] * U + LMat * coeff );
            mB[i] = coeff[1];
            mC[i] = coeff[2];
            mD[i] = coeff[3];
        }

        delete1( invM );
#endif
    }