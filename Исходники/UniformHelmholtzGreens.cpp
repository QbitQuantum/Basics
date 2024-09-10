void UniformHelmholtzGreens( Matrix<Complex<Real>>& A, Int n, Real lambda )
{
    EL_DEBUG_CSE
    typedef Complex<Real> C;
    const Real pi = 4*Atan( Real(1) );
    const Real k0 = 2*pi/lambda;

    // Generate a list of n uniform samples from the 3D unit ball
    Matrix<Real> X(3,n);
    for( Int j=0; j<n; ++j )
    {
        Real x0, x1, x2;
        // Sample uniformly from [-1,+1]^3 until a point is drawn from the ball
        while( true )
        {
            x0 = SampleUniform( Real(-1), Real(1) ); 
            x1 = SampleUniform( Real(-1), Real(1) );
            x2 = SampleUniform( Real(-1), Real(1) );
            const Real radiusSq = x0*x0 + x1*x1 + x2*x2;
            if( radiusSq > 0 && radiusSq <= 1 )
                break;
        }
        X(0,j) = x0;
        X(1,j) = x1;
        X(2,j) = x2;
    }
    
    A.Resize( n, n );
    for( Int j=0; j<n; ++j )
    {
        const Real xj0 = X(0,j);
        const Real xj1 = X(1,j);
        const Real xj2 = X(2,j);
        for( Int i=0; i<n; ++i )
        {
            if( i == j ) 
            {
                A(i,j) = 0;
            }
            else
            {
                const Real d0 = X(0,i)-xj0;
                const Real d1 = X(1,i)-xj1;
                const Real d2 = X(2,i)-xj2;
                const Real gamma = k0*Sqrt(d0*d0+d1*d1+d2*d2);
                const Real realPart = Cos(gamma)/gamma;
                const Real imagPart = Sin(gamma)/gamma;
                A(i,j) = C(realPart,imagPart);
            }
        }
    }
}