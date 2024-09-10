// create fskdem object (frequency demodulator)
//  _m          :   bits per symbol, _m > 0
//  _k          :   samples/symbol, _k >= 2^_m
//  _bandwidth  :   total signal bandwidth, (0,0.5)
fskdem fskdem_create(unsigned int _m,
                     unsigned int _k,
                     float        _bandwidth)
{
    // validate input
    if (_m == 0) {
        fprintf(stderr,"error: fskdem_create(), bits/symbol must be greater than 0\n");
        exit(1);
    } else if (_k < 2 || _k > 2048) {
        fprintf(stderr,"error: fskdem_create(), samples/symbol must be in [2^_m, 2048]\n");
        exit(1);
    } else if (_bandwidth <= 0.0f || _bandwidth >= 0.5f) {
        fprintf(stderr,"error: fskdem_create(), bandwidth must be in (0,0.5)\n");
        exit(1);
    }

    // create main object memory
    fskdem q = (fskdem) malloc(sizeof(struct fskdem_s));

    // set basic internal properties
    q->m         = _m;              // bits per symbol
    q->k         = _k;              // samples per symbol
    q->bandwidth = _bandwidth;      // signal bandwidth

    // derived values
    q->M  = 1 << q->m;              // constellation size
    q->M2 = 0.5f*(float)(q->M-1);   // (M-1)/2

    // compute demodulation FFT size such that FFT output bin frequencies are
    // as close to modulated frequencies as possible
    float        df = q->bandwidth / q->M2;         // frequency spacing
    float        err_min = 1e9f;                    // minimum error value
    unsigned int K_min = q->k;                      // minimum FFT size
    unsigned int K_max = q->k*4 < 16 ? 16 : q->k*4; // maximum FFT size
    unsigned int K_hat;
    for (K_hat=K_min; K_hat<=K_max; K_hat++) {
        // compute candidate FFT size
        float v     = 0.5f*df*(float)K_hat;         // bin spacing
        float err = fabsf( roundf(v) - v );         // fractional bin spacing

#if DEBUG_FSKDEM
        // print results
        printf("  K_hat = %4u : v = %12.8f, err=%12.8f %s\n", K_hat, v, err, err < err_min ? "*" : "");
#endif

        // save best result
        if (K_hat==K_min || err < err_min) {
            q->K    = K_hat;
            err_min = err;
        }

        // perfect match; no need to continue searching
        if (err < 1e-6f)
            break;
    }
    
    // determine demodulation mapping between tones and frequency bins
    // TODO: use gray coding
    q->demod_map = (unsigned int *) malloc(q->M * sizeof(unsigned int));
    unsigned int i;
    for (i=0; i<q->M; i++) {
        // print frequency bins
        float freq = ((float)i - q->M2) * q->bandwidth / q->M2;
        float idx  = freq * (float)(q->K);
        unsigned int index = (unsigned int) (idx < 0 ? roundf(idx + q->K) : roundf(idx));
        q->demod_map[i] = index;
#if DEBUG_FSKDEM
        printf("  s=%3u, f = %12.8f, index=%3u\n", i, freq, index);
#endif
    }

    // check for uniqueness
    for (i=1; i<q->M; i++) {
        if (q->demod_map[i] == q->demod_map[i-1]) {
            fprintf(stderr,"warning: fskdem_create(), demod map is not unique; consider increasing bandwidth\n");
            break;
        }
    }

    // allocate memory for transform
    q->buf_time = (float complex*) malloc(q->K * sizeof(float complex));
    q->buf_freq = (float complex*) malloc(q->K * sizeof(float complex));
    q->fft = FFT_CREATE_PLAN(q->K, q->buf_time, q->buf_freq, FFT_DIR_FORWARD, 0);

    // reset modem object
    fskdem_reset(q);

    // return main object
    return q;
}