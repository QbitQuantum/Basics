void test_fp_and_80x87_math( void )
{
    double      dnum;
    int         inum;
#ifdef __FPI__
    unsigned    fp_status, fp_control, fp_mask, origbits, bits;
#endif

    printf( "Testing other floating point " );
#ifdef __FPI__
    printf( "and 80x87 specific " );
#endif
    printf( "functions...\n" );
    VERIFY( CompDbl( j0( 2.387 ), 0.009288 ) );
    VERIFY( CompDbl( j1( 2.387 ), 0.522941 ) );
    VERIFY( CompDbl( jn( 2, 2.387 ), 0.428870 ) );
    VERIFY( CompDbl( y0( 2.387 ), 0.511681 ) );
    VERIFY( CompDbl( y1( 2.387 ), 0.094374 ) );
    VERIFY( CompDbl( yn( 2, 2.387 ), -0.432608 ) );
    VERIFY( ceil( 1.0001 ) == 2.0 );
    VERIFY( ceil( -1.0001 ) == -1.0 );
    VERIFY( floor( 1.0001 ) == 1.0 );
    VERIFY( floor( -1.0001 ) == -2.0 );
    VERIFY( CompDbl( exp( 1.0 ), E ) );
    VERIFY( CompDbl( exp( 3.0 ), E * E * E ) );
    VERIFY( exp( 0.0 ) == 1.0 );
    VERIFY( fabs( -1.5 ) == 1.5 );
    VERIFY( fabs( 2.5 ) == 2.5 );
    VERIFY( fabs( 0.0 ) == 0.0 );
    VERIFY( fmod( 2.5, 0.5 ) == 0.0 );
    VERIFY( fmod( 4.5, 2.0 ) == 0.5 );
    VERIFY( fmod( -4.5, 2.0 ) == -0.5 );
    VERIFY( fmod( -7.5, -2.0 ) == -1.5 );
    dnum = frexp( 65535.0, &inum );
    VERIFY( inum == 16 );
    VERIFY( CompDbl( ldexp( dnum, inum ), 65535.0 ) );
    while( inum-- > 0 ) dnum *= 2;
    VERIFY( CompDbl( dnum, 65535.0 ) );
    VERIFY( CompDbl( log( E ), 1.0 ) );
    VERIFY( CompDbl( log( 1.0 ), 0.0 ) );
    VERIFY( CompDbl( log( 1.0 / E ), -1.0 ) );
    VERIFY( CompDbl( log10( 10.0 ), 1.0 ) );
    VERIFY( CompDbl( log10( 1 ), 0.0 ) );
    VERIFY( CompDbl( log10( 0.1 ), -1.0 ) );
#ifdef __WATCOMC__      /* Not in Microsoft libs. */
    VERIFY( CompDbl( log2( 65536.0 ), 16.0 ) );
    VERIFY( CompDbl( log2( 1 ), 0.0 ) );
    VERIFY( CompDbl( log2( 0.25 ), -2.0 ) );
#endif
    VERIFY( CompDbl( sqrt( 99980001.0 ), 9999.0 ) );
    dnum = 1.0/DBL_MIN;
    VERIFY( CompDbl( 1.0 / dnum, DBL_MIN ) );
    VERIFY( CompDbl( modf( PI, &dnum ), PI - 3.0 ) );
    VERIFY( dnum == 3.0 );
    VERIFY( CompDbl( modf( -PI, &dnum ) , - PI + 3.0 ) );
    VERIFY( dnum == -3.0 );
    VERIFY( pow( 1.0, 123456789.0 ) == 1.0 );
    VERIFY( pow( 2.0, 16.0 ) == 65536.0 );
    VERIFY( CompDbl( pow( E, log(1234.0) ), 1234.0 ) );
#ifdef __FPI__
    VERIFY( sqrt( -1 ) == 1 );
    // Now my_matherrno should == DOMAIN after calling sqrt( -1 )
    // If not, matherr() fails
    VERIFY( my_matherrno == DOMAIN );
    my_matherrno = 0;   // reset
    VERIFY( sqrt( 0 ) == 0 );
    VERIFY( my_matherrno == 0 );
    _fpreset();
    fp_status = _clear87();
    VERIFY( fp_status == 0 );
    //
    fp_status = _status87();
    VERIFY( fp_status == 0 );
    //
    _fpreset();
    fp_control = _control87( 0, 0 );
    bits = fp_control & MCW_IC;
    bits = (bits == IC_AFFINE) ? IC_PROJECTIVE : IC_AFFINE;
    fp_control = _control87( bits, MCW_IC );
    VERIFY( (fp_control & MCW_IC) ==  bits );
    bits = (bits == IC_AFFINE) ? IC_PROJECTIVE : IC_AFFINE;
    fp_control = _control87( bits, MCW_IC );
    VERIFY( (fp_control & MCW_IC) ==  bits );
    //
    fp_control = _control87( 0, 0 );
    origbits = fp_control & MCW_RC;
    bits = (origbits == RC_NEAR) ? RC_CHOP : RC_NEAR;
    fp_control = _control87( bits, MCW_RC );
    VERIFY( (fp_control & MCW_RC) ==  bits );
    fp_control = _control87( origbits, MCW_RC );
    VERIFY( (fp_control & MCW_RC) ==  origbits );
    //
    _fpreset();
    fp_control = 0;
    fp_mask = _EM_INEXACT;
    signal( SIGFPE, (void (*)(int))my_handler );
    (void)_control87( fp_control, fp_mask );
    q = a / b;
    VERIFY( sig_count > 0 );
    fp_control = _EM_INEXACT;
    (void)_control87( fp_control, fp_mask );
    sig_count = 0;
    q = a / b;
    VERIFY( sig_count == 0 );
    signal( SIGFPE, SIG_DFL );
#endif
}