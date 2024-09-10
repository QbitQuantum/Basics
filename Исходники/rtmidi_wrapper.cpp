    /* returns 0 on failure */
    int
    start_midi(int port)
    {
        if(midi.getPortCount() < 1) {
            std::cout << "No MIDI ports available!\n";
            return 0;
        }

        try {
            midi.openPort(port);
        } catch(RtError &error) {
            return 0;
        }

        // don't ignore sysex, timing, or active sensing messages
        midi.ignoreTypes(false, false, false);

        return 1;
    }