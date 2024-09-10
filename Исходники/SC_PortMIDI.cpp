/*
-------------------------------------------------------------
*/
static void midiCleanUp()
{
	lock_guard<SC_Lock> mulo(gPmStreamMutex);

	if(gMIDIInitialized) {
		for (int i=0; i<gNumMIDIOutPorts; ++i) {
			Pm_Abort(gMIDIOutStreams[i]);
			Pm_Close(gMIDIOutStreams[i]);
		}
		for (int i=0; i<gNumMIDIInPorts; ++i) {
			Pm_Abort(gMIDIInStreams[i]);
			Pm_Close(gMIDIInStreams[i]);
		}

		gNumMIDIOutPorts = 0;
		gNumMIDIInPorts = 0;
	}

	// set the stream pointers to NULL
	memset(gMIDIInStreams,0,kMaxMidiPorts*sizeof(PmStream*));
	memset(gMIDIOutStreams,0,kMaxMidiPorts*sizeof(PmStream*));

	// delete the objects that map in/out indices to Pm dev indices
	gMidiInputIndexToPmDevIndex.clear();
	gMidiOutputIndexToPmDevIndex.clear();

	gMIDIInitialized = false;
}