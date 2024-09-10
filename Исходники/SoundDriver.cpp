CADENCII_MEDIA_HELPER_API(double, SoundGetPosition)() {
    if ( NULL == wave_out ) {
        return 0.0;
    }

    MMTIME mmt;
    mmt.wType = TIME_MS;
    EnterCriticalSection( &locker );
    waveOutGetPosition( wave_out, &mmt, sizeof( MMTIME ) );
    LeaveCriticalSection( &locker );
    float ms = 0.0f;
    switch ( mmt.wType ) {
        case TIME_MS:
            return mmt.u.ms * 0.001;
        case TIME_SAMPLES:
            return (double)mmt.u.sample / (double)wave_format.nSamplesPerSec;
        case TIME_BYTES:
            return (double)mmt.u.cb / (double)wave_format.nAvgBytesPerSec;
        default:
            return 0.0;
    }
    return 0.0;
}