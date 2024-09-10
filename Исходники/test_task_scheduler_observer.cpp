int TestMain () {
    if ( P < 2 )
        return Harness::Skipped;
    theNumObservers = 0;
    theWorkersBarrier.initialize(P);
    // Fully- and under-utilized mode
    for ( int M = 1; M < P; M <<= 1 ) {
        if ( M > P/2 ) {
            ASSERT( P & (P-1), "Can get here only in case of non power of two cores" );
            M = P/2;
            if ( M & (M-1) )
                break; // Already tested this configuration
        }
        int T = P / M;
        ASSERT( T > 1, NULL );
        REMARK( "Masters: %d; Arena size: %d\n", M, T );
        theMasterBarrier.initialize(M);
        theGlobalBarrier.initialize(M * T);
        TestObserver(M, T, 0);
        TestObserver(M, T, tmLocalObservation | ( T==P? tmAutoinitialization : 0) );
        CleanLocalState();
        TestObserver(M, T, tmSynchronized);
        TestObserver(M, T, tmSynchronized | tmLocalObservation
#if __TBB_TASK_ARENA
                     | ( T==P? tmLeavingControl : 0)
#endif
                     );
    }
    // Oversubscribed mode
    for ( int i = 0; i < 5; ++i ) {
        REMARK( "Masters: %d; Arena size: %d\n", P-1, P );
        TestObserver(P-1, P, 0);
        TestObserver(P-1, P, tmLocalObservation);
    }
    Harness::Sleep(20);
    return Harness::Done;
}