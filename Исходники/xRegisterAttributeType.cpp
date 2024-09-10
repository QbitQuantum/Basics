//************************************
// Method:    CreateRegisterAttributeTypeProto
// FullName:  CreateRegisterAttributeTypeProto
// Access:    public
// Returns:   CKERROR
// Qualifier:
// Parameter: CKBehaviorPrototype **pproto
//************************************
CKERROR CreateRegisterAttributeTypeProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("RegisterAttribute");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("In");
	proto->DeclareOutput("Out");
	proto->DeclareOutput("Error");

	proto->DeclareInParameter("Name",CKPGUID_STRING);
	proto->DeclareInParameter("Category",CKPGUID_STRING);
	proto->DeclareInParameter("Default Value",CKPGUID_STRING);
	proto->DeclareInParameter("Parameter Type",CKPGUID_PARAMETERTYPE);
	proto->DeclareInParameter("Compatible Class",CKPGUID_CLASSID);

	proto->DeclareInParameter("User",CKPGUID_BOOL,"TRUE");
	proto->DeclareInParameter("Save",CKPGUID_BOOL,"TRUE");


	proto->SetBehaviorCallbackFct( RegisterAttributeTypeCB );


	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	
	proto->SetFunction(RegisterAttributeType);
	*pproto = proto;
	return CK_OK;
}