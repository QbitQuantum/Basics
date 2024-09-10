//This copies the data at requestHeader, so you can free the memory after this has been called
int RequestCommon(char * sourceIP, char * destinationIP, char * dstHostName, request_hdr_t * requestHeader, unsigned int requestSize, me_t * outboundPendingME, char * parentFuncName){
	int ret;
	unsigned short sourcePort = 0xDEAD;
	unsigned short destinationPort = 0xBEEF;
	unsigned char dstMac[6] = {0,0,0,0,0,0};
	ULONG dstMacLong[2] = {0,0};
	ULONG MACSize = 6;
	RawPacket RP;
	IPAddr srcIPAddr, dstIPAddr;

	srcIPAddr = inet_addr(sourceIP);
	dstIPAddr = inet_addr(destinationIP);

	//This is a quick hack to make it server be a bit smarter 
	//about what dst MAC is uses - gateway if the dst IP is non-local, 
	//otherwise the MAC specifically for the dst host
	//ASSUMPTION: that all hosts on the same /24 are on the same ethernet segment
	if(memcmp(&srcIPAddr, &dstIPAddr, 3) == 0){
		//send to a local host on the same ethernet segment directly
		ret = SendARP(dstIPAddr, srcIPAddr, &dstMacLong, &MACSize);
		if(ret != NO_ERROR){
			if(gUseBroadcastMAC){
				printf("%s: RequestCommon: Failed to get the MAC address for the destination host on the same local network. Defaulting to broadcast MAC\n", parentFuncName);
				memset(&dstMac, 0xFF, 6);
			}
			else{
				printf("%s: RequestCommon: Failed to get the MAC address for the destination host on the same local network. Broadcast MAC disabled, erroring out\n", parentFuncName);
				//UpdateReadinessByHostID(hostID, ARP_FAIL);
				//If we're going to error out and not send the packet, we need to delete the pending events
				//We will not delete the null measurement because it will have actually been sent
				if(strcmp("BuildNullSelfMeasurementRequestPacket", parentFuncName) != 0){
					if(strcmp("BuildSelfMeasurementRequestPacket", parentFuncName) != 0){
						ret = SelectPreviousPendingIDFromPendingME(outboundPendingME->id,outboundPendingME->nonce, &outboundPendingME->previousPendingID);
						if(ret != GENERIC_SUCCESS){
							printf("RequestCommon: SelectPreviousPendingIDFromPendingMEByID failed\n");
							return ret;
						}
						if(!gQuiet) printf("Deleting PendingMeasurementEvent id = %u\n", outboundPendingME->previousPendingID);
						DeleteFromTableByID("PendingMeasurementEvents", outboundPendingME->previousPendingID);
					}
					if(!gQuiet) printf("Deleting PendingMeasurementEvent id = %u\n", outboundPendingME->id);
					DeleteFromTableByID("PendingMeasurementEvents", outboundPendingME->id);
				
					return GENERIC_ERROR;
				}
			}
		}
		else{
			memcpy(&dstMac, &dstMacLong, 6);
		}
		RP.CreatePacket(globDeviceInfoPtr->PhysicalAddress, dstMac,
						inet_addr(sourceIP),inet_addr(destinationIP),sourcePort,destinationPort,
						(UCHAR*)requestHeader, requestSize);
	}
	else{
		//send to a non-local host, by way of the gateway
		RP.CreatePacket(globDeviceInfoPtr->PhysicalAddress, globDeviceInfoPtr->GatewayPhysicalAddress,
						inet_addr(sourceIP),inet_addr(destinationIP),sourcePort,destinationPort,
						(UCHAR*)requestHeader, requestSize);
	}

	RP.SendPacket(globDevice);

	return GENERIC_SUCCESS;
}