/*
 *******************************************************************
 * Function: CKERROR CreateCISIteratorBBProto( CKBehaviorPrototype** behaviorPrototypePtr )
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
CKERROR CreateCISIteratorBBProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype(GBL_CI_API_ENTRY("CISIterator"));
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("On/Reset");
	proto->DeclareOutput("Exit On/Reset");

	proto->DeclareInput("Loop In");
	proto->DeclareOutput("Loop Out");

	    
	proto->DeclareOutParameter("value", CKPGUID_STRING,"-1");					
	proto->DeclareOutParameter("default value", CKPGUID_STRING,"-1");					

	proto->DeclareOutParameter("unique name", CKPGUID_STRING,"");
	proto->DeclareOutParameter("description", CKPGUID_STRING,"-1");					
	proto->DeclareOutParameter("access flags", CIPRTFLAGSGUID,"");				
	proto->DeclareOutParameter("parameter type", CKPGUID_PARAMETERTYPE,"-1");	
	proto->DeclareOutParameter("ci db index", CKPGUID_INT,"-1");	

	proto->DeclareLocalParameter(NULL, CKPGUID_INT); // index
	proto->DeclareLocalParameter(NULL, CKPGUID_INT); // cis size
	proto->DeclareLocalParameter(NULL, CKPGUID_POINTER); // ciid list
	proto->DeclareSetting("Read From Database", CKPGUID_BOOL,"FALSE");	
    
	proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);

	proto->SetBehaviorCallbackFct(CISIteratorCB);
	proto->SetFunction(CISIteratorBB);

	*pproto = proto;
	return CK_OK;
}