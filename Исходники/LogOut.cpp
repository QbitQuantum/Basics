CKERROR CreateLogEntryProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("pLogEvent");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("In");
	proto->DeclareInput("Off");
	proto->DeclareOutput("Message");

	proto->DeclareOutput("Error");
	proto->DeclareOutput("Warning");
	proto->DeclareOutput("Info");
	proto->DeclareOutput("Trace");
	proto->DeclareOutput("Debug");


	
	proto->DeclareOutParameter("Entry",CKPGUID_STRING);
	
	proto->DeclareOutParameter("Type",CKPGUID_INT);
	proto->DeclareOutParameter("Component",CKPGUID_STRING);


	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorFlags((CK_BEHAVIOR_FLAGS)( CKBEHAVIOR_VARIABLEPARAMETERINPUTS  ));
	proto->SetFunction(LogEntry);
	proto->SetBehaviorCallbackFct(LogEntryCB);


	*pproto = proto;


	return CK_OK;

}