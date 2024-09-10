void ofxMidiOutProcessor::openPort(int portIndex){
    if(connected){
        closePort();
    }
    
    midiOut.openPort( portIndex );
    
    if( midiOut.isOpen() ){
        if(verbose) cout<<"[ofxPDSP]: connected to midi port "<<portIndex<<"\n";
        
        midiOut_p = &midiOut;
        
        startMidiDaemon();
        
        connected = true;
    }
}