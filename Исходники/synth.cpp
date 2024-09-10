int main(int argc, char** argv)
{

  if (argc != 2) {
    printf("Usage: synth file.sf2\n");
    exit(0);
  }

  LightFluidSynth *usynth;

  usynth = new LightFluidSynth();

  usynth->loadSF2(argv[1]);
//  usynth->loadSF2("tim.sf2");

  RtMidiIn *midiIn = new RtMidiIn();
  if (midiIn->getPortCount() == 0) {
    std::cout << "No MIDI ports available!\n";
  }
  midiIn->openPort(0);
  midiIn->setCallback( &midiCallback, (void *)usynth );
  midiIn->ignoreTypes( false, false, false );

//   RtAudio dac(RtAudio::LINUX_PULSE);
  RtAudio dac;
  RtAudio::StreamParameters rtParams;

  // Determine the number of devices available
  unsigned int devices = dac.getDeviceCount();
  // Scan through devices for various capabilities
  RtAudio::DeviceInfo info;
  for ( unsigned int i = 0; i < devices; i++ ) {
    info = dac.getDeviceInfo( i );
    if ( info.probed == true ) {
      std::cout << "device " << " = " << info.name;
      std::cout << ": maximum output channels = " << info.outputChannels << "\n";
    }
  }
//  rtParams.deviceId = 3;
  rtParams.deviceId = dac.getDefaultOutputDevice();
  rtParams.nChannels = 2;
  unsigned int bufferFrames = FRAME_SIZE;

  RtAudio::StreamOptions options;
  options.flags = RTAUDIO_SCHEDULE_REALTIME;

  dac.openStream( &rtParams, NULL, AUDIO_FORMAT, SAMPLE_RATE, &bufferFrames, &audioCallback, (void *)usynth, &options );
  dac.startStream();

  printf("\n\nPress Enter to stop\n\n");
  cin.get();
  dac.stopStream();

  delete(usynth);
  return 0;
}