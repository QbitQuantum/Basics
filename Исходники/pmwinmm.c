static PmError winmm_in_open(PmInternal *midi, void *driverInfo)
{
    DWORD dwDevice;
    int i = midi->device_id;
    int max_sysex_len = midi->buffer_len * 4;
    int num_input_buffers = max_sysex_len / INPUT_SYSEX_LEN;
    midiwinmm_type m;

    dwDevice = (DWORD) descriptors[i].descriptor;

    /* create system dependent device data */
    m = (midiwinmm_type) pm_alloc(sizeof(midiwinmm_node)); /* create */
    midi->descriptor = m;
    if (!m) goto no_memory;
    m->handle.in = NULL;
    m->buffers = NULL; /* not used for input */
    m->num_buffers = 0; /* not used for input */
    m->max_buffers = FALSE; /* not used for input */
    m->buffers_expanded = 0; /* not used for input */
    m->next_buffer = 0; /* not used for input */
    m->buffer_signal = 0; /* not used for input */
    m->last_time = 0;
    m->first_message = TRUE; /* not used for input */
    m->sysex_mode = FALSE;
    m->sysex_word = 0;
    m->sysex_byte_count = 0;
    m->hdr = NULL; /* not used for input */
    m->sync_time = 0;
    m->delta = 0;
    m->error = MMSYSERR_NOERROR;
    /* 4000 is based on Windows documentation -- that's the value used in the
       memory manager. It's small enough that it should not hurt performance even
       if it's not optimal.
     */
    InitializeCriticalSectionAndSpinCount(&m->lock, 4000);
    /* open device */
    pm_hosterror = midiInOpen(
	    &(m->handle.in),  /* input device handle */
	    dwDevice,  /* device ID */
	    (DWORD_PTR) winmm_in_callback,  /* callback address */
	    (DWORD_PTR) midi,  /* callback instance data */
	    CALLBACK_FUNCTION); /* callback is a procedure */
    if (pm_hosterror) goto free_descriptor;

    if (num_input_buffers < MIN_INPUT_BUFFERS)
        num_input_buffers = MIN_INPUT_BUFFERS;
    for (i = 0; i < num_input_buffers; i++) {
        if (allocate_input_buffer(m->handle.in, INPUT_SYSEX_LEN)) {
            /* either pm_hosterror was set, or the proper return code
               is pmInsufficientMemory */
            goto close_device;
        }
    }
    /* start device */
    pm_hosterror = midiInStart(m->handle.in);
    if (pm_hosterror) goto reset_device;
    return pmNoError;

    /* undo steps leading up to the detected error */
reset_device:
    /* ignore return code (we already have an error to report) */
    midiInReset(m->handle.in);
close_device:
    midiInClose(m->handle.in); /* ignore return code */
free_descriptor:
    midi->descriptor = NULL;
    pm_free(m);
no_memory:
    if (pm_hosterror) {
        int err = midiInGetErrorText(pm_hosterror, (char *) pm_hosterror_text,
                                     PM_HOST_ERROR_MSG_LEN);
        assert(err == MMSYSERR_NOERROR);
        return pmHostError;
    }
    /* if !pm_hosterror, then the error must be pmInsufficientMemory */
    return pmInsufficientMemory;
    /* note: if we return an error code, the device will be
       closed and memory will be freed. It's up to the caller
       to free the parameter midi */
}