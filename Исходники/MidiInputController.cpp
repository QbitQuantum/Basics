bool MidiInputController::enablePort(int portNumber) {
    if(portNumber < 0)
        return false;

    try {
        MidiInputCallback *callback = new MidiInputCallback;
        RtMidiIn *rtMidiIn = new RtMidiIn;

        cout << "Enabling MIDI port " << portNumber << " (" << rtMidiIn->getPortName(portNumber) << ")\n";

        rtMidiIn->openPort(portNumber);				// Open the port
        rtMidiIn->ignoreTypes(true, true, true);	// Ignore sysex, timing, active sensing

        callback->controller = this;
        callback->midiIn = rtMidiIn;
        callback->inputNumber = portNumber;

        rtMidiIn->setCallback(MidiInputController::rtMidiStaticCallback, callback);

        activePorts_[portNumber] = callback;
    }
    catch(...) {
        return false;
    }

    return true;
}