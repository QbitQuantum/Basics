short *Audio_MMSystem::open (AudioConfig &cfg, const char *)
{
    WAVEFORMATEX  wfm;

    if (isOpen)
    {
        _errorString = "MMSYSTEM ERROR: Audio device already open.";
        return NULL;
    }
    isOpen = true;

    /* Initialise blocks */
    memset (blockHandles, 0, sizeof (blockHandles));
    memset (blockHeaders, 0, sizeof (blockHeaders));
    memset (blockHeaderHandles, 0, sizeof (blockHeaderHandles));

    // Format
    memset (&wfm, 0, sizeof(WAVEFORMATEX));
    wfm.wFormatTag      = WAVE_FORMAT_PCM;
    wfm.nChannels       = cfg.channels;
    wfm.nSamplesPerSec  = cfg.frequency;
    wfm.wBitsPerSample  = 16;
    wfm.nBlockAlign     = wfm.wBitsPerSample / 8 * wfm.nChannels;
    wfm.nAvgBytesPerSec = wfm.nSamplesPerSec * wfm.nBlockAlign;
    wfm.cbSize          = 0;

    // Rev 1.3 (saw) - Calculate buffer to hold 250ms of data
    bufSize = wfm.nSamplesPerSec / 4 * wfm.nBlockAlign;

    cfg.bufSize = bufSize / 2;
    waveOutOpen (&waveHandle, WAVE_MAPPER, &wfm, 0, 0, 0);
    if ( !waveHandle ) {
        _errorString = "MMSYSTEM ERROR: Can't open wave out device.";
        goto Audio_MMSystem_openError;
    }

    _settings    = cfg;

    {
        /* Allocate and lock memory for all mixing blocks: */
        int i;
        for (i = 0; i < MAXBUFBLOCKS; i++ )
        {
            /* Allocate global memory for mixing block: */
            if ( (blockHandles[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,
                                                bufSize)) == NULL )
            {
                _errorString = "MMSYSTEM ERROR: Can't allocate global memory.";
                goto Audio_MMSystem_openError;
            }

            /* Lock mixing block memory: */
            if ( (blocks[i] = (short *)GlobalLock(blockHandles[i])) == NULL )
            {
                _errorString = "MMSYSTEM ERROR: Can't lock global memory.";
                goto Audio_MMSystem_openError;
            }

            /* Allocate global memory for mixing block header: */
            if ( (blockHeaderHandles[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE,
                                                      sizeof(WAVEHDR))) == NULL )
            {
                _errorString = "MMSYSTEM ERROR: Can't allocate global memory.";
                goto Audio_MMSystem_openError;
            }

            /* Lock mixing block header memory: */
            WAVEHDR *header;
            if ( (header = blockHeaders[i] =
                  (WAVEHDR*)GlobalLock(blockHeaderHandles[i])) == NULL )
            {
                _errorString = "MMSYSTEM ERROR: Can't lock global memory.";
                goto Audio_MMSystem_openError;
            }

            /* Reset wave header fields: */
            memset (header, 0, sizeof (WAVEHDR));
            header->lpData         = (char*)blocks[i];
            header->dwBufferLength = bufSize;
            header->dwFlags        = WHDR_DONE; /* mark the block is done */
        }
    }

    blockNum = 0;
    _sampleBuffer = blocks[blockNum];
return _sampleBuffer;

Audio_MMSystem_openError:
    close ();
    return NULL;
}