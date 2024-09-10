// input : current spectrum in the form of power *spec and phase *phase,
//         the last two earlier spectrums are at position
//         512 and 1024 of the corresponding Input-Arrays.
//         Array *vocal, which can mark an FFT_Linie as harmonic
// output: current amplitude *amp and unpredictability *cw
static void
CalcUnpred (PsyModel* m,
			const int     MaxLine,
			const float*  spec,
			const float*  phase,
			const int*    vocal,
			float*        amp0,
			float*        phs0,
			float*        cw )
{
    int     n;
    float   amp;
    float   tmp;
#define amp1  ((amp0) +  512)           // amp[ 512...1023] contains data of frame-1
#define amp2  ((amp0) + 1024)           // amp[1024...1535] contains data of frame-2
#define phs1  ((phs0) +  512)           // phs[ 512...1023] contains data of frame-1
#define phs2  ((phs0) + 1024)           // phs[1024...1535] contains data of frame-2


    for ( n = 0; n < MaxLine; n++ ) {
        tmp     = COSF  ((phs0[n] = phase[n]) - 2*phs1[n] + phs2[n]);   // copy phase to output-array, predict phase and calculate predictive error
        amp0[n] = SQRTF (spec[n]);                                      // calculate and set amplitude
        amp     = 2*amp1[n] - amp2[n];                                  // predict amplitude

        // calculate unpredictability
        cw[n] = SQRTF (spec[n] + amp * (amp - 2*amp0[n] * tmp)) / (amp0[n] + FABS(amp));
    }

    // postprocessing of harmonic FFT-lines (*cw is set to CVD_UNPRED)
	if ( m->CVD_used  &&  vocal != NULL ) {
        for ( n = 0; n < MAX_CVD_LINE; n++, cw++, vocal++ )
            if ( *vocal != 0  &&  *cw > CVD_UNPRED * 0.01 * *vocal )
                *cw = CVD_UNPRED * 0.01 * *vocal;
    }

    return;
}