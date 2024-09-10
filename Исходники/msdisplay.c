/* ------------------------------------------------------------------------- */
Boolean SetUpMidi(void)
{
	char buff[32], *name;

	InitTblLibEv();
	
	if ( !MidiShare()) {
		printf ("MidiShare not available\n");
		return false;
	}

	myRefNum = MidiOpen(AppliName);
	if ( myRefNum == MIDIerrSpace ){
		printf ( "Too much MidiShare client applications\n");
		return false;
	}
	
	MidiSetRcvAlarm(myRefNum,ReceiveEvents);
	MidiConnect( 0, myRefNum, true);
	myFilter = MidiNewFilter();
	InstallFilter( myRefNum, myFilter);
	return true;
}