void QAudioInputPrivate::suspend()
{
    if(deviceState == QAudio::ActiveState) {
        waveInReset(hWaveIn);
        deviceState = QAudio::SuspendedState;
        emit stateChanged(deviceState);
    }
}