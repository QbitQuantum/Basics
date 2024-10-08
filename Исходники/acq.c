bool acq_search(gnss_signal_t sid, float cf_min, float cf_max,
                float cf_bin_width, acq_result_t *acq_result)
{
    /* Configuration */
    u32 fft_len_log2 = FFT_LEN_LOG2_MAX;
    u32 fft_len = 1 << fft_len_log2;
    float fft_bin_width = NAP_ACQ_SAMPLE_RATE_Hz / fft_len;
    float chips_per_sample = CHIP_RATE / NAP_ACQ_SAMPLE_RATE_Hz;

    /* Generate, resample, and FFT code */
    static fft_cplx_t code_fft[FFT_LEN_MAX];
    code_resample(sid, chips_per_sample, code_fft, fft_len);
    if (!fft(code_fft, code_fft, fft_len_log2,
             FFT_DIR_FORWARD, FFT_SCALE_SCHED_CODE)) {
        return false;
    }

    /* FFT samples */
    u32 sample_count;
    static fft_cplx_t sample_fft[FFT_LEN_MAX];
    if(!fft_samples(FFT_SAMPLES_INPUT, sample_fft, fft_len_log2,
                    FFT_DIR_FORWARD, FFT_SCALE_SCHED_SAMPLES, &sample_count)) {
        return false;
    }

    /* Search for results */
    float best_mag_sq = 0.0f;
    float best_mag_sq_sum = 0.0f;
    float best_doppler = 0.0f;
    u32 best_sample_offset = 0;

    /* Loop over Doppler bins */
    s32 doppler_bin_min = (s32)floorf(cf_min / cf_bin_width);
    s32 doppler_bin_max = (s32)floorf(cf_max / cf_bin_width);
    for (s32 doppler_bin = doppler_bin_min; doppler_bin <= doppler_bin_max;
            doppler_bin++) {

        s32 sample_offset = (s32)roundf(doppler_bin * cf_bin_width / fft_bin_width);
        /* Actual computed Doppler */
        float doppler = sample_offset * fft_bin_width;

        /* Multiply sample FFT by shifted conjugate code FFT */
        static fft_cplx_t result_fft[FFT_LEN_MAX];
        for (u32 i=0; i<fft_len; i++) {
            const fft_cplx_t *a = &code_fft[i];
            const fft_cplx_t *b = &sample_fft[(i + sample_offset) & (fft_len - 1)];
            fft_cplx_t *r = &result_fft[i];

            s32 a_re = (s32)a->re;
            s32 a_im = (s32)a->im;
            s32 b_re = (s32)b->re;
            s32 b_im = (s32)b->im;

            r->re = ((a_re * b_re) + (a_im * b_im)) / RESULT_DIV;
            r->im = ((a_re * -b_im) + (a_im * b_re)) / RESULT_DIV;
        }

        /* Inverse FFT */
        if (!fft(result_fft, result_fft, fft_len_log2,
                 FFT_DIR_BACKWARD, FFT_SCALE_SCHED_INV)) {
            return false;
        }

        /* Peak search */
        float mag_sq_sum = 0.0f;
        bool match = false;
        for (u32 i=0; i<fft_len; i++) {
            const fft_cplx_t *r = &result_fft[i];

            float re = (float)r->re;
            float im = (float)r->im;
            float mag_sq = re*re + im*im;
            mag_sq_sum += mag_sq;

            if (mag_sq > best_mag_sq) {
                best_mag_sq = mag_sq;
                best_doppler = doppler;
                best_sample_offset = i;
                match = true;
            }
        }

        if (match) {
            best_mag_sq_sum = mag_sq_sum;
        }
    }

    /* Account for non-integer number of codes and circular convolution:
     * If correlation peak is in the first half of the buffer, most samples
     * have NOT wrapped, so assume a positive shift.
     * If correlation peak is in the second half of the buffer, most samples
     * HAVE wrapped, so assume a negative shift. */
    s32 corrected_sample_offset = (best_sample_offset < fft_len/2) ?
                                  (s32)best_sample_offset :
                                  (s32)best_sample_offset - (s32)fft_len;

    /* Compute code phase */
    float cp = chips_per_sample * corrected_sample_offset;
    /* Modulus code length */
    cp -= CODE_LENGTH * floorf(cp / CODE_LENGTH);

    /* Compute C/N0 */
    float snr = best_mag_sq / (best_mag_sq_sum / fft_len);
    float cn0 = 10.0f * log10f(snr)
                + 10.0f * log10f(fft_bin_width); /* Bandwidth */

    /* Set output */
    acq_result->sample_count = sample_count;
    acq_result->cp = cp;
    acq_result->cf = best_doppler;
    acq_result->cn0 = cn0;
    return true;
}