CKERROR CreatePlayFFEffectProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = NULL;
	proto = CreateCKBehaviorPrototype("PlayFFEffect");
	if(!proto) return CKERR_OUTOFMEMORY;
	
	proto->DeclareInput("Init");
	proto->DeclareInput("play");
	proto->DeclareInput("stop");
	proto->DeclareInput("release device");
	

	proto->DeclareOutput("initiated");
	proto->DeclareOutput("play exit");
	proto->DeclareOutput("stopped");
	proto->DeclareOutput("released");

	proto->DeclareOutput("error");


	proto->DeclareInParameter("effect file",CKPGUID_STRING);
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetFunction( PlayFFEffect );

	proto->SetBehaviorCallbackFct(PlayFFECallBackObject);
	
	*pproto = proto;
	return CK_OK;

}