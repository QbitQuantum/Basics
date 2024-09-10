/*
 *******************************************************************
 * Function: CKERROR CreateGetCISProto( CKBehaviorPrototype** behaviorPrototypePtr )
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
CKERROR CreateGetCISProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype(GBL_CI_API_ENTRY("GetCIS"));
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("Start");
	proto->DeclareOutput("Success");
	proto->DeclareOutput("Error");

	proto->DeclareInParameter("CIS ID", CKPGUID_INT,"0");
	proto->DeclareOutParameter("GetErrorCode", GUID_TGBLERROR,"0");

	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);

	proto->SetFunction(GetCIS);
	*pproto = proto;
	return CK_OK;
}