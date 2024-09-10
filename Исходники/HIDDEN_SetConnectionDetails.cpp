/*
*******************************************************************
* Function:CreateAddPacketProto()
*
* Description : Behavior prototypes describe the Bb's internal structure.   
*
* Parameters :  CKBehaviorPrototype **pproto :  r,w
*
* Returns :	CKERROR = CK_OK if the building block prototype was correct created.  
*
*******************************************************************
*/
CKERROR CreateSetCIConnectionDetailsProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype("SetMOConnectionDetails");
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("Set Details");
	proto->DeclareOutput("Set Exit");

	proto->DeclareInParameter("network message", CKPGUID_STRING,"GBLInternal");
	proto->DeclareInParameter("network connection id", CKPGUID_INT,"");
   
	if(!GBLDebugBuild)
	{
		proto->SetFlags(CK_BEHAVIORPROTOTYPE_HIDDEN);
	}else
	{
		proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	}

	proto->SetFunction(SetCIConnectionDetails);
	
	*pproto = proto;
	return CK_OK;
}