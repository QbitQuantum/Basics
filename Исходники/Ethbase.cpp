/**
Process processes a packet received from the packet driver.
@param aPdu The Packet to be sent (actually an RMBufPkt).
@param aLLC Unclear.
*/
EXPORT_C void CLANLinkCommon::Process(RMBufChain& aPdu, TAny* /*aLLC*/)
{
	TUint16 etherCode;
	TUint8* etherPtr;
	TUint etherHeaderSize;
	TBool packetProcessed=EFalse;
	TInt ret=GetProtocolType(aPdu,etherCode,etherPtr,etherHeaderSize);
	if (ret==KErrNone)
		{ // It's an ethernet packet of some kind.

		// Dump it to the log in pcap format
#ifdef TCPDUMP_LOGGING
		//Find absolute time now
		TTime timeNow;
		timeNow.HomeTime();

		RMBufPacket& pkt = (RMBufPacket&)aPdu;
		pkt.Unpack();
		iLogger->DumpFrame(timeNow,aPdu);
		pkt.Pack();
#endif

		TUint bearerLim = iBearers->Count();
		for(TUint index=0;index<bearerLim && !packetProcessed;index++)
			{
			CLanxBearer* bearer=(*iBearers)[index];
			if (BearerIsActive(bearer))
				{
				if(bearer->WantsProtocol(etherCode,etherPtr))
					{
					RMBufPacket& pkt = (RMBufPacket&)aPdu;
					pkt.Unpack();
					pkt.TrimStart(etherHeaderSize);
					pkt.Pack();
					bearer->Process(aPdu, (TAny*)(TUint32)etherCode);	// process expects ether type, but fixed function definition...
					packetProcessed=ETrue;
					}
				}
			}
		}
	if (ret!=KErrNone || !packetProcessed)
		{
		__FLOG_STATIC(KEther802LogTag1, KEthLogTag2, _L ("CLANLinkCommon::Process() - dropping packet - unrecognised type"));
		aPdu.Free(); // Something strange about the packet - bin it
		}
}