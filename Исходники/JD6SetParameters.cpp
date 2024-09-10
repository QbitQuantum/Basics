//************************************
// Method:    CreateJD6SetParametersProto
// FullName:  CreateJD6SetParametersProto
// Access:    public 
// Returns:   CKERROR
// Qualifier:
// Parameter: CKBehaviorPrototype **pproto
//************************************
CKERROR CreateJD6SetParametersProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("PJD6SetParameters");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("In0");
	proto->DeclareOutput("Out0");

	
	
	proto->SetBehaviorCallbackFct( JD6SetParametersCB );
	
	
	proto->DeclareInParameter("Body B",CKPGUID_3DENTITY,"ball2");
	proto->DeclareInParameter("Drive Linear Velocity",CKPGUID_VECTOR);
	proto->DeclareInParameter("Drive Angular Velocity",CKPGUID_VECTOR);
	proto->DeclareInParameter("Drive Position",CKPGUID_VECTOR);
	proto->DeclareInParameter("Drive Orientation",CKPGUID_QUATERNION);
	
	proto->DeclareInParameter("Ratio",CKPGUID_FLOAT,"0");
	
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorFlags(CKBEHAVIOR_TARGETABLE);
	
	proto->SetFunction(JD6SetParameters);
	*pproto = proto;
	return CK_OK;
}