CKERROR CreateMidiEventBehaviorProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("Midi Event");
	if(!proto) return CKERR_OUTOFMEMORY;
	
	proto->DeclareInput("On");
	proto->DeclareInput("Off");
	
	proto->DeclareOutput("Activated");
	proto->DeclareOutput("Deactivated");

	proto->DeclareInParameter("Channel", CKPGUID_INT, "0");
	proto->DeclareInParameter("Note 1", CKPGUID_INT, "0");
	
	proto->DeclareLocalParameter(NULL, CKPGUID_BOOL, "FALSE"); // Combination was ok

	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetFunction(MidiEvent);
	proto->SetBehaviorFlags((CK_BEHAVIOR_FLAGS)(CKBEHAVIOR_VARIABLEPARAMETERINPUTS));
	
  proto->SetBehaviorCallbackFct( MidiEventCallBack );
  
	*pproto = proto;
	return CK_OK;
}