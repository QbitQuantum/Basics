void ampmodem_demodulate(ampmodem _q,
                         float complex _y,
                         float *_x)
{
#if DEBUG_AMPMODEM
    windowcf_push(_q->debug_x, _y);
#endif

    if (_q->suppressed_carrier) {
        // single side-band suppressed carrier
        if (_q->type != LIQUID_AMPMODEM_DSB) {
            *_x = crealf(_y);
            return;
        }

        // coherent demodulation
        
        // mix signal down
        float complex y_hat;
        nco_crcf_mix_down(_q->oscillator, _y, &y_hat);

        // compute phase error
        float phase_error = tanhf( crealf(y_hat) * cimagf(y_hat) );
#if DEBUG_AMPMODEM
        // compute frequency error
        float nco_freq   = nco_crcf_get_frequency(_q->oscillator);
        float freq_error = nco_freq/(2*M_PI) - _q->fc/(2*M_PI);

        // retain phase and frequency errors
        windowf_push(_q->debug_phase_error, phase_error);
        windowf_push(_q->debug_freq_error, freq_error);
#endif

        // adjust nco, pll objects
        nco_crcf_pll_step(_q->oscillator, phase_error);

        // step NCO
        nco_crcf_step(_q->oscillator);

        // set output
        *_x = crealf(y_hat);
    } else {
        // non-coherent demodulation (peak detector)
        float t = cabsf(_y);

        // remove DC bias
        _q->ssb_q_hat = (    _q->ssb_alpha)*t +
                        (1 - _q->ssb_alpha)*_q->ssb_q_hat;
        *_x = 2.0f*(t - _q->ssb_q_hat);
    }
}