// -----------------------------------------------------------------------------
bool ofxRtMidiIn::openPort(unsigned int portNumber) {	
	// handle RtMidi exceptions
	try {
		closePort();
		midiIn.setCallback(&_midiMessageCallback, this);
		midiIn.openPort(portNumber, "ofxMidi Input "+ofToString(portNumber));
	}
	catch(RtMidiError& err) {
		ofLogError("ofxMidiIn") << "couldn't get open port " << portNumber << ": " << err.what();
		return false;
	}
	portNum = portNumber;
	portName = midiIn.getPortName(portNumber);
	bOpen = true;
	ofLogVerbose("ofxMidiIn") << "opened port " << portNumber << " " << portName;
	return true;
}