bool UBWaveRecorder::close()
{
    if (waveInReset(mWaveInDevice) != MMSYSERR_NOERROR)
    {
        setLastErrorMessage("Cannot reset wave in device ");
        return false;
    }

    foreach(WAVEHDR* buffer, mWaveBuffers)
    {
        waveInUnprepareHeader(mWaveInDevice, buffer, sizeof(WAVEHDR));
        delete [] buffer->lpData;
        delete buffer;
    }