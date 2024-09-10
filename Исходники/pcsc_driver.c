static int pcsc_connect(cardreader_t *cr, unsigned prefered_protocol)
{
    DWORD attr_maxinput = 0;
    DWORD attr_maxinput_len = sizeof(unsigned int);
    SCARD_READERSTATE reader_state;
    pcsc_data_t* pcsc = cr->extra_data;
    int counter = 0;
    void *progress;

    memset(&reader_state,0,sizeof(reader_state));
    reader_state.szReader = cr->name+7;
    reader_state.dwCurrentState = SCARD_STATE_UNAWARE;
    pcsc->status = SCardGetStatusChange(pcsc->hcontext,INFINITE,&reader_state,1);

    if (pcsc->status != SCARD_S_SUCCESS)
    {
        log_printf(LOG_ERROR,"Failed to query reader status before connecting: %s (error 0x%08x).",
                pcsc_stringify_error(pcsc->status),
                pcsc->status );
        return 0;
    }

    progress = ui_inprogress_new("Connection","Waiting for the reader to connect to a card.");
    while ((reader_state.dwEventState & SCARD_STATE_PRESENT)==0)
    {
        reader_state.dwCurrentState = reader_state.dwEventState;
        if (((counter++)%30)==0)
        {
            log_printf(LOG_INFO,"Waiting for card to be present (current state: %s)...",
                    pcsc_stringify_state(reader_state.dwEventState));
        }

        if (!ui_inprogress_pulse(progress))
        {
            log_printf(LOG_ERROR,"Connection aborted by user");
            ui_inprogress_free(progress);
            pcsc->status = 0x6FFF;
            return 0;	    
        }

        pcsc->status = SCardGetStatusChange(pcsc->hcontext,100,&reader_state,1);
        if ((pcsc->status!=(LONG)SCARD_S_SUCCESS) && (pcsc->status!=(LONG)SCARD_E_TIMEOUT))
        {
            log_printf(LOG_ERROR,"Failed to query reader status change before connecting: %s (error 0x%08x/%08x).",
                    pcsc_stringify_error(pcsc->status),
                    pcsc->status,
                    SCARD_E_TIMEOUT );
            return 0;
        }
    }
    ui_inprogress_free(progress);

    log_printf(LOG_DEBUG,"Attempting to connect to '%s'",cr->name);
    pcsc->status = SCardConnect(pcsc->hcontext,
            cr->name+7,
            /* SCARD_SHARE_EXCLUSIVE, */
            SCARD_SHARE_SHARED,
            prefered_protocol,
            &(pcsc->hcard),
            &(cr->protocol));

    if (pcsc->status!=SCARD_S_SUCCESS)
    {
        log_printf(LOG_ERROR,"Connection failed: %s (error 0x%08x).",
                pcsc_stringify_error(pcsc->status),
                pcsc->status );
        return 0;
    }

    if (SCardGetAttrib(pcsc->hcard,SCARD_ATTR_MAXINPUT,(LPBYTE)&attr_maxinput,(LPDWORD)&attr_maxinput_len)==SCARD_S_SUCCESS)
        log_printf(LOG_INFO,"Reader maximum input length is %u bytes",attr_maxinput);
    else
        log_printf(LOG_DEBUG,"Could not determinate reader maximum input length");

    log_printf(LOG_INFO,"Connection successful, protocol is %s",pcsc_stringify_protocol(cr->protocol));
    cr->connected=1;

    return 1;
}