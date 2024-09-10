// -----------------------------------------------------------------------------
bool ofxRtMidiOut::openPort(unsigned int portNumber) {	
	// handle rtmidi exceptions
	try {
		closePort();
		midiOut.openPort(portNumber, "ofxMidi Output "+ofToString(portNumber));
	}
	catch(RtError& err) {
		ofLog(OF_LOG_ERROR, "ofxMidiOut: couldn't open port %i: %s", portNumber, err.what());
		return false;
	}
	portNum = portNumber;
	portName = midiOut.getPortName(portNumber);
	bOpen = true;
	ofLog(OF_LOG_VERBOSE, "ofxMidiOut: opened port %i %s", portNum, portName.c_str());
	return true;
}