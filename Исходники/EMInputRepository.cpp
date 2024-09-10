bool
EMInputRepository	::	SetAsActiveMIDIInput(int32 p_vInputID, int32 p_vOutputID)
{
	LockContainer();
	try
	{
		Rewind();
		while(Current() != NULL)
		{
			EMRealtimeInputDescriptor* opInput = Current();
			if((opInput -> GetType() & EM_TYPE_MIDI) > 0)
			{
				EMRealtimeMIDIInputDescriptor* opMIDIInput =
					 static_cast<EMRealtimeMIDIInputDescriptor*>(opInput);

				if(opMIDIInput -> GetID() == p_vInputID)
					opMIDIInput -> SetActive(true, p_vOutputID);
				else
					opMIDIInput -> SetActive(false, 0);
			}
			Next();
		}
	}
	catch(...)
	{
		EMDebugger("ERROR! Exception while setting active MIDI track!");
	}
	UnlockContainer();
	return true;
}