void ofxPDSPMidiIn::openPort(int index){
    if(connected){
        closePort();
    }
    
    midiIn.openPort(index); 
    
    if(midiIn.isOpen()){
        midiIn_p = &midiIn;
        midiIn_p->addListener(this); // add ofApp as a listener
        connected = true;
        bufferChrono = chrono::high_resolution_clock::now();
    }
}