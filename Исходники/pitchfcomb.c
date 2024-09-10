/* input must be stepsize long */
void
aubio_pitchfcomb_do (aubio_pitchfcomb_t * p, const fvec_t * input, fvec_t * output)
{
    uint_t k, l, maxharm = 0;
    smpl_t phaseDifference = TWO_PI * (smpl_t) p->stepSize / (smpl_t) p->fftSize;
    aubio_fpeak_t peaks[MAX_PEAKS];

    for (k = 0; k < MAX_PEAKS; k++) {
        peaks[k].db = -200.;
        peaks[k].bin = 0.;
    }

    for (k = 0; k < input->length; k++) {
        p->winput->data[k] = p->win->data[k] * input->data[k];
    }
    aubio_fft_do (p->fft, p->winput, p->fftOut);

    for (k = 0; k <= p->fftSize / 2; k++) {
        smpl_t
        magnitude =
            20. * LOG10 (2. * p->fftOut->norm[k] / (smpl_t) p->fftSize),
            phase = p->fftOut->phas[k], tmp, bin;

        /* compute phase difference */
        tmp = phase - p->fftLastPhase->data[k];
        p->fftLastPhase->data[k] = phase;

        /* subtract expected phase difference */
        tmp -= (smpl_t) k *phaseDifference;

        /* map delta phase into +/- Pi interval */
        tmp = aubio_unwrap2pi (tmp);

        /* get deviation from bin frequency from the +/- Pi interval */
        tmp = p->fftSize / (smpl_t) p->stepSize * tmp / (TWO_PI);

        /* compute the k-th partials' true bin */
        bin = (smpl_t) k + tmp;

        if (bin > 0.0 && magnitude > peaks[0].db) {       // && magnitude < 0) {
            memmove (peaks + 1, peaks, sizeof (aubio_fpeak_t) * (MAX_PEAKS - 1));
            peaks[0].bin = bin;
            peaks[0].db = magnitude;
        }
    }

    k = 0;
    for (l = 1; l < MAX_PEAKS && peaks[l].bin > 0.0; l++) {
        sint_t harmonic;
        for (harmonic = 5; harmonic > 1; harmonic--) {
            if (peaks[0].bin / peaks[l].bin < harmonic + .02 &&
                    peaks[0].bin / peaks[l].bin > harmonic - .02) {
                if (harmonic > (sint_t) maxharm && peaks[0].db < peaks[l].db / 2) {
                    maxharm = harmonic;
                    k = l;
                }
            }
        }
    }
    output->data[0] = peaks[k].bin;
    /* quick hack to clean output a bit */
    if (peaks[k].bin > 5000.)
        output->data[0] = 0.;
}