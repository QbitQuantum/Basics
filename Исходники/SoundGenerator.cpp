bool SoundGenerator::Stop()
{
    return waveOutReset(m_hDeviceHandle) != MMSYSERR_NOERROR;
}