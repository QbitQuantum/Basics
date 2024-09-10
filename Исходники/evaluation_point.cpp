returnValue EvaluationPoint::init( const Function &f ,
                                   uint nx_, uint na_, uint np_,
                                   uint nu_, uint nw_, uint nd_,
                                   uint N_                       ) {

    uint run1;
    deleteAll();

    nx = acadoMax( nx_, f.getNX ()                 );
    na = acadoMax( na_, f.getNXA()                 );
    np = acadoMax( np_, f.getNP ()                 );
    nu = acadoMax( nu_, f.getNU ()                 );
    nw = acadoMax( nw_, f.getNW ()                 );
    nd = acadoMax( nd_, f.getNDX()                 );
    N  = acadoMax( N_ , f.getNumberOfVariables()+1 );

    if( N != 0 ) z = new double[N];
    else         z = 0            ;

    setZero( );

    idx = new int*[7 ];

    idx[0] = new int [1 ];
    idx[1] = new int [nx];
    idx[2] = new int [na];
    idx[3] = new int [np];
    idx[4] = new int [nu];
    idx[5] = new int [nw];
    idx[6] = new int [nd];

    idx[0][0] = f.index( VT_TIME, 0 );

    for( run1 = 0; run1 < nx; run1++ )
        idx[1][run1] = f.index( VT_DIFFERENTIAL_STATE, run1 );

    for( run1 = 0; run1 < na; run1++ )
        idx[2][run1] = f.index( VT_ALGEBRAIC_STATE, run1 );

    for( run1 = 0; run1 < np; run1++ )
        idx[3][run1] = f.index( VT_PARAMETER, run1 );

    for( run1 = 0; run1 < nu; run1++ )
        idx[4][run1] = f.index( VT_CONTROL, run1 );

    for( run1 = 0; run1 < nw; run1++ )
        idx[5][run1] = f.index( VT_DISTURBANCE, run1 );

    for( run1 = 0; run1 < nd; run1++ )
        idx[6][run1] = f.index( VT_DDIFFERENTIAL_STATE, run1 );

    return SUCCESSFUL_RETURN;
}