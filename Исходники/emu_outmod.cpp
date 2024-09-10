int EmuOutMod::Pause(int pause) {
    if(pause) {
        waveOutPause(m_hwo);
        m_playing = false;
    } else {
        waveOutRestart(m_hwo);
        m_playing = true;
    }
    return !pause;
}