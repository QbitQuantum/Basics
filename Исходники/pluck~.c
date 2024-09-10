static t_int *pluck_perform(t_int *w){
    t_pluck *x = (t_pluck *)(w[1]);
    int n = (int)(w[2]);
    t_random_state *rstate = (t_random_state *)(w[3]);
    t_float *hz_in = (t_float *)(w[4]);
    t_float *t_in = (t_float *)(w[5]);
    t_float *ain = (t_float *)(w[6]);
    t_float *cut_in = (t_float *)(w[7]);
    t_float *out = (t_float *)(w[8]);
    uint32_t *s1 = &rstate->s1;
    uint32_t *s2 = &rstate->s2;
    uint32_t *s3 = &rstate->s3;
    t_float sr = x->x_sr;
    t_float last_trig = x->x_last_trig;
    t_float sum = x->x_sum;
    t_float amp = x->x_amp;
    double xnm1 = x->x_xnm1;
    double xnm2 = x->x_xnm2;
    double ynm1 = x->x_ynm1;
    double ynm2 = x->x_ynm2;
    for(t_int i = 0; i < n; i++){
        t_float hz = hz_in[i];
        t_float trig = t_in[i];
        if(hz < 1){
            out[i] = sum = 0;
            xnm1 = xnm2 = ynm1 = ynm2 = 0;
        }
        else{
            float period = 1./hz;
            float delms = period * 1000;
            t_int samps = (int)roundf(period * sr);
            double fb_del = pluck_read_delay(x, x->x_ybuf, samps); // get delayed vals
            if (ain[i] == 0)
                ain[i] = 0;
            else
                ain[i] = copysign(exp(log(0.001) * delms/fabs(ain[i])), ain[i]);
            if(trig != 0 && last_trig == 0){
                sum = 0;
                amp = trig;
            }
// Filter stuff
            double cuttoff = (double)cut_in[i];
            double omega, alphaQ, cos_w, a0, a1, a2, b0, b1, b2, yn;
            double nyq = (sr * 0.5);
            double hz2rad = PI/nyq;
            if (cuttoff < 0.000001)
                cuttoff = 0.000001;
            if (cuttoff > nyq - 0.000001)
                cuttoff = nyq - 0.000001;
            omega = cuttoff * hz2rad;
            alphaQ = sin(omega); // q = 0.5
            cos_w = cos(omega);
            b0 = alphaQ + 1;
            a0 = (1 - cos_w) / (2 * b0);
            a1 = (1 - cos_w) / b0;
            a2 = a0;
            b1 = 2*cos_w / b0;
            b2 = (alphaQ - 1) / b0;
            // gate
            t_float gate = (sum++ <= samps) * amp;
            // noise
            t_float noise;
            if(gate != 0)
                noise = (t_float)(random_frand(s1, s2, s3)) * gate;
            else
                noise = 0;
            // output
            double output = (double)noise + (double)ain[i] * fb_del;
            out[i] = output;
            // filter
            yn = a0 * output + a1 * xnm1 + a2 * xnm2 + b1 * ynm1 + b2 * ynm2;
            // put into delay buffer
            int wh = x->x_wh;
            x->x_ybuf[wh] = yn;
            x->x_wh = (wh + 1) % x->x_sz; // increment writehead
            last_trig = trig;
            xnm2 = xnm1;
            xnm1 = output;
            ynm2 = ynm1;
            ynm1 = yn;
        }
    };
    x->x_sum = sum; // next
    x->x_last_trig = amp;
    x->x_last_trig = last_trig;
    x->x_xnm1 = xnm1;
    x->x_xnm2 = xnm2;
    x->x_ynm1 = ynm1;
    x->x_ynm2 = ynm2;
    return(w+9);
}