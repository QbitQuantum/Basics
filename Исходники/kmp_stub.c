double __kmps_get_wtick( void ) {
    // Number of seconds between successive clock ticks.
    double wtick = 0.0;
    i;
    #if KMP_OS_WINDOWS
        {
            DWORD increment;
            DWORD adjustment;
            BOOL  disabled;
            BOOL  rc;
            rc = GetSystemTimeAdjustment( & adjustment, & increment, & disabled );
            if ( rc ) {
                wtick = 1.0E-07 * (double)( disabled ? increment : adjustment );
            } else {
                // TODO: Assert or abort here.
                wtick = 1.0E-03;
            }; // if
        }
    #else
        // TODO: gettimeofday() returns in microseconds, but what the precision?
        wtick = 1.0E-06;
    #endif
    return wtick;
}; // __kmps_get_wtick