void AudioCaptureThread::ON_WIMDATA(WPARAM wParam, LPARAM lParam)
{
    if(IsWorking())
    {
#ifdef ENABLE_AUDIO_DENOISE
        Denoise((BYTE*)((PWAVEHDR)lParam)->lpData, ((PWAVEHDR)lParam)->dwBytesRecorded);
#endif//ENABLE_AUDIO_DENOISE

        static ULONG ulPkgNo = 0;

        MMRESULT mmResult = MMSYSERR_NOERROR;
        PWAVEHDR waveHdr = (PWAVEHDR) lParam;

#ifdef ENABLE_AUDIO_AEC
        VERIFY(::GetMicQueue());
        {
            double dCurTime = jrtplib::RTPTime::CurrentTime().GetDouble();
            RecPkgQueue::element_type bufAEC(new AudioBuffer((BYTE*)waveHdr->lpData, waveHdr->dwBytesRecorded, dCurTime));
            if (IsWorking())
            {
                ::GetMicQueue()->push_back(bufAEC);

#ifdef PRINT_AEC_INFO
                SPRINTF_S(dbg_str,
                    "Audio data: mic recv= %d"
                    "\ttime: %f"
                    , ulPkgNo
                    , dCurTime);
                DEBUG_INFO(dbg_str);
#endif//PRINT_AEC_INFO
            }
        }
#else //ENABLE_AUDIO_AEC

        RecPkgQueue::element_type buf2Send(new AudioBuffer((BYTE*)((PWAVEHDR)lParam)->lpData, ((PWAVEHDR)lParam)->dwBytesRecorded, 0));
        ((AudioSendSession*)m_pSession)->getPackageQueue()->push_back(buf2Send);
#endif//ENABLE_AUDIO_AEC
    
        //mmResult = ::waveInPrepareHeader (hWaveIn, waveHdr, sizeof(WAVEHDR));
        //checkMMError(mmResult, true);
        waveHdr->dwFlags = WHDR_PREPARED;

        mmResult = ::waveInAddBuffer (m_hWaveIn, waveHdr, sizeof(WAVEHDR));
        checkMMError(mmResult, true);

        ++ulPkgNo;
    }
}