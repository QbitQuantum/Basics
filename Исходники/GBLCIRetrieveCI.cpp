CKERROR CreateRetrieveCIProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype(GBL_CI_API_ENTRY("RetrieveCI"));
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("Start");
	proto->DeclareOutput("Success");
	proto->DeclareOutput("Error");
	
	proto->DeclareInParameter("Configurable Information ID", CKPGUID_INT);

	proto->DeclareOutParameter("Configurable Information Value", CKPGUID_STRING);

	proto->DeclareOutParameter("GetErrorCode", GUID_TGBLERROR);

	proto->DeclareSetting("Get value as string",CKPGUID_BOOL,"FALSE");
	proto->DeclareSetting("Output custom values",CKPGUID_BOOL,"FALSE");

	proto->SetBehaviorFlags((CK_BEHAVIOR_FLAGS)( CKBEHAVIOR_VARIABLEPARAMETEROUTPUTS ));
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorCallbackFct(RetrieveCICB);
	proto->SetFunction(RetrieveCI);

	*pproto = proto;
	return CK_OK;
}