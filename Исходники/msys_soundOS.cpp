long msys_soundGetPosInSamples( void )
{
    MMTIME  mmt;

    mmt.wType = TIME_SAMPLES;
    waveOutGetPosition( h, &mmt, sizeof(MMTIME) );

	return mmt.u.cb;
}