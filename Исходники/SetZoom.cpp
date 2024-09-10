CKERROR CreateSetZoomProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("Set Zoom");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("In");
	proto->DeclareOutput("Out");
	
	proto->DeclareInParameter("Focal Length (mm)", CKPGUID_FLOAT, "50");
	
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetFunction(SetZoom);
  proto->SetBehaviorFlags(CKBEHAVIOR_TARGETABLE);
	
	*pproto = proto;
	return CK_OK;

}