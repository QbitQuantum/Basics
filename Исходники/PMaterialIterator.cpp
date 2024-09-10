//************************************
// Method:    CreatePMaterialIteratorProto
// FullName:  CreatePMaterialIteratorProto
// Access:    public 
// Returns:   CKERROR
// Qualifier:
// Parameter: CKBehaviorPrototype **pproto
//************************************
CKERROR CreatePMaterialIteratorProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("PMaterialIterator");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("In");

	proto->DeclareInput("Next");
	proto->DeclareOutput("Finish");
	proto->DeclareOutput("Loop");

	proto->DeclareLocalParameter("current result", CKPGUID_POINTER, "0");

	proto->DeclareOutParameter("Index",CKPGUID_INT);
	proto->DeclareOutParameter("XML Link",VTE_XML_MATERIAL_TYPE);
	proto->DeclareOutParameter("Name",CKPGUID_STRING);
	proto->DeclareOutParameter("Dynamic Friction",CKPGUID_FLOAT);
	proto->DeclareOutParameter("Static Friction",CKPGUID_FLOAT);
	proto->DeclareOutParameter("Restitution",CKPGUID_FLOAT);
	proto->DeclareOutParameter("Dynamic Friction V",CKPGUID_FLOAT);
	proto->DeclareOutParameter("Static Friction V",CKPGUID_FLOAT);
	proto->DeclareOutParameter("Direction of Anisotropy ",CKPGUID_VECTOR);
	proto->DeclareOutParameter("Friction Combine Mode",VTE_MATERIAL_COMBINE_MODE);
	proto->DeclareOutParameter("Restitution Combine Mode",VTE_MATERIAL_COMBINE_MODE);
	proto->DeclareOutParameter("Flags",VTF_MATERIAL_FLAGS);
	proto->DeclareOutParameter("Result",VTS_MATERIAL);

	proto->SetBehaviorCallbackFct( PMaterialIteratorCB );
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorFlags(CKBEHAVIOR_TARGETABLE);
	
	proto->SetFunction(PMaterialIterator);
	*pproto = proto;
	return CK_OK;
}