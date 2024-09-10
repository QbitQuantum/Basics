int hairtunes_init(char *pAeskey, char *pAesiv, char *fmtpstr, int pCtrlPort, int pTimingPort,
         int pDataPort, char *pRtpHost, char*pPipeName, char *pLibaoDriver, char *pLibaoDeviceName, char *pLibaoDeviceId,
         int bufStartFill)
{
    if(pAeskey != NULL)    
        memcpy(aeskey, pAeskey, sizeof(aeskey));
    if(pAesiv != NULL)
        memcpy(aesiv, pAesiv, sizeof(aesiv));
    if(pRtpHost != NULL)
        rtphost = pRtpHost;
    if(pPipeName != NULL)
        pipename = pPipeName;
    if(pLibaoDriver != NULL)
        audio_set_driver(pLibaoDriver);
    if(pLibaoDeviceName != NULL)
        audio_set_device_name(pLibaoDeviceName);
    if(pLibaoDeviceId != NULL)
        audio_set_device_id(pLibaoDeviceId);
    
    controlport = pCtrlPort;
    timingport = pTimingPort;
    dataport = pDataPort;
    if(bufStartFill < 0)
        bufStartFill = START_FILL;
    buffer_start_fill = bufStartFill;

    AES_set_decrypt_key(aeskey, 128, &aes);

    memset(fmtp, 0, sizeof(fmtp));
    int i = 0;
    char *arg;
    while ( (arg = strsep(&fmtpstr, " \t")) )
        fmtp[i++] = atoi(arg);

    init_decoder();
    init_buffer();
    init_rtp();      // open a UDP listen port and start a listener; decode into ring buffer
    fflush(stdout);
    init_output();              // resample and output from ring buffer

    char line[128];
    int in_line = 0;
    int n;
    double f;
    while (fgets(line + in_line, sizeof(line) - in_line, stdin)) {
        n = strlen(line);
        if (line[n-1] != '\n') {
            in_line = strlen(line) - 1;
            if (n == sizeof(line)-1)
                in_line = 0;
            continue;
        }
        if (sscanf(line, "vol: %lf\n", &f)) {
#ifdef DEBUG
            assert(f<=0);
            fprintf(stderr, "VOL: %lf\n", f);
#endif
            pthread_mutex_lock(&vol_mutex);
            volume = pow(10.0,0.05*f);
            fix_volume = 65536.0 * volume;
            pthread_mutex_unlock(&vol_mutex);
            continue;
        }
        if (!strcmp(line, "exit\n")) {
            exit(0);
        }
        if (!strcmp(line, "flush\n")) {
            pthread_mutex_lock(&ab_mutex);
            ab_resync();
            pthread_mutex_unlock(&ab_mutex);
#ifdef DEBUG
                fprintf(stderr, "FLUSH\n");
#endif
        }
    }
    deinit_output();
    fprintf(stderr, "bye!\n");
    fflush(stderr);

    return EXIT_SUCCESS;
}