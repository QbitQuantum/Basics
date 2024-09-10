void AddSynthApp::initializePresets()
{
//    mPresetHandler.print();
    sequencer << synth.mPresetHandler;
    recorder << synth.mPresetHandler;
//    mKeyboardPresets.presets = &mPresetHandler;

    // MIDI Control of parameters
    int midiPort = 0;
    parameterMIDI.init(midiPort);
    parameterMIDI.connectControl(synth.mCumulativeDelay, 75, 1);
    parameterMIDI.connectControl(synth.mCumulativeDelayRandomness, 76, 1);
    parameterMIDI.connectControl(synth.mArcStart, 77, 1);
    parameterMIDI.connectControl(synth.mArcSpan, 78, 1);

    // MIDI control of presets
    // 74 71 91 93 73 72 5 84 7
    // 75 76 77 78 74 71 24 102
    presetMIDI.init(midiPort, synth.mPresetHandler);
    presetMIDI.setMorphControl(102, 1, 0.0, 8.0);
    // MIDI preset mapping
//    presetMIDI.connectNoteToPreset(1, 0, 36, 24, 59);

    // Print out names of available input ports
    for(unsigned i=0; i< midiIn.getPortCount(); ++i){
        printf("Port %u: %s\n", i, midiIn.getPortName(i).c_str());
    }
    try {
        // Open the port specified above
        midiIn.openPort(midiPort);
    }
    catch(MIDIError &error){
        error.printMessage();
    }

    midiIn.setCallback(AddSynthApp::midiCallback, this);
}