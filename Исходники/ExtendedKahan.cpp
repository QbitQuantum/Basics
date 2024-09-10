void MakeExtendedKahan
( Matrix<F>& A, Base<F> phi, Base<F> mu )
{
    EL_DEBUG_CSE
    typedef Base<F> Real;

    if( A.Height() != A.Width() )
        LogicError("Extended Kahan matrices must be square");
    const Int n = A.Height();
    if( n % 3 != 0 )
        LogicError("Dimension must be an integer multiple of 3");
    const Int l = n / 3;
    if( !l || (l & (l-1)) )
        LogicError("n/3 is not a power of two");
    Int k=0;
    while( Int(1u<<k) < l )
        ++k;

    if( phi <= Real(0) || phi >= Real(1) )
        LogicError("phi must be in (0,1)");
    if( mu <= Real(0) || mu >= Real(1) )
        LogicError("mu must be in (0,1)");

    // Start by setting A to the identity, and then modify the necessary 
    // l x l blocks of its 3 x 3 partitioning.
    MakeIdentity( A );
    auto ABlock = A( IR(2*l,3*l), IR(2*l,3*l) );
    ABlock *= mu;
    ABlock = A( IR(0,l), IR(l,2*l) );
    Walsh( ABlock, k );
    ABlock *= -phi;
    ABlock = A( IR(l,2*l), IR(2*l,3*l) );
    Walsh( ABlock, k );
    ABlock *= phi;

    // Now scale A by S
    const Real zeta = Sqrt(Real(1)-phi*phi);
    for( Int i=0; i<n; ++i )
    {
        const Real gamma = Pow(zeta,Real(i));
        for( Int j=0; j<n; ++j )
            A(i,j) *= gamma;
    }
}