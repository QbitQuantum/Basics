void rtsyn_midiports_close(void){
	UINT port;
	
	for(port=0;port<rtsyn_portnumber;port++){
		if( MMSYSERR_NOERROR!=midiInStop(hMidiIn[port]) )
			ctl->cmsg(  CMSG_ERROR, VERB_NORMAL,"MIDI Stop Error\n");
		if( MMSYSERR_NOERROR!=midiInReset(hMidiIn[port]) ) 
			ctl->cmsg(  CMSG_ERROR, VERB_NORMAL,"MIDI Rest Error\n");
		if( MMSYSERR_NOERROR!=midiInClose(hMidiIn[port]) ) 
			ctl->cmsg(  CMSG_ERROR, VERB_NORMAL,"MIDI Close Error\n");
	}
}