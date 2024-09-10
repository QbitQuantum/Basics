void ff_lowpass_init(LPFilterContext *s, float sample_rate, float fpass, float fstop, float apass, float astop){
    int i, j;
    float fp = sample_rate*tanf(M_PI*fpass/sample_rate)/M_PI;
    float fs = sample_rate*tanf(M_PI*fstop/sample_rate)/M_PI;
    float ws = fs/fp;
    float vp = 2*M_PI*fp;
    int   N = (int)ceilf(log10f((pow(10, astop/10)-1) / (pow(10, apass/10)-1))/(2*log10f(ws)));
    float w0 = ws/pow(pow(10, astop/10)-1, 1.0/(2.0*N));
    float dfi0 = M_PI/N;
    complex *p, *pt;
    complex gain = 1.0;

    p = av_malloc(N*sizeof(*p));
    pt = av_malloc((N+1)*sizeof(*pt));
    for(i=0; i<2; i++){
        s->filterCoeffs[i] = av_malloc((N+1)*sizeof(*s->filterCoeffs[i]));
        s->buf[i] = av_malloc((N+1)*sizeof(*s->buf[i]));
    }
    for(i=0; i<N; i++){
        s->buf[0][i] = s->buf[1][i] = 0;
    }

    av_log(NULL, AV_LOG_DEBUG, "fp=%f fs=%f\n", fp, fs);
    av_log(NULL, AV_LOG_DEBUG, "vp=%f\n", vp);
    av_log(NULL, AV_LOG_DEBUG, "ws=%f\n", ws);
    av_log(NULL, AV_LOG_DEBUG, "N=%i w0=%f\n", N, w0);

    for(i=0; i<N; i++){
        p[i] = w0 * cexp(I*(M_PI/2.0 + (i+0.5)*dfi0));
        gain *= -p[i];
        p[i] *= vp;
        gain *= vp/(2.0*sample_rate-p[i]);
        p[i] = (2.0*sample_rate+p[i])/(2.0*sample_rate-p[i]);
        av_log(NULL, AV_LOG_DEBUG, "p[%i]=%f+%fI\n", i, creal(p[i]), cimag(p[i]));
    }

    av_log(NULL, AV_LOG_DEBUG, "gain=%f+%fI\n", creal(gain), cimag(gain));

    for(i=0; i<N; i++){
        pt[i] = 1;
        for(j=i; j>0; j--)
            pt[j] = -pt[j]*p[i] + pt[j-1];
        pt[0] *= -p[i];
    }
    for(i=0; i<=N; i++){
        av_log(NULL, AV_LOG_DEBUG, "a %i: %f\n", i, creal(pt[i]));
    }
    pt[N]=1;
    for(i=0; i<=N/2; i++){
        complex t;
        t=pt[i];
        pt[i] = pt[N-i];
        pt[N-i] = t;
    }
    for(i=0; i<=N; i++){
        av_log(NULL, AV_LOG_DEBUG, "%i: %f\n", i, creal(pt[i]));
    }

    for(i=0; i<N; i++)
        s->filterCoeffs[0][i] = creal(pt[i+1]);
    s->filterCoeffs[0][N] = 0;

    av_free(p);
    av_free(pt);

    for(i=0; i<N; i++){
        s->filterCoeffs[1][i] = gain;
        for(j=i; j>0; j--)
            s->filterCoeffs[1][j] = s->filterCoeffs[1][j] + s->filterCoeffs[1][j-1];
    }
    s->filterCoeffs[1][N] = gain;

    for(i=0; i<=N; i++){
        av_log(NULL, AV_LOG_DEBUG, "%i: ac=%f bc=%f\n", i, s->filterCoeffs[0][i], s->filterCoeffs[1][i]);
    }
    s->N = N;
}