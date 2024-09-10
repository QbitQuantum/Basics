void 
audio_waveout::play(void)
{
    MMRESULT err;
    unsigned int i;

    if (!main_buffer)
    {
        /* TODO; throw error, or assert */
        return;
    }

    /* If the status is PAUSED, we have to resume the audio playing */
    if (status == WAVEOUT_PAUSED)
    {
        /* Updates status */
        status = WAVEOUT_PLAYING;
        /* Tells to the driver to resume audio playing */
        waveOutRestart(waveout_handle);
        /* Wakeup playing thread */
        SetEvent(wakeup_playthread);
        return;
    } /* if status == WAVEOUT_PAUSED */

    if (status != WAVEOUT_READY)
        return;

    /* Prepares WAVEHDR structures */
    prep_headers_();
    /* Sets correct status */
    status = WAVEOUT_PLAYING;
    /* Reads the audio from the start */
    //audio_buf.set_position_start();

    /* Reads the first N bytes from the audio buffer, where N = the total
       size of all little buffers */
    audio_buf.read(main_buffer, mb_size);

    /* Wakeup the playing thread */
    SetEvent(wakeup_playthread);

    /* Sends all the little buffers to the audio driver, so it can play
       the sound data */
    for (i = 0; i < buffers; ++i)
    {
        err = waveOutWrite(waveout_handle, &wave_headers[i], sizeof(WAVEHDR));
        if (err != MMSYSERR_NOERROR)
        {
            MessageBox(0, _T("waveOutWrite Error"), 0, 0);
            /* TODO: throw error */
        }
    }
}