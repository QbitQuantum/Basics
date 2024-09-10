CKERROR CreateLoadCISProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("Load CIS");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("Start");
	proto->DeclareOutput("Success");
	proto->DeclareOutput("Error");

	proto->DeclareInParameter("Learning Application ID", CKPGUID_INT,"0");
	proto->DeclareOutParameter("Error String ", CKPGUID_STRING,"0");
	
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);

	proto->SetFunction(LoadCIS);
	*pproto = proto;
	return CK_OK;
}