/*
 *******************************************************************
 * Function: int CreateBehaviourPrototype() 
 *
 * Description : Returns the number of plugins in this DLL
 *		
 * Paramters :
 *    CKBehaviorPrototype w ppProto
 *
 * Returns : CKERROR - Standard virtools return type
 *
 *******************************************************************
 */
CKERROR CGBLLOGetMOStatus::CreateBehaviourPrototype(CKBehaviorPrototype** ppProto)
{
	CKERROR err = CK_OK;

	// Create the CKBehaviorPrototype object
	CKBehaviorPrototype *pProto = CreateCKBehaviorPrototype("GBLLOStartMO");
	if (!pProto)
		return NULL;

	// Set the B-Ins, B-Outs, P-Ins and P-Outs
	if (eParamInputMO != pProto->DeclareInParameter("Set Measured Objective", CKGUID_CGBLMO_PARAMETER))
		assert(NULL);
	if (eParamOutputGetError != pProto->DeclareOutParameter("Get Error", GUID_TGBLERROR))
		assert(NULL);
	if (eParamOutputGetStatus != pProto->DeclareOutParameter("Get Status", CKPGUID_BOOL))
		assert(NULL);
	if (eBehInputStart != pProto->DeclareInput("InS tart"))
		assert(NULL);
	if (eBehOutputDone != pProto->DeclareOutput("Out Done"))
		assert(NULL);
	if (eBehOutputError != pProto->DeclareOutput("Out Error"))
		assert(NULL);
	
	// flags
	pProto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);

	// Set the behaviour function
	pProto->SetFunction(BehaviourFunction);

	// Everything must have gone OK, pass back Proto pointer to Virtools
	*ppProto = pProto;
	return err;
}