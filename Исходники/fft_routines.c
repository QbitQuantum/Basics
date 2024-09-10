// input : Signal *x
// output: energy spectrum *erg and phase spectrum *phs
void
PolarSpec1024 ( const float* x, float* erg, float* phs )
{
    int i;
    for( i = 0; i < 1024; i++ )
        a[i] = x[i] * Hann_1024[i];

    rdft( 1024, a, ip, w); // perform FFT

    // calculate power and phase
    for( i = 0; i < 512; ++i )
    {
        erg[i]  = a[i*2] * a[i*2] + a[i*2+1] * a[i*2+1];
        phs[i]  = ATAN2F( a[i*2+1], a[i*2] );  
    }
}