float EDIT_scale_misfit( int nxyz , float fac , short *sar , float *far )
{
    float sf , ff , sum=0.0f , df ;
    int ii , nf=0 ;

    ENTRY("EDIT_scale_misfit") ;

    if( nxyz <= 0 || sar == NULL || far == NULL ) RETURN(0.0f) ;

    if( fac == 0.0f ) fac = 1.0f ;
    df = 1.0f / fac ;

    for( ii=0 ; ii < nxyz ; ii++ ) {
        if( BAD(ii) ) continue ;
        ff = far[ii] ;
        if( ff == 0.0f ) continue ;
        sf = (short)rintf(fac*sar[ii]) ;
        if( sf == 0.0f ) {
            if( fabsf(ff) < df ) sum += fabsf(ff)*fac ;
            else                 sum += 1.0f ;
        } else {
            sf = fabsf((sf-ff)/ff) ;
            if( sf > 1.0f ) sf = 1.0f ;
            sum += sf ;
        }
        nf++ ;
    }

    if( nf > 0 ) sum /= nf ;
    RETURN(sum) ;
}