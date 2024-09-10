int bench_stat( long count )
{
    long		l ;
    struct STAT	st ;

    int		nret ;

    for( l = 0 ; l < count ; l++ )
    {
        nret = STAT( PATHFILENAME , & st ) ;
        if( nret )
        {
            printf( "stat failed[%d] , errno[%d]\n" , nret , errno );
            return -1;
        }
    }

    return 0;
}