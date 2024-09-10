HnAudio *hn_win32_audio_open(HnAudioFormat *pFormat)
{
    HnAudio_Win32 *pImpl = 
        (HnAudio_Win32 *)calloc(1, sizeof(HnAudio_Win32));
    MMRESULT result = MMSYSERR_NOERROR;
    
    WAVEFORMATEX wfex;
    build_wfex(&wfex, 
               pFormat->samplesPerSecond, 
               pFormat->sampleResolution, 
               pFormat->numberOfChannels);

    result = check_signedness(pFormat);
    if (MMSYSERR_NOERROR != result) goto Done;

    result = waveOutOpen(&(pImpl->hwo), 0, &wfex, (DWORD_PTR)wave_out_proc, 
        (DWORD_PTR)pImpl, CALLBACK_FUNCTION);
    if (MMSYSERR_NOERROR != result) goto Done;

    pImpl->pVtbl = &_HnAudio_Win32_vtbl;
Done:
    if (MMSYSERR_NOERROR != result)
    {
        waveOutClose(pImpl->hwo);
        free(pImpl);
        pImpl = NULL;
    }

    return (HnAudio *)pImpl;
}