bool QWindowsAudioDeviceInfo::testSettings(const QAudioFormat& format) const
{
    WAVEFORMATEXTENSIBLE wfx;
    if (qt_convertFormat(format, &wfx)) {
        // query only, do not open device
        if (mode == QAudio::AudioOutput) {
            return (waveOutOpen(NULL, UINT_PTR(devId), &wfx.Format, 0, 0,
                                WAVE_FORMAT_QUERY) == MMSYSERR_NOERROR);
        } else { // AudioInput
            return (waveInOpen(NULL, UINT_PTR(devId), &wfx.Format, 0, 0,
                                WAVE_FORMAT_QUERY) == MMSYSERR_NOERROR);
        }
    }

    return false;
}