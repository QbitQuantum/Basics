// this is run by a java thread; the context needs to be the JNI environment
// pointer valid for the thread.
static void PV_AudioWaveInFrameThread(void* threadContext)
{
    WAVEHDR         waveHeader[BAE_WAVEIN_NUM_BUFFERS];
    MMTIME          audioStatus;

    long            count, currentPos, lastPos, framesToRead, bytesToRead, buffersToRead, error;

    long            waveHeaderCount;    // current index in the array of waveheaders
    LPWAVEHDR       pCurrentWaveHdr;

    bytesToRead = g_audioBytesPerBuffer; 
    framesToRead = g_audioFramesPerBuffer;  

    memset(&waveHeader, 0, sizeof(WAVEHDR) * BAE_WAVEIN_NUM_BUFFERS);
    memset(&audioStatus, 0, (long)sizeof(MMTIME));
    audioStatus.wType = TIME_BYTES; // get byte position
    
    error = waveInGetPosition(g_captureSound, &audioStatus, sizeof(MMTIME));
    currentPos = audioStatus.u.cb;
    lastPos = currentPos + g_audioBytesPerBuffer;

    // set up all the capture buffers
    for (count = 0; count < BAE_WAVEIN_NUM_BUFFERS; count++)
    {
        waveHeader[count].lpData = (char *)g_audioBufferBlock[count];
        waveHeader[count].dwBufferLength = g_audioBytesPerBuffer;
        waveHeader[count].dwFlags       = 0;
        waveHeader[count].dwLoops       = 0;
        error = waveInPrepareHeader(g_captureSound, &waveHeader[count], (long)sizeof(WAVEHDR));
    }

    // add all the capture buffers
    for (count = 0; count < BAE_WAVEIN_NUM_BUFFERS; count++)
    {
        error = waveInAddBuffer(g_captureSound, &waveHeader[count], sizeof(WAVEHDR));
    }


    // now run this loop to do the capture.  
    // we wait for enough samples to be captured to fill one capture buffer,
    // callback with the captured data, and put the buffer back in the queue.

    waveHeaderCount = 0; // which buffer we're processing
    while (g_captureShutdown == FALSE)
    {   
        // wait for the device to record enough data to fill our capture buffer

        while (currentPos < lastPos)
        {
            if (g_captureShutdown == TRUE)
            {
                break;
            }

            BAE_SleepFrameThread(threadContext, BAE_WAVEIN_SOUND_PERIOD);       // in ms
                
            error = waveInGetPosition(g_captureSound, &audioStatus, sizeof(MMTIME));
            currentPos = audioStatus.u.cb;
        }

        lastPos += bytesToRead;


        if (g_captureShutdown == FALSE)
        {
            // then process the captured data

            // this is the data buffer for the current capture buffer
            pCurrentWaveHdr = &waveHeader[waveHeaderCount];

            if (pCurrentWaveHdr->dwFlags & WHDR_DONE)
            {
                DWORD dwBytesRecorded = pCurrentWaveHdr->dwBytesRecorded;
                LPSTR lpData = pCurrentWaveHdr->lpData;

                // callback with the captured data
                (*g_captureDoneProc)(threadContext, DATA_READY_CAPTURE, &lpData, (void *)&dwBytesRecorded);

                // add the buffer back into the queue
                error = waveInAddBuffer(g_captureSound, pCurrentWaveHdr, sizeof(WAVEHDR));

                // increment to the next wavehdr
                waveHeaderCount++;
                if (waveHeaderCount == BAE_WAVEIN_NUM_BUFFERS)
                {
                    waveHeaderCount = 0;
                }
            }
        }
    } // while

    waveInReset(g_captureSound);        // stop all audio before unpreparing headers

    // unprepare headers
    for (count = 0; count < BAE_WAVEIN_NUM_BUFFERS; count++)
    {
        error = waveInUnprepareHeader(g_captureSound, &waveHeader[count], (long)sizeof(WAVEHDR));
    }
    // do this here, when we can't call it anymore.
    g_captureDoneProc = NULL;
}