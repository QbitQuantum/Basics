    JackNetAdapter::JackNetAdapter(jack_client_t* jack_client, jack_nframes_t buffer_size, jack_nframes_t sample_rate, const JSList* params)
            : JackAudioAdapterInterface(buffer_size, sample_rate), JackNetSlaveInterface(), fThread(this)
    {
        jack_log("JackNetAdapter::JackNetAdapter");

        /*
        Global parameter setting : we can't call JackNetSlaveInterface constructor with some parameters before,
        because we don't have full parametering right now, parameters will be parsed from the param list,
        and then JackNetSlaveInterface will be filled with proper values.
        */
        char multicast_ip[32];
        uint udp_port;
        GetHostName(fParams.fName, JACK_CLIENT_NAME_SIZE);
        fSocket.GetName(fParams.fSlaveNetName);
        fParams.fMtu = DEFAULT_MTU;
        // Desactivated for now...
        fParams.fTransportSync = 0;
        int send_audio = -1;
        int return_audio = -1;
        fParams.fSendMidiChannels = 0;
        fParams.fReturnMidiChannels = 0;
        fParams.fSampleRate = sample_rate;
        fParams.fPeriodSize = buffer_size;
        fParams.fSlaveSyncMode = 1;
        fParams.fNetworkLatency = 2;
        fParams.fSampleEncoder = JackFloatEncoder;
        fClient = jack_client;
    
        // Possibly use env variable
        const char* default_udp_port = getenv("JACK_NETJACK_PORT");
        udp_port = (default_udp_port) ? atoi(default_udp_port) : DEFAULT_PORT;

        const char* default_multicast_ip = getenv("JACK_NETJACK_MULTICAST");
        if (default_multicast_ip) {
            strcpy(multicast_ip, default_multicast_ip);
        } else {
            strcpy(multicast_ip, DEFAULT_MULTICAST_IP);
        }

        //options parsing
        const JSList* node;
        const jack_driver_param_t* param;
        for (node = params; node; node = jack_slist_next(node))
        {
            param = (const jack_driver_param_t*) node->data;

            switch (param->character) {
                case 'a' :
                    assert(strlen(param->value.str) < 32);
                    strcpy(multicast_ip, param->value.str);
                    break;
                case 'p' :
                    udp_port = param->value.ui;
                    break;
                case 'M' :
                    fParams.fMtu = param->value.i;
                    break;
                case 'C' :
                    send_audio = param->value.i;
                    break;
                case 'P' :
                    return_audio = param->value.i;
                    break;
                case 'n' :
                    strncpy(fParams.fName, param->value.str, JACK_CLIENT_NAME_SIZE);
                    break;
                case 't' :
                    fParams.fTransportSync = param->value.ui;
                    break;
            #if HAVE_CELT
                case 'c':
                    if (param->value.i > 0) {
                        fParams.fSampleEncoder = JackCeltEncoder;
                        fParams.fKBps = param->value.i;
                    }
                    break;
            #endif
            #if HAVE_OPUS
                case 'O':
                    if (param->value.i > 0) {
                        fParams.fSampleEncoder = JackOpusEncoder;
                        fParams.fKBps = param->value.i;
                    }
                    break;
            #endif
                case 'l' :
                    fParams.fNetworkLatency = param->value.i;
                    if (fParams.fNetworkLatency > NETWORK_MAX_LATENCY) {
                        jack_error("Error : network latency is limited to %d\n", NETWORK_MAX_LATENCY);
                        throw std::bad_alloc();
                    }
                    break;
                case 'q':
                    fQuality = param->value.ui;
                    break;
                case 'g':
                    fRingbufferCurSize = param->value.ui;
                    fAdaptative = false;
                    break;
             }
        }

        strcpy(fMulticastIP, multicast_ip);

        // Set the socket parameters
        fSocket.SetPort(udp_port);
        fSocket.SetAddress(fMulticastIP, udp_port);

        // If not set, takes default
        fParams.fSendAudioChannels = (send_audio == -1) ? 2 : send_audio;

        // If not set, takes default
        fParams.fReturnAudioChannels = (return_audio == -1) ? 2 : return_audio;

        // Set the audio adapter interface channel values
        SetInputs(fParams.fSendAudioChannels);
        SetOutputs(fParams.fReturnAudioChannels);

        // Soft buffers will be allocated later (once network initialization done)
        fSoftCaptureBuffer = NULL;
        fSoftPlaybackBuffer = NULL;
    }