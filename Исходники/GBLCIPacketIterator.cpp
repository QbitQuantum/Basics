CKERROR CreatePacketIteratorProto(CKBehaviorPrototype **pproto)
{
	CKBehaviorPrototype *proto = CreateCKBehaviorPrototype(GBL_CI_API_ENTRY("PacketIterator"));
	if(!proto) return CKERR_OUTOFMEMORY;

	proto->DeclareInput("On/Reset");
	proto->DeclareOutput("Exit On/Reset");

	proto->DeclareInput("Loop In");
	proto->DeclareOutput("Loop Out");
	
	proto->DeclareOutParameter("Target user id", CKPGUID_INT,"-1");
	proto->DeclareOutParameter("Data", CKPGUID_STRING,"");
	proto->DeclareOutParameter("Header", CKPGUID_STRING,"");
	proto->DeclareOutParameter("PacketType", GUID_GBLCI_EPACKET_TYPE,"");
	proto->DeclareOutParameter("Time Stamp", CKPGUID_INT,"-1");
    
	proto->DeclareLocalParameter(NULL, CKPGUID_INT); // packet index

	if(!GBLDebugBuild)
	{
		proto->SetFlags(CK_BEHAVIORPROTOTYPE_HIDDEN);
	}else
	{
		proto->SetFlags(CK_BEHAVIORPROTOTYPE_NORMAL);
	}

	proto->SetFunction(PacketIterator);

	*pproto = proto;
	return CK_OK;
}