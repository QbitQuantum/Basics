void WindowsAudioInputDevice::initializeIfNecessary() {
  if (ourAudioInputPorts != NULL) return; // we've already been initialized
  numAudioInputPorts = waveInGetNumDevs();
  ourAudioInputPorts = new AudioInputPort[numAudioInputPorts];

  // Initialize each audio input port
  for (unsigned i = 0; i < numAudioInputPorts; ++i) {
    AudioInputPort& port = ourAudioInputPorts[i];
    port.index = i;
    port.open(); // to set the port name
    port.close();
  }
}