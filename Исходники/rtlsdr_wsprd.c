int main(int argc, char** argv) {
    uint32_t opt;

    int32_t  rtl_result;
    int32_t  rtl_count;
    char     rtl_vendor[256], rtl_product[256], rtl_serial[256];

    initrx_options();
    initDecoder_options();

    /* RX buffer allocation */
    rx_state.iSamples=malloc(sizeof(float)*SIGNAL_LENGHT*SIGNAL_SAMPLE_RATE);
    rx_state.qSamples=malloc(sizeof(float)*SIGNAL_LENGHT*SIGNAL_SAMPLE_RATE);

    /* Stop condition setup */
    rx_state.exit_flag   = false;
    rx_state.decode_flag = false;
    uint32_t nLoop = 0;


    if (argc <= 1)
        usage();

    while ((opt = getopt(argc, argv, "f:c:l:g:a:o:p:u:d:n:i:H:Q:S")) != -1) {
        switch (opt) {
        case 'f': // Frequency
            rx_options.dialfreq = (uint32_t)atofs(optarg);
            break;
        case 'c': // Callsign
            sprintf(dec_options.rcall, "%.12s", optarg);
            break;
        case 'l': // Locator / Grid
            sprintf(dec_options.rloc, "%.6s", optarg);
            break;
        case 'g': // Small signal amplifier gain
            rx_options.gain = atoi(optarg);
            if (rx_options.gain < 0) rx_options.gain = 0;
            if (rx_options.gain > 49) rx_options.gain = 49;
            rx_options.gain *= 10;
            break;
        case 'a': // Auto gain
            rx_options.autogain = atoi(optarg);
            if (rx_options.autogain < 0) rx_options.autogain = 0;
            if (rx_options.autogain > 1) rx_options.autogain = 1;
            break;
        case 'o': // Fine frequency correction
            rx_options.shift = atoi(optarg);
            break;
        case 'p':
            rx_options.ppm = atoi(optarg);
            break;
        case 'u': // Upconverter frequency
            rx_options.upconverter = (uint32_t)atofs(optarg);
            break;
        case 'd': // Direct Sampling
            rx_options.directsampling = (uint32_t)atofs(optarg);
            break;
        case 'n': // Stop after n iterations
            rx_options.maxloop = (uint32_t)atofs(optarg);
            break;
        case 'i': // Select the device to use
            rx_options.device = (uint32_t)atofs(optarg);
            break;
        case 'H': // Decoder option, use a hastable
            dec_options.usehashtable = 1;
            break;
        case 'Q': // Decoder option, faster
            dec_options.quickmode = 1;
            break;
        case 'S': // Decoder option, single pass mode (same as original wsprd)
            dec_options.subtraction = 0;
            dec_options.npasses = 1;
            break;
        default:
            usage();
            break;
        }
    }

    if (rx_options.dialfreq == 0) {
        fprintf(stderr, "Please specify a dial frequency.\n");
        fprintf(stderr, " --help for usage...\n");
        exit(1);
    }

    if (dec_options.rcall[0] == 0) {
        fprintf(stderr, "Please specify your callsign.\n");
        fprintf(stderr, " --help for usage...\n");
        exit(1);
    }

    if (dec_options.rloc[0] == 0) {
        fprintf(stderr, "Please specify your locator.\n");
        fprintf(stderr, " --help for usage...\n");
        exit(1);
    }

    /* Calcule shift offset */
    rx_options.realfreq = rx_options.dialfreq + rx_options.shift + rx_options.upconverter;

    /* Store the frequency used for the decoder */
    dec_options.freq = rx_options.dialfreq;

    /* If something goes wrong... */
    signal(SIGINT, &sigint_callback_handler);
    signal(SIGTERM, &sigint_callback_handler);
    signal(SIGILL, &sigint_callback_handler);
    signal(SIGFPE, &sigint_callback_handler);
    signal(SIGSEGV, &sigint_callback_handler);
    signal(SIGABRT, &sigint_callback_handler);

    /* Init & parameter the device */
    rtl_count = rtlsdr_get_device_count();
    if (!rtl_count) {
        fprintf(stderr, "No supported devices found\n");
        return EXIT_FAILURE;
    }


    fprintf(stderr, "Found %d device(s):\n", rtl_count);
    for (uint32_t i=0; i<rtl_count; i++) {
        rtlsdr_get_device_usb_strings(i, rtl_vendor, rtl_product, rtl_serial);
        fprintf(stderr, "  %d:  %s, %s, SN: %s\n", i, rtl_vendor, rtl_product, rtl_serial);
    }
    fprintf(stderr, "\nUsing device %d: %s\n", rx_options.device, rtlsdr_get_device_name(rx_options.device));


    rtl_result = rtlsdr_open(&rtl_device, rx_options.device);
    if (rtl_result < 0) {
        fprintf(stderr, "ERROR: Failed to open rtlsdr device #%d.\n", rx_options.device);
        return EXIT_FAILURE;
    }

    if (rx_options.directsampling) {
        rtl_result = rtlsdr_set_direct_sampling(rtl_device, rx_options.directsampling);
        if (rtl_result < 0) {
            fprintf(stderr, "ERROR: Failed to set direct sampling\n");
            rtlsdr_close(rtl_device);
            return EXIT_FAILURE;
        }
    }

    rtl_result = rtlsdr_set_sample_rate(rtl_device, SAMPLING_RATE);
    if (rtl_result < 0) {
        fprintf(stderr, "ERROR: Failed to set sample rate\n");
        rtlsdr_close(rtl_device);
        return EXIT_FAILURE;
    }


    rtl_result = rtlsdr_set_tuner_gain_mode(rtl_device, 1);
    if (rtl_result < 0) {
        fprintf(stderr, "ERROR: Failed to enable manual gain\n");
        rtlsdr_close(rtl_device);
        return EXIT_FAILURE;
    }


    if (rx_options.autogain) {
        rtl_result = rtlsdr_set_tuner_gain_mode(rtl_device, 0);
        if (rtl_result != 0) {
            fprintf(stderr, "ERROR: Failed to set tuner gain\n");
            rtlsdr_close(rtl_device);
            return EXIT_FAILURE;
        }
    } else {
        rtl_result = rtlsdr_set_tuner_gain(rtl_device, rx_options.gain);
        if (rtl_result != 0) {
            fprintf(stderr, "ERROR: Failed to set tuner gain\n");
            rtlsdr_close(rtl_device);
            return EXIT_FAILURE;
        }
    }


    if (rx_options.ppm != 0) {
        rtl_result = rtlsdr_set_freq_correction(rtl_device, rx_options.ppm);
        if (rtl_result < 0) {
            fprintf(stderr, "ERROR: Failed to set ppm error\n");
            rtlsdr_close(rtl_device);
            return EXIT_FAILURE;
        }
    }


    rtl_result = rtlsdr_set_center_freq(rtl_device, rx_options.realfreq + FS4_RATE + 1500);
    if (rtl_result < 0) {
        fprintf(stderr, "ERROR: Failed to set frequency\n");
        rtlsdr_close(rtl_device);
        return EXIT_FAILURE;
    }


    rtl_result = rtlsdr_reset_buffer(rtl_device);
    if (rtl_result < 0) {
        fprintf(stderr, "ERROR: Failed to reset buffers.\n");
        rtlsdr_close(rtl_device);
        return EXIT_FAILURE;
    }

    /* Print used parameter */
    time_t rawtime;
    time ( &rawtime );
    struct tm *gtm = gmtime(&rawtime);
    printf("\nStarting rtlsdr-wsprd (%04d-%02d-%02d, %02d:%02dz) -- Version 0.2\n",
           gtm->tm_year + 1900, gtm->tm_mon + 1, gtm->tm_mday, gtm->tm_hour, gtm->tm_min);
    printf("  Callsign     : %s\n", dec_options.rcall);
    printf("  Locator      : %s\n", dec_options.rloc);
    printf("  Dial freq.   : %d Hz\n", rx_options.dialfreq);
    printf("  Real freq.   : %d Hz\n", rx_options.realfreq);
    printf("  PPM factor   : %d\n", rx_options.ppm);
    if(rx_options.autogain)
        printf("  Auto gain    : enable\n");
    else
        printf("  Gain         : %d dB\n", rx_options.gain/10);


    /* Time alignment stuff */
    struct timeval lTime;
    gettimeofday(&lTime, NULL);
    uint32_t sec   = lTime.tv_sec % 120;
    uint32_t usec  = sec * 1000000 + lTime.tv_usec;
    uint32_t uwait = 120000000 - usec;
    printf("Wait for time sync (start in %d sec)\n\n", uwait/1000000);

    /* Prepare a low priority param for the decoder thread */
    struct sched_param param;
    pthread_attr_init(&dec.tattr);
    pthread_attr_setschedpolicy(&dec.tattr, SCHED_RR);
    pthread_attr_getschedparam(&dec.tattr, &param);
    param.sched_priority = 90;  // = sched_get_priority_min();
    pthread_attr_setschedparam(&dec.tattr, &param);

    /* Create a thread and stuff for separate decoding
       Info : https://computing.llnl.gov/tutorials/pthreads/
    */
    pthread_rwlock_init(&dec.rw, NULL);
    pthread_cond_init(&dec.ready_cond, NULL);
    pthread_mutex_init(&dec.ready_mutex, NULL);
    pthread_create(&dongle.thread, NULL, rtlsdr_rx, NULL);
    pthread_create(&dec.thread, &dec.tattr, wsprDecoder, NULL);


    /* Main loop : Wait, read, decode */
    while (!rx_state.exit_flag && !(rx_options.maxloop && (nLoop >= rx_options.maxloop))) {
        /* Wait for time Sync on 2 mins */
        gettimeofday(&lTime, NULL);
        sec   = lTime.tv_sec % 120;
        usec  = sec * 1000000 + lTime.tv_usec;
        uwait = 120000000 - usec + 10000;  // Adding 10ms, to be sure to reach this next minute
        usleep(uwait);
        //printf("SYNC! RX started\n");

        /* Use the Store the date at the begin of the frame */
        time ( &rawtime );
        gtm = gmtime(&rawtime);
        sprintf(rx_options.date,"%02d%02d%02d", gtm->tm_year - 100, gtm->tm_mon + 1, gtm->tm_mday);
        sprintf(rx_options.uttime,"%02d%02d", gtm->tm_hour, gtm->tm_min);

        /* Start to store the samples */
        initSampleStorage();

        while( (rx_state.exit_flag == false) &&
                (rx_state.iqIndex < (SIGNAL_LENGHT * SIGNAL_SAMPLE_RATE) ) ) {
            usleep(250000);
        }
        nLoop++;
    }

    /* Stop the RX and free the blocking function */
    rtlsdr_cancel_async(rtl_device);

    /* Close the RTL device */
    rtlsdr_close(rtl_device);

    printf("Bye!\n");

    /* Wait the thread join (send a signal before to terminate the job) */
    pthread_mutex_lock(&dec.ready_mutex);
    pthread_cond_signal(&dec.ready_cond);
    pthread_mutex_unlock(&dec.ready_mutex);
    pthread_join(dec.thread, NULL);
    pthread_join(dongle.thread, NULL);

    /* Destroy the lock/cond/thread */
    pthread_rwlock_destroy(&dec.rw);
    pthread_cond_destroy(&dec.ready_cond);
    pthread_mutex_destroy(&dec.ready_mutex);
    pthread_exit(NULL);

    return EXIT_SUCCESS;
}