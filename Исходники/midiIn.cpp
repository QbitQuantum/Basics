int main(){
	MIDIIn midiIn;

	// Check available ports vs. specified
	unsigned portToOpen = 0;
	unsigned numPorts = midiIn.getPortCount();

	if(portToOpen >= numPorts){
		printf("Invalid port specifier!\n");
	}

	try {

		// Print out names of available input ports
		for(unsigned i=0; i<numPorts; ++i){
			printf("Port %u: %s\n", i, midiIn.getPortName(i).c_str());
		}

		// Open the port specified above
		midiIn.openPort(portToOpen);
	}
	catch(MIDIError &error){
		error.printMessage();
		return 1;
	}

	// Set our callback function.  This should be done immediately after
	// opening the port to avoid having incoming messages written to the
	// queue instead of sent to the callback function.
	midiIn.setCallback(&midiCallback);

	// Don't ignore sysex, timing, or active sensing messages.
	midiIn.ignoreTypes(false, false, false);

	printf("\nReading MIDI input ... press <enter> to quit.\n");
	getchar();
}