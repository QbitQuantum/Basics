CKERROR CreateGetCurrentCameraProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("Get Current Camera");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("In");
	proto->DeclareOutput("Out");
	
	proto->DeclareOutParameter("Current Camera",CKPGUID_CAMERA);

	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetFunction(GetCurrentCamera);

	*pproto = proto;
	return CK_OK;
}