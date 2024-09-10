void OBS::MainAudioLoop()
{
    const unsigned int audioSamplesPerSec = App->GetSampleRateHz();
    const unsigned int audioSampleSize = audioSamplesPerSec/100;

    DWORD taskID = 0;
    HANDLE hTask = AvSetMmThreadCharacteristics(TEXT("Pro Audio"), &taskID);

    bufferedAudioTimes.Clear();

    bPushToTalkOn = false;

    micMax = desktopMax = VOL_MIN;
    micPeak = desktopPeak = VOL_MIN;

    UINT audioFramesSinceMeterUpdate = 0;
    UINT audioFramesSinceMicMaxUpdate = 0;
    UINT audioFramesSinceDesktopMaxUpdate = 0;

    List<float> mixBuffer, levelsBuffer;
    mixBuffer.SetSize(audioSampleSize*2);
    levelsBuffer.SetSize(audioSampleSize*2);

    latestAudioTime = 0;

    //---------------------------------------------
    // the audio loop of doom

    while (true) {
        OSSleep(5); //screw it, just run it every 5ms

        if (!bRunning)
            break;

        //-----------------------------------------------

        float *desktopBuffer, *micBuffer;

        curDesktopVol = desktopVol * desktopBoost;

        if (bUsingPushToTalk)
            curMicVol = bPushToTalkOn ? micVol : 0.0f;
        else
            curMicVol = micVol;

        curMicVol *= micBoost;

        bool bDesktopMuted = (curDesktopVol < EPSILON);
        bool bMicEnabled   = (micAudio != NULL);

        while (QueryNewAudio()) {
            QWORD timestamp = bufferedAudioTimes[0];
            bufferedAudioTimes.Remove(0);

            zero(mixBuffer.Array(),    audioSampleSize*2*sizeof(float));
            zero(levelsBuffer.Array(), audioSampleSize*2*sizeof(float));

            //----------------------------------------------------------------------------
            // get latest sample for calculating the volume levels

            float *latestDesktopBuffer = NULL, *latestMicBuffer = NULL;

            desktopAudio->GetBuffer(&desktopBuffer, timestamp);
            desktopAudio->GetNewestFrame(&latestDesktopBuffer);

            if (micAudio != NULL) {
                micAudio->GetBuffer(&micBuffer, timestamp);
                micAudio->GetNewestFrame(&latestMicBuffer);
            }

            //----------------------------------------------------------------------------
            // mix desktop samples

            if (desktopBuffer)
                MixAudio(mixBuffer.Array(), desktopBuffer, audioSampleSize*2, false);

            if (latestDesktopBuffer)
                MixAudio(levelsBuffer.Array(), latestDesktopBuffer, audioSampleSize*2, false);

            //----------------------------------------------------------------------------
            // get latest aux volume level samples and mix

            OSEnterMutex(hAuxAudioMutex);

            for (UINT i=0; i<auxAudioSources.Num(); i++) {
                float *latestAuxBuffer;

                if(auxAudioSources[i]->GetNewestFrame(&latestAuxBuffer))
                    MixAudio(levelsBuffer.Array(), latestAuxBuffer, audioSampleSize*2, false);
            }

            //----------------------------------------------------------------------------
            // mix output aux sound samples with the desktop

            for (UINT i=0; i<auxAudioSources.Num(); i++) {
                float *auxBuffer;

                if(auxAudioSources[i]->GetBuffer(&auxBuffer, timestamp))
                    MixAudio(mixBuffer.Array(), auxBuffer, audioSampleSize*2, false);
            }

            OSLeaveMutex(hAuxAudioMutex);

            //----------------------------------------------------------------------------
            // multiply samples by volume and compute RMS and max of samples
            // Use 1.0f instead of curDesktopVol, since aux audio sources already have their volume set, and shouldn't be boosted anyway.

            float desktopRMS = 0, micRMS = 0, desktopMx = 0, micMx = 0;
            if (latestDesktopBuffer)
                CalculateVolumeLevels(levelsBuffer.Array(), audioSampleSize*2, 1.0f, desktopRMS, desktopMx);
            if (bMicEnabled && latestMicBuffer)
                CalculateVolumeLevels(latestMicBuffer, audioSampleSize*2, curMicVol, micRMS, micMx);

            //----------------------------------------------------------------------------
            // convert RMS and Max of samples to dB 

            desktopRMS = toDB(desktopRMS);
            micRMS = toDB(micRMS);
            desktopMx = toDB(desktopMx);
            micMx = toDB(micMx);

            //----------------------------------------------------------------------------
            // update max if sample max is greater or after 1 second

            float maxAlpha = 0.15f;
            UINT peakMeterDelayFrames = audioSamplesPerSec * 3;

            if (micMx > micMax)
                micMax = micMx;
            else
                micMax = maxAlpha * micMx + (1.0f - maxAlpha) * micMax;

            if(desktopMx > desktopMax)
                desktopMax = desktopMx;
            else
                desktopMax = maxAlpha * desktopMx + (1.0f - maxAlpha) * desktopMax;

            //----------------------------------------------------------------------------
            // update delayed peak meter

            if (micMax > micPeak || audioFramesSinceMicMaxUpdate > peakMeterDelayFrames) {
                micPeak = micMax;
                audioFramesSinceMicMaxUpdate = 0;
            } else {
                audioFramesSinceMicMaxUpdate += audioSampleSize;
            }

            if (desktopMax > desktopPeak || audioFramesSinceDesktopMaxUpdate > peakMeterDelayFrames) {
                desktopPeak = desktopMax;
                audioFramesSinceDesktopMaxUpdate = 0;
            } else {
                audioFramesSinceDesktopMaxUpdate += audioSampleSize;
            }

            //----------------------------------------------------------------------------
            // low pass the level sampling

            float rmsAlpha = 0.15f;
            desktopMag = rmsAlpha * desktopRMS + desktopMag * (1.0f - rmsAlpha);
            micMag = rmsAlpha * micRMS + micMag * (1.0f - rmsAlpha);

            //----------------------------------------------------------------------------
            // update the meter about every 50ms

            audioFramesSinceMeterUpdate += audioSampleSize;
            if (audioFramesSinceMeterUpdate >= (audioSampleSize*5)) {
                PostMessage(hwndMain, WM_COMMAND, MAKEWPARAM(ID_MICVOLUMEMETER, VOLN_METERED), 0);
                audioFramesSinceMeterUpdate = 0;
            }

            //----------------------------------------------------------------------------
            // mix mic and desktop sound
            // also, it's perfectly fine to just mix into the returned buffer

            if (bMicEnabled && micBuffer)
                MixAudio(mixBuffer.Array(), micBuffer, audioSampleSize*2, bForceMicMono);

            EncodeAudioSegment(mixBuffer.Array(), audioSampleSize, timestamp);
        }

        //-----------------------------------------------

        if (!bRecievedFirstAudioFrame && pendingAudioFrames.Num())
            bRecievedFirstAudioFrame = true;
    }

    desktopMag = desktopMax = desktopPeak = VOL_MIN;
    micMag = micMax = micPeak = VOL_MIN;

    PostMessage(hwndMain, WM_COMMAND, MAKEWPARAM(ID_MICVOLUMEMETER, VOLN_METERED), 0);

    for (UINT i=0; i<pendingAudioFrames.Num(); i++)
        pendingAudioFrames[i].audioData.Clear();

    AvRevertMmThreadCharacteristics(hTask);
}