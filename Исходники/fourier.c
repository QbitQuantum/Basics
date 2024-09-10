/* CKTfour() - perform fourier analysis of an output vector.
 *
 * Due to the construction of the program which places all the output
 * data in the post-processor, the fourier analysis can not be done
 * directly.  This function allows the post processor to hand back
 * vectors of time and data values to have the fourier analysis
 * performed on them.  */
static int
CKTfour(int ndata,              /* number of entries in the Time and
                                   Value arrays */
        int numFreq,            /* number of harmonics to calculate */
        double *thd,            /* total harmonic distortion (percent)
                                   to be returned */
        double *Time,           /* times at which the voltage/current
                                   values were measured*/
        double *Value,          /* voltage or current vector whose
                                   transform is desired */
        double FundFreq,        /* the fundamental frequency of the
                                   analysis */
        double *Freq,           /* the frequency value of the various
                                   harmonics */
        double *Mag,            /* the Magnitude of the fourier
                                   transform */
        double *Phase,          /* the Phase of the fourier transform */
        double *nMag,           /* the normalized magnitude of the
                                   transform: nMag(fund)=1*/
        double *nPhase)         /* the normalized phase of the
                                   transform: Nphase(fund)=0 */
{
    /* Note: we can consider these as a set of arrays.  The sizes are:
     * Time[ndata], Value[ndata], Freq[numFreq], Mag[numfreq],
     * Phase[numfreq], nMag[numfreq], nPhase[numfreq]
     *
     * The arrays must all be allocated by the caller.
     * The Time and Value array must be reasonably distributed over at
     * least one full period of the fundamental Frequency for the
     * fourier transform to be useful.  The function will take the
     * last period of the frequency as data for the transform.
     *
     * We are assuming that the caller has provided exactly one period
     * of the fundamental frequency.  */
    int i;
    int j;
    double tmp;

    NG_IGNORE(Time);

    /* clear output/computation arrays */

    for (i = 0; i < numFreq; i++) {
        Mag[i] = 0;
        Phase[i] = 0;
    }

    for (i = 0; i < ndata; i++)
        for (j = 0; j < numFreq; j++) {
            Mag[j]   += Value[i] * sin(j*2.0*M_PI*i/((double)ndata));
            Phase[j] += Value[i] * cos(j*2.0*M_PI*i/((double)ndata));
        }

    Mag[0] = Phase[0]/ndata;
    Phase[0] = nMag[0] = nPhase[0] = Freq[0] = 0;
    *thd = 0;
    for (i = 1; i < numFreq; i++) {
        tmp = Mag[i] * 2.0 / ndata;
        Phase[i] *= 2.0 / ndata;
        Freq[i] = i * FundFreq;
        Mag[i] = hypot(tmp, Phase[i]);
        Phase[i] = atan2(Phase[i], tmp) * 180.0/M_PI;
        nMag[i] = Mag[i] / Mag[1];
        nPhase[i] = Phase[i] - Phase[1];
        if (i > 1)
            *thd += nMag[i] * nMag[i];
    }
    *thd = 100*sqrt(*thd);
    return (OK);
}