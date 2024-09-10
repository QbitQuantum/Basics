/* creates a waveform in the frequency domain; the waveform might be generated
 * in the time-domain and transformed */
int create_fd_waveform(COMPLEX16FrequencySeries ** htilde_plus, COMPLEX16FrequencySeries ** htilde_cross, struct params p)
{
    clock_t timer_start = 0;
    double chirplen, deltaF;
    int chirplen_exp;

    /* length of the chirp in samples */
    chirplen = imr_time_bound(p.f_min, p.m1, p.m2, p.s1z, p.s2z) * p.srate;
    /* make chirplen next power of two */
    frexp(chirplen, &chirplen_exp);
    chirplen = ldexp(1.0, chirplen_exp);
    deltaF = p.srate / chirplen;
    if (p.verbose)
        fprintf(stderr, "using frequency resolution deltaF = %g Hz\n", deltaF);

    if (p.condition) {
        if (p.verbose) {
            fprintf(stderr, "generating waveform in frequency domain using XLALSimInspiralFD...\n");
            timer_start = clock();
        }
        XLALSimInspiralFD(htilde_plus, htilde_cross, p.m1, p.m2, p.s1x, p.s1y, p.s1z, p.s2x, p.s2y, p.s2z, p.distance, p.inclination, p.phiRef, p.longAscNodes, p.eccentricity, p.meanPerAno, deltaF, p.f_min, 0.5 * p.srate, p.fRef, p.params, p.approx);
        if (p.verbose)
            fprintf(stderr, "generation took %g seconds\n", (double)(clock() - timer_start) / CLOCKS_PER_SEC);
    } else if (p.domain == LAL_SIM_DOMAIN_FREQUENCY) {
        if (p.verbose) {
            fprintf(stderr, "generating waveform in frequency domain using XLALSimInspiralChooseFDWaveform...\n");
            timer_start = clock();
        }
        XLALSimInspiralChooseFDWaveform(htilde_plus, htilde_cross, p.m1, p.m2, p.s1x, p.s1y, p.s1z, p.s2x, p.s2y, p.s2z, p.distance, p.inclination, p.phiRef, p.longAscNodes, p.eccentricity, p.meanPerAno, deltaF, p.f_min, 0.5 * p.srate, p.fRef, p.params, p.approx);
        if (p.verbose)
            fprintf(stderr, "generation took %g seconds\n", (double)(clock() - timer_start) / CLOCKS_PER_SEC);
    } else {
        REAL8TimeSeries *h_plus = NULL;
        REAL8TimeSeries *h_cross = NULL;
        REAL8FFTPlan *plan;

        /* generate time domain waveform */
        if (p.verbose) {
            fprintf(stderr, "generating waveform in time domain using XLALSimInspiralChooseTDWaveform...\n");
            timer_start = clock();
        }
        XLALSimInspiralChooseTDWaveform(&h_plus, &h_cross, p.m1, p.m2, p.s1x, p.s1y, p.s1z, p.s2x, p.s2y, p.s2z, p.distance, p.inclination, p.phiRef, p.longAscNodes, p.eccentricity, p.meanPerAno, 1.0 / p.srate, p.f_min, p.fRef, p.params, p.approx);
        if (p.verbose)
            fprintf(stderr, "generation took %g seconds\n", (double)(clock() - timer_start) / CLOCKS_PER_SEC);

        /* resize the waveforms to the required length */
        XLALResizeREAL8TimeSeries(h_plus, h_plus->data->length - (size_t) chirplen, (size_t) chirplen);
        XLALResizeREAL8TimeSeries(h_cross, h_cross->data->length - (size_t) chirplen, (size_t) chirplen);

        /* put the waveform in the frequency domain */
        /* (the units will correct themselves) */
        if (p.verbose) {
            fprintf(stderr, "transforming waveform to frequency domain...\n");
            timer_start = clock();
        }
        *htilde_plus = XLALCreateCOMPLEX16FrequencySeries("htilde_plus", &h_plus->epoch, 0.0, deltaF, &lalDimensionlessUnit, (size_t) chirplen / 2 + 1);
        *htilde_cross = XLALCreateCOMPLEX16FrequencySeries("htilde_cross", &h_cross->epoch, 0.0, deltaF, &lalDimensionlessUnit, (size_t) chirplen / 2 + 1);
        plan = XLALCreateForwardREAL8FFTPlan((size_t) chirplen, 0);
        XLALREAL8TimeFreqFFT(*htilde_cross, h_cross, plan);
        XLALREAL8TimeFreqFFT(*htilde_plus, h_plus, plan);
        if (p.verbose)
            fprintf(stderr, "transformation took %g seconds\n", (double)(clock() - timer_start) / CLOCKS_PER_SEC);

        /* clean up */
        XLALDestroyREAL8FFTPlan(plan);
        XLALDestroyREAL8TimeSeries(h_cross);
        XLALDestroyREAL8TimeSeries(h_plus);
    }
    return 0;
}