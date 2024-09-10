void CompressibleExponentialLaw<DIM>::ComputeStressAndStressDerivative(c_matrix<double,DIM,DIM>& rC,
                                                                       c_matrix<double,DIM,DIM>& rInvC,
                                                                       double                pressure /* not used */,
                                                                       c_matrix<double,DIM,DIM>& rT,
                                                                       FourthOrderTensor<DIM,DIM,DIM,DIM>& rDTdE,
                                                                       bool                  computeDTdE)
{
    static c_matrix<double,DIM,DIM> C_transformed;
    static c_matrix<double,DIM,DIM> invC_transformed;

    // The material law parameters are set up assuming the fibre direction is (1,0,0)
    // and sheet direction is (0,1,0), so we have to transform C,inv(C),and T.
    // Let P be the change-of-basis matrix P = (\mathbf{m}_f, \mathbf{m}_s, \mathbf{m}_n).
    // The transformed C for the fibre/sheet basis is C* = P^T C P.
    // We then compute T* = T*(C*), and then compute T = P T* P^T.

    this->ComputeTransformedDeformationTensor(rC, rInvC, C_transformed, invC_transformed);

    // Compute T*

    c_matrix<double,DIM,DIM> E = 0.5*(C_transformed - mIdentity);

    double QQ = 0;
    for (unsigned M=0; M<DIM; M++)
    {
        for (unsigned N=0; N<DIM; N++)
        {
            QQ += mB[M][N]*E(M,N)*E(M,N);
        }
    }
    assert(QQ < 10.0);///\todo #2193 This line is to trap for large deformations which lead to blow up in the exponential Uysk model
    double multiplier = mA*exp(QQ);
    rDTdE.Zero();

    double J = sqrt(Determinant(rC));

    for (unsigned M=0; M<DIM; M++)
    {
        for (unsigned N=0; N<DIM; N++)
        {
            rT(M,N) = multiplier*mB[M][N]*E(M,N) + mCompressibilityParam * J*log(J)*invC_transformed(M,N);

            if (computeDTdE)
            {
                for (unsigned P=0; P<DIM; P++)
                {
                    for (unsigned Q=0; Q<DIM; Q++)
                    {
                        rDTdE(M,N,P,Q) =    multiplier * mB[M][N] * (M==P)*(N==Q)
                                         +  2*multiplier*mB[M][N]*mB[P][Q]*E(M,N)*E(P,Q)
                                         +  mCompressibilityParam * (J*log(J) + J) * invC_transformed(M,N) * invC_transformed(P,Q)
                                         -  mCompressibilityParam * 2*J*log(J) * invC_transformed(M,P) * invC_transformed(Q,N);
                    }
                }
            }
        }
    }

    // Now do:   T = P T* P^T   and   dTdE_{MNPQ}  =  P_{Mm}P_{Nn}P_{Pp}P_{Qq} dT*dE*_{mnpq}
    this->TransformStressAndStressDerivative(rT, rDTdE, computeDTdE);
}