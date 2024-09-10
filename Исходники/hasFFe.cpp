CKERROR CreateHasFFEffectsProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = NULL;
	proto = CreateCKBehaviorPrototype("JHasForceFeedback");
	if(!proto) return CKERR_OUTOFMEMORY;
	
	proto->DeclareInput("In");
	proto->DeclareOutput("yes");
	proto->DeclareOutput("no");
	
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetFunction( HasFFEffects );
	proto->SetBehaviorCallbackFct(PlayFFECallBackObject2);
	
	*pproto = proto;
	return CK_OK;
	
}