// frame detection
void wlanframesync_execute_seekplcp(wlanframesync _q)
{
    _q->timer++;

    // TODO : only check every 100 - 150 (decimates/reduced complexity)
    if (_q->timer < 64)
        return;

    // reset timer
    _q->timer = 0;

    // read contents of input buffer
    float complex * rc;
    windowcf_read(_q->input_buffer, &rc);
    
    // estimate gain
    // TODO : use gain from result of FFT
    unsigned int i;
    float g = 0.0f;
    for (i=16; i<80; i+=4) {
        // compute |rc[i]|^2 efficiently
        g += crealf(rc[i  ])*crealf(rc[i  ]) + cimagf(rc[i  ])*cimagf(rc[i  ]);
        g += crealf(rc[i+1])*crealf(rc[i+1]) + cimagf(rc[i+1])*cimagf(rc[i+1]);
        g += crealf(rc[i+2])*crealf(rc[i+2]) + cimagf(rc[i+2])*cimagf(rc[i+2]);
        g += crealf(rc[i+3])*crealf(rc[i+3]) + cimagf(rc[i+3])*cimagf(rc[i+3]);
    }
    g = 64.0f / (g + 1e-12f);
    
    // save gain (permits dynamic invocation of get_rssi() method)
    _q->g0 = g;

    // estimate S0 gain
    wlanframesync_estimate_gain_S0(_q, &rc[16], _q->G0a);
    
    // compute S0 metrics
    float complex s_hat;
    wlanframesync_S0_metrics(_q, _q->G0a, &s_hat);
    s_hat *= g;

    float tau_hat  = cargf(s_hat) * (float)(16.0f) / (2*M_PI);
#if DEBUG_WLANFRAMESYNC_PRINT
    printf(" - gain=%12.3f, rssi=%8.2f dB, s_hat=%12.4f <%12.8f>, tau_hat=%8.3f\n",
            sqrt(g),
            -10*log10(g),
            cabsf(s_hat), cargf(s_hat),
            tau_hat);
#endif

    // 
    if (cabsf(s_hat) > WLANFRAMESYNC_S0A_ABS_THRESH) {

        int dt = (int)roundf(tau_hat);
        // set timer appropriately...
        _q->timer = (16 + dt) % 16;
        //_q->timer += 32; // add delay to help ensure good S0 estimate (multiple of 16)
        _q->state = WLANFRAMESYNC_STATE_RXSHORT0;

#if DEBUG_WLANFRAMESYNC_PRINT
        printf("********** frame detected! ************\n");
        printf("    s_hat   :   %12.8f <%12.8f>\n", cabsf(s_hat), cargf(s_hat));
        printf("  tau_hat   :   %12.8f\n", tau_hat);
        printf("    dt      :   %12d\n", dt);
        printf("    timer   :   %12u\n", _q->timer);
#endif
    }

}