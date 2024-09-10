MIDIPlayer::MIDIPlayer(){
	if(midiOutOpen(&mid,(UINT)-1,0,0,0))
		exit(1);
		
	velocity = 127;
	setVoice(0); // default
}