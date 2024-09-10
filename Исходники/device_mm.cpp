  void
  MMAudioDevice::update() {
    ADR_GUARD("MMAudioDevice::update");

    // if a buffer is done playing, add it to the queue again
    for (int i = 0; i < BUFFER_COUNT; ++i) {
      WAVEHDR& wh = m_buffers[i];
      if (wh.dwFlags & WHDR_DONE) {

        // unprepare
        MMRESULT result = waveOutUnprepareHeader(m_device, &wh, sizeof(wh));
        if (result != MMSYSERR_NOERROR) {
          ADR_LOG("waveOutUnprepareHeader failed");
        }

        // fill with new samples
        read(BUFFER_LENGTH / 4, wh.lpData);
        wh.dwFlags = 0;

        // prepare
        result = waveOutPrepareHeader(m_device, &wh, sizeof(wh));
        if (result != MMSYSERR_NOERROR) {
          ADR_LOG("waveOutPrepareHeader failed");
        }

        // write
        result = waveOutWrite(m_device, &wh, sizeof(wh));
        if (result != MMSYSERR_NOERROR) {
          ADR_LOG("waveOutWrite failed");
        }
      }
    }
    Sleep(10);
  }