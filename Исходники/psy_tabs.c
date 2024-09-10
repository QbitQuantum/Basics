// calculating the table for loudness calculation based on absLtq = ank
static void
Loudness_Tabelle (PsyModel* m)
{
    int    n;
    float  midfreq;
    float  tmp;

    // ca. dB(A)
    for ( n = 0; n < PART_LONG; n++ ){
		midfreq      = (MPC_WH[n] + MPC_WL[n] + 3) * (0.25 * m->SampleFreq / 512);     // center frequency in kHz, why +3 ???
        tmp          = LOG10 (midfreq) - 3.5f;                                  // dB(A)
        tmp          = -10 * tmp * tmp + 3 - midfreq/3000;
		m->tables.Loudness [n] = POW10 ( 0.1 * tmp );                                     // conversion into power
    }
}