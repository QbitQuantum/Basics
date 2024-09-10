_WCRTLINK int wait( int *status )
    {
        return( cwait( status, 0, 0 ) );
    }