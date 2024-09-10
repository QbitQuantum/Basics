void AudioInputElement::resetCaps()
{
    QbAudioCaps::SampleFormat sampleFormat;
    int channels;
    int sampleRate;
    this->m_audioDevice.preferredFormat(AudioDevice::DeviceModeCapture,
                                        &sampleFormat,
                                        &channels,
                                        &sampleRate);

    QbAudioCaps caps;
    caps.isValid() = true;
    caps.format() = sampleFormat;
    caps.bps() = QbAudioCaps::bytesPerSample(sampleFormat);
    caps.channels() = channels;
    caps.rate() = sampleRate;
    caps.layout() = channels > 1? QbAudioCaps::Layout_mono: QbAudioCaps::Layout_stereo;
    caps.align() = false;

    this->setCaps(caps.toCaps());
}