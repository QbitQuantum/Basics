void WaveOut::ClearBuffers(){
    waveOutReset(this->waveHandle);
}