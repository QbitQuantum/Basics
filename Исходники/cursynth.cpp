  void Cursynth::setupMidi() {
    RtMidiIn* midi_in = new RtMidiIn();
    if (midi_in->getPortCount() <= 0) {
      std::cout << "No midi devices found.\n";
    }

    // Setup MIDI callbacks for every MIDI device.
    // TODO: Have a menu for only enabling some MIDI devices.
    for (unsigned int i = 0; i < midi_in->getPortCount(); ++i) {
      RtMidiIn* device = new RtMidiIn();
      device->openPort(i);
      device->setCallback(&midiCallback, (void*)this);
      midi_ins_.push_back(device);
    }

    delete midi_in;
  }