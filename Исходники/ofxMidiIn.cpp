// --------------------------------------------------------------------------------------
void ofxMidiIn::openPort(string _deviceName){
	if ( nPorts == 0 ) {
		ofLogError() << "No ports available!";
		return;
	}
	
	// Iterate through MIDI ports, find requested devices
	bool foundDevice = false;
	int _port;
	for(unsigned int i=0; i < nPorts; ++i){
		string portName = portNames[i].c_str();
		if(portName.compare(_deviceName) == 0) {
			foundDevice = true;
			_port = i;
		}
	}
	if(!foundDevice) {
		// if not found
		ofLogError() << "The selected port is not available";
		return;
	}
	
	openPort( _port );	
	
}