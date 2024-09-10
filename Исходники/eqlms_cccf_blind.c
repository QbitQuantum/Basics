int main(int argc, char*argv[])
{
    // options
    unsigned int num_symbols=500;   // number of symbols to observe
    float SNRdB = 30.0f;            // signal-to-noise ratio [dB]
    unsigned int hc_len=5;          // channel filter length
    unsigned int k=2;               // matched filter samples/symbol
    unsigned int m=3;               // matched filter delay (symbols)
    float beta=0.3f;                // matched filter excess bandwidth factor
    unsigned int p=3;               // equalizer length (symbols, gr_len = 2*k*p+1)
    float mu = 0.09f;               // LMS learning rate

    // modulation type/depth
    modulation_scheme ms = LIQUID_MODEM_QPSK;
    
    // plotting options
    unsigned int nfft = 512;    // fft size
    float gnuplot_version = 4.2;
    char filename_base[256] = "figures.gen/eqlms_cccf_blind";

    int dopt;
    while ((dopt = getopt(argc,argv,"hf:g:n:s:c:k:m:b:p:u:M:")) != EOF) {
        switch (dopt) {
        case 'h': usage();                      return 0;
        case 'f': strncpy(filename_base,optarg,256);    break;
        case 'g': gnuplot_version = atoi(optarg);       break;
        case 'n': num_symbols   = atoi(optarg); break;
        case 's': SNRdB         = atof(optarg); break;
        case 'c': hc_len        = atoi(optarg); break;
        case 'k': k             = atoi(optarg); break;
        case 'm': m             = atoi(optarg); break;
        case 'b': beta          = atof(optarg); break;
        case 'p': p             = atoi(optarg); break;
        case 'u': mu            = atof(optarg); break;
        case 'M':
            ms = liquid_getopt_str2mod(optarg);
            if (ms == LIQUID_MODEM_UNKNOWN) {
                fprintf(stderr,"error: %s, unknown/unsupported modulation scheme '%s'\n", argv[0], optarg);
                return 1;
            }
            break;
        default:
            exit(1);
        }
    }

    // validate input
    if (num_symbols == 0) {
        fprintf(stderr,"error: %s, number of symbols must be greater than zero\n", argv[0]);
        exit(1);
    } else if (hc_len == 0) {
        fprintf(stderr,"error: %s, channel must have at least 1 tap\n", argv[0]);
        exit(1);
    } else if (k < 2) {
        fprintf(stderr,"error: %s, samples/symbol must be at least 2\n", argv[0]);
        exit(1);
    } else if (m == 0) {
        fprintf(stderr,"error: %s, filter semi-length must be at least 1 symbol\n", argv[0]);
        exit(1);
    } else if (beta < 0.0f || beta > 1.0f) {
        fprintf(stderr,"error: %s, filter excess bandwidth must be in [0,1]\n", argv[0]);
        exit(1);
    } else if (p == 0) {
        fprintf(stderr,"error: %s, equalizer semi-length must be at least 1 symbol\n", argv[0]);
        exit(1);
    } else if (mu < 0.0f || mu > 1.0f) {
        fprintf(stderr,"error: %s, equalizer learning rate must be in [0,1]\n", argv[0]);
        exit(1);
    }

    // set 'random' seed on options
    srand( hc_len + p + nfft );

    // derived values
    unsigned int gt_len = 2*k*m+1;   // matched filter length
    unsigned int gr_len = 2*k*p+1;   // equalizer filter length
    unsigned int num_samples = k*num_symbols;

    // bookkeeping variables
    float complex sym_tx[num_symbols];  // transmitted data sequence
    float complex x[num_samples];       // interpolated time series
    float complex y[num_samples];       // channel output
    float complex z[num_samples];       // equalized output

    // least mean-squares (LMS) equalizer
    float mse[num_symbols];             // equalizer mean-squared error
    float complex gr[gr_len];           // equalizer filter coefficients

    unsigned int i;

    // generate matched filter response
    float gtf[gt_len];                   // matched filter response
    liquid_firdes_rnyquist(LIQUID_RNYQUIST_RRC, k, m, beta, 0.0f, gtf);
    
    // convert to complex coefficients
    float complex gt[gt_len];
    for (i=0; i<gt_len; i++)
        gt[i] = gtf[i]; //+ 0.1f*(randnf() + _Complex_I*randnf());

    // create interpolator
    interp_cccf interp = interp_cccf_create(k, gt, gt_len);

    // create the modem objects
    modem mod   = modem_create(ms);
    modem demod = modem_create(ms);
    unsigned int bps = modem_get_bps(mod);
    unsigned int M = 1 << bps;

    // generate channel impulse response, filter
#if 0
    float complex hc[hc_len];           // channel filter coefficients
    hc[0] = 1.0f;
    for (i=1; i<hc_len; i++)
        hc[i] = 0.09f*(randnf() + randnf()*_Complex_I);
#else
    // use fixed channel
    hc_len = 8;
    float complex hc[hc_len];           // channel filter coefficients
    hc[0] =   1.00000000+  0.00000000*_Complex_I;
    hc[1] =   0.08077553+ -0.00247592*_Complex_I;
    hc[2] =   0.03625883+ -0.09219734*_Complex_I;
    hc[3] =   0.05764082+  0.03277601*_Complex_I;
    hc[4] =  -0.04773349+ -0.18766306*_Complex_I;
    hc[5] =  -0.00101735+ -0.00270737*_Complex_I;
    hc[6] =  -0.05796884+ -0.12665297*_Complex_I;
    hc[7] =   0.03805391+ -0.07609370*_Complex_I;
#endif
    firfilt_cccf fchannel = firfilt_cccf_create(hc, hc_len);
    firfilt_cccf_print(fchannel);

    // generate random symbols
    for (i=0; i<num_symbols; i++)
        modem_modulate(mod, rand()%M, &sym_tx[i]);

    // interpolate
    for (i=0; i<num_symbols; i++)
        interp_cccf_execute(interp, sym_tx[i], &x[i*k]);
    
    // push through channel
    float nstd = powf(10.0f, -SNRdB/20.0f);
    for (i=0; i<num_samples; i++) {
        firfilt_cccf_push(fchannel, x[i]);
        firfilt_cccf_execute(fchannel, &y[i]);

        // add noise
        y[i] += nstd*(randnf() + randnf()*_Complex_I)*M_SQRT1_2;
    }

    // push through equalizers
    float grf[gr_len];
    liquid_firdes_rnyquist(LIQUID_RNYQUIST_RRC, k, p, beta, 0.0f, grf);
    for (i=0; i<gr_len; i++) {
        gr[i] = grf[i] / (float)k;
    }

    // create LMS equalizer
    eqlms_cccf eq = eqlms_cccf_create(gr, gr_len);
    eqlms_cccf_set_bw(eq, mu);

    // filtered error vector magnitude (emperical MSE)
    //float zeta=0.05f;   // smoothing factor (small zeta -> smooth MSE)

    float complex d_hat = 0.0f;
    unsigned int num_symbols_rx=0;
    for (i=0; i<num_samples; i++) {

        // push samples into equalizers
        eqlms_cccf_push(eq, y[i]);

        // compute outputs
        eqlms_cccf_execute(eq, &d_hat);

        // store outputs
        z[i] = d_hat;

        // check to see if buffer is full
        if ( i < gr_len) continue;

        // decimate by k
        if ( (i%k) != 0 ) continue;

        // estimate transmitted signal
        unsigned int sym_out;       // output symbol
        float complex d_prime;  // estimated input sample

        // LMS
        modem_demodulate(demod, d_hat, &sym_out);
        modem_get_demodulator_sample(demod, &d_prime);

        // update equalizers
        eqlms_cccf_step(eq, d_prime, d_hat);

#if 0
        // update filtered evm estimate
        float evm = crealf( (d_prime-d_hat)*conjf(d_prime-d_hat) );

        if (num_symbols_rx == 0) {
            mse[num_symbols_rx] = evm; 
        } else {
            mse[num_symbols_rx] = mse[num_symbols_rx-1]*(1-zeta) + evm*zeta;
        }
#else
        // compute ISI for entire system
        eqlms_cccf_get_weights(eq, gr);
        mse[num_symbols_rx] = eqlms_cccf_isi(k, gt, gt_len, hc, hc_len, gr, gr_len);
#endif

        // print filtered evm (emperical rms error)
        if ( ((num_symbols_rx+1)%100) == 0 )
            printf("%4u : mse = %12.8f dB\n",
                    num_symbols_rx+1,
                    20*log10f(mse[num_symbols_rx]));
        
        // increment output symbol counter
        num_symbols_rx++;
    }

    // get equalizer weights
    eqlms_cccf_get_weights(eq, gr);

    // destroy objects
    eqlms_cccf_destroy(eq);
    interp_cccf_destroy(interp);
    firfilt_cccf_destroy(fchannel);
    modem_destroy(mod);
    modem_destroy(demod);

    // 
    // export output
    //
    FILE * fid = NULL;
    char filename[300];

    // 
    // const: constellation
    //
    strncpy(filename, filename_base, 256);
    strcat(filename, "_const.gnu");
    fid = fopen(filename,"w");
    if (!fid) {
        fprintf(stderr,"error: %s, could not open file '%s' for writing\n", argv[0], filename);
        return 1;
    }
    fprintf(fid,"# %s: auto-generated file\n\n", filename);
    fprintf(fid,"reset\n");
    fprintf(fid,"set terminal postscript eps enhanced color solid rounded\n");
    fprintf(fid,"set size ratio 1\n");
    fprintf(fid,"set xrange [-1.5:1.5];\n");
    fprintf(fid,"set yrange [-1.5:1.5];\n");
    fprintf(fid,"set xlabel 'In-phase'\n");
    fprintf(fid,"set ylabel 'Quadrature phase'\n");
    fprintf(fid,"set grid xtics ytics\n");
    fprintf(fid,"set grid linetype 1 linecolor rgb '%s' linewidth 1\n",LIQUID_DOC_COLOR_GRID);
    fprintf(fid,"plot '-' using 1:2 with points pointtype 7 pointsize 0.5 linecolor rgb '%s' title 'first 50%%',\\\n", LIQUID_DOC_COLOR_GRAY);
    fprintf(fid,"     '-' using 1:2 with points pointtype 7 pointsize 0.7 linecolor rgb '%s' title 'last 50%%'\n",     LIQUID_DOC_COLOR_RED);
    // first half of symbols
    for (i=2*p; i<num_symbols/2; i+=k)
        fprintf(fid,"  %12.4e %12.4e\n", crealf(y[i]), cimagf(y[i]));
    fprintf(fid,"e\n");

    // second half of symbols
    for ( ; i<num_symbols; i+=k)
        fprintf(fid,"  %12.4e %12.4e\n", crealf(z[i]), cimagf(z[i]));
    fprintf(fid,"e\n");

    fclose(fid);
    printf("results written to '%s'\n", filename);

    // 
    // mse : mean-squared error
    //
    strncpy(filename, filename_base, 256);
    strcat(filename, "_mse.gnu");
    fid = fopen(filename,"w");
    if (!fid) {
        fprintf(stderr,"error: %s, could not open file '%s' for writing\n", argv[0], filename);
        return 1;
    }
    fprintf(fid,"# %s: auto-generated file\n\n", filename);
    fprintf(fid,"reset\n");
    fprintf(fid,"set terminal postscript eps enhanced color solid rounded\n");
    fprintf(fid,"set size ratio 0.3\n");
    fprintf(fid,"set xrange [0:%u];\n", num_symbols);
    fprintf(fid,"set yrange [1e-3:1e-1];\n");
    fprintf(fid,"set format y '10^{%%L}'\n");
    fprintf(fid,"set log y\n");
    fprintf(fid,"set xlabel 'symbol index'\n");
    fprintf(fid,"set ylabel 'mean-squared error'\n");
    fprintf(fid,"set grid xtics ytics\n");
    fprintf(fid,"set grid linetype 1 linecolor rgb '%s' linewidth 1\n",LIQUID_DOC_COLOR_GRID);
    fprintf(fid,"plot '-' using 1:2 with lines linewidth 4 linetype 1 linecolor rgb '%s' title 'LMS MSE'\n", LIQUID_DOC_COLOR_RED);
    // LMS
    for (i=0; i<num_symbols_rx; i++)
        fprintf(fid,"  %4u %16.8e\n", i, mse[i]);
    fprintf(fid,"e\n");

    fclose(fid);
    printf("results written to '%s'\n", filename);


    // 
    // psd : power spectral density
    //

    // scale transmit filter appropriately
    for (i=0; i<gt_len; i++) gt[i] /= (float)k;

    float complex Gt[nfft];     // transmit matched filter
    float complex Hc[nfft];     // channel response
    float complex Gr[nfft];     // equalizer response
    liquid_doc_compute_psdcf(gt, gt_len, Gt, nfft, LIQUID_DOC_PSDWINDOW_NONE, 0);
    liquid_doc_compute_psdcf(hc, hc_len, Hc, nfft, LIQUID_DOC_PSDWINDOW_NONE, 0);
    liquid_doc_compute_psdcf(gr, gr_len, Gr, nfft, LIQUID_DOC_PSDWINDOW_NONE, 0);
    fft_shift(Gt, nfft);
    fft_shift(Hc, nfft);
    fft_shift(Gr, nfft);
    float freq[nfft];
    for (i=0; i<nfft; i++)
        freq[i] = (float)(i) / (float)nfft - 0.5f;

    strncpy(filename, filename_base, 256);
    strcat(filename, "_freq.gnu");
    fid = fopen(filename,"w");
    if (!fid) {
        fprintf(stderr,"error: %s, could not open file '%s' for writing\n", argv[0], filename);
        return 1;
    }
    fprintf(fid,"# %s: auto-generated file\n\n", filename);
    fprintf(fid,"reset\n");
    fprintf(fid,"set terminal postscript eps enhanced color solid rounded\n");
    fprintf(fid,"set size ratio 0.6\n");
    fprintf(fid,"set xrange [-0.5:0.5];\n");
    fprintf(fid,"set yrange [-10:6]\n");
    fprintf(fid,"set xlabel 'Normalized Frequency'\n");
    fprintf(fid,"set ylabel 'Power Spectral Density [dB]'\n");
    fprintf(fid,"set key top right nobox\n");
    fprintf(fid,"set grid xtics ytics\n");
    fprintf(fid,"set grid linetype 1 linecolor rgb '%s' lw 1\n",LIQUID_DOC_COLOR_GRID);
    fprintf(fid,"plot '-' using 1:2 with lines linetype 1 linewidth 1.5 linecolor rgb '%s' title 'transmit',\\\n",  LIQUID_DOC_COLOR_GRAY);
    fprintf(fid,"     '-' using 1:2 with lines linetype 1 linewidth 1.5 linecolor rgb '%s' title 'channel',\\\n",   LIQUID_DOC_COLOR_RED);
    fprintf(fid,"     '-' using 1:2 with lines linetype 1 linewidth 1.5 linecolor rgb '%s' title 'equalizer',\\\n", LIQUID_DOC_COLOR_GREEN);
    fprintf(fid,"     '-' using 1:2 with lines linetype 1 linewidth 4.0 linecolor rgb '%s' title 'composite',\\\n", LIQUID_DOC_COLOR_BLUE);
    fprintf(fid,"     '-' using 1:2 with points pointtype 7 pointsize 0.6 linecolor rgb '%s' notitle\n", LIQUID_DOC_COLOR_BLUE);
    // received signal
    for (i=0; i<nfft; i++)
        fprintf(fid,"%12.8f %12.4e\n", freq[i], 20*log10f(cabsf(Gt[i])) );
    fprintf(fid,"e\n");

    // channel
    for (i=0; i<nfft; i++)
        fprintf(fid,"%12.8f %12.4e\n", freq[i], 20*log10f(cabsf(Hc[i])) );
    fprintf(fid,"e\n");

    // equalizer
    for (i=0; i<nfft; i++)
        fprintf(fid,"%12.8f %12.4e\n", freq[i], 20*log10f(cabsf(Gr[i])) );
    fprintf(fid,"e\n");

    // composite
    for (i=0; i<nfft; i++)
        fprintf(fid,"%12.8f %12.4e\n", freq[i], 20*log10f( cabsf(Gt[i])*cabsf(Hc[i])*cabsf(Gr[i])) );
    fprintf(fid,"e\n");

    // composite
    fprintf(fid,"%12.8f %12.4e\n", -0.5f/(float)k, 20*log10f(0.5f));
    fprintf(fid,"%12.8f %12.4e\n",  0.5f/(float)k, 20*log10f(0.5f));
    fprintf(fid,"e\n");

    fclose(fid);
    printf("results written to '%s'\n", filename);

    //
    // time...
    //
    strncpy(filename, filename_base, 256);
    strcat(filename, "_time.gnu");
    fid = fopen(filename,"w");
    if (!fid) {
        fprintf(stderr,"error: %s, could not open file '%s' for writing\n", argv[0], filename);
        return 1;
    }
    fprintf(fid,"# %s: auto-generated file\n\n", filename);
    fprintf(fid,"reset\n");
    fprintf(fid,"set terminal postscript eps enhanced color solid rounded\n");
    fprintf(fid,"set xrange [0:%u];\n",num_symbols);
    fprintf(fid,"set yrange [-1.5:1.5]\n");
    fprintf(fid,"set size ratio 0.3\n");
    fprintf(fid,"set xlabel 'Symbol Index'\n");
    fprintf(fid,"set key top right nobox\n");
    //fprintf(fid,"set ytics -5,1,5\n");
    fprintf(fid,"set grid xtics ytics\n");
    fprintf(fid,"set pointsize 0.6\n");
    fprintf(fid,"set grid linetype 1 linecolor rgb '%s' lw 1\n", LIQUID_DOC_COLOR_GRID);
    fprintf(fid,"set multiplot layout 2,1 scale 1.0,1.0\n");

    // real
    fprintf(fid,"# real\n");
    fprintf(fid,"set ylabel 'Real'\n");
    fprintf(fid,"plot '-' using 1:2 with lines linetype 1 linewidth 1 linecolor rgb '#999999' notitle,\\\n");
    fprintf(fid,"     '-' using 1:2 with points pointtype 7 linecolor rgb '%s' notitle'\n", LIQUID_DOC_COLOR_BLUE);
    // 
    for (i=0; i<num_samples; i++)
        fprintf(fid,"%12.8f %12.4e\n", (float)i/(float)k, crealf(z[i]));
    fprintf(fid,"e\n");
    // 
    for (i=0; i<num_samples; i+=k)
        fprintf(fid,"%12.8f %12.4e\n", (float)i/(float)k, crealf(z[i]));
    fprintf(fid,"e\n");

    // imag
    fprintf(fid,"# imag\n");
    fprintf(fid,"set ylabel 'Imag'\n");
    fprintf(fid,"plot '-' using 1:2 with lines linetype 1 linewidth 1 linecolor rgb '#999999' notitle,\\\n");
    fprintf(fid,"     '-' using 1:2 with points pointtype 7 linecolor rgb '%s' notitle'\n", LIQUID_DOC_COLOR_GREEN);
    // 
    for (i=0; i<num_samples; i++)
        fprintf(fid,"%12.8f %12.4e\n", (float)i/(float)k, cimagf(z[i]));
    fprintf(fid,"e\n");
    // 
    for (i=0; i<num_samples; i+=k)
        fprintf(fid,"%12.8f %12.4e\n", (float)i/(float)k, cimagf(z[i]));
    fprintf(fid,"e\n");

    fprintf(fid,"unset multiplot\n");

    // close output file
    fclose(fid);
    printf("results written to '%s'\n", filename);

    return 0;
}