returnValue Integrator::getBackwardSensitivities(	DVector &DX,
													DVector &DP ,
													DVector &DU ,
													DVector &DW ,
													int    order   ) const{

    int run2;
    returnValue returnvalue;

    DVector tmpX ( rhs->getDim() );

    DX.setZero();
    DP.setZero();
    DU.setZero();
    DW.setZero();

    returnvalue = getProtectedBackwardSensitivities( tmpX, DP, DU, DW, order );
    DVector components = rhs->getDifferentialStateComponents();

    for( run2 = 0; run2 < (int) components.getDim(); run2++ )
        DX((int) components(run2)) = tmpX(run2);

    for( run2 = 0; run2 < (int) dPb.getDim(); run2++ )
        DP(run2) += dPb(run2);

    for( run2 = 0; run2 < (int) dUb.getDim(); run2++ )
        DU(run2) += dUb(run2);

    for( run2 = 0; run2 < (int) dWb.getDim(); run2++ )
        DW(run2) += dWb(run2);

    return returnvalue;
}