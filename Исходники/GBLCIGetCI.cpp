/*
 *******************************************************************
 * Function: CKERROR CreateGetCIValueProto( CKBehaviorPrototype** behaviorPrototypePtr )
 *
 * Description : The prototype creation function will be called the first time 
 *               a behavior must be created to create the CKBehaviorPrototype 
 *               that contains the description of the behavior.
 *
 * Parameters :
 *    behaviorPrototypePtr    w   Pointer to a CKBehaviorPrototype object that 
 *                                describes the behavior's internal structure 
 *                                and relationships with other objects.
 *
 * Returns : CKERROR
 *
 *******************************************************************
 */
CKERROR CreateGetCIValueProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype(GBL_CI_API_ENTRY("GetCI"));
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("Start");
	proto->DeclareOutput("Success");
	
	proto->DeclareInParameter("Configurable Information", CIPARAMETERGUID);
	
	proto->DeclareOutParameter("Configurable Information Value", CKPGUID_STRING);

	proto->DeclareSetting("Get CI by unique name",CKPGUID_BOOL,"FALSE");
	proto->DeclareSetting("Get value as string",CKPGUID_BOOL,"FALSE");
	proto->DeclareSetting("Output custom values",CKPGUID_BOOL,"FALSE");
	proto->DeclareSetting("Output on change",CKPGUID_BOOL,"FALSE");


	proto->SetBehaviorFlags((CK_BEHAVIOR_FLAGS)( CKBEHAVIOR_VARIABLEPARAMETEROUTPUTS ));
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	proto->SetBehaviorCallbackFct(GetCIValueCB);
	proto->SetFunction(GetCIValue);

	*pproto = proto;
	return CK_OK;
}