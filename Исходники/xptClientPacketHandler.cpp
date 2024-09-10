/*
 * Called when a packet with the opcode XPT_OPC_S_WORKDATA1 is received
 * This is the first version of xpt 'getwork'
 */
bool xptClient_processPacket_blockData1(xptClient_t* xptClient)
{
	// parse block data
	bool recvError = false;
	xptPacketbuffer_beginReadPacket(xptClient->recvBuffer);
	// update work info, GBT style (sha256 & scrypt)
	xptClient->blockWorkInfo.version = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);				// version
	xptClient->blockWorkInfo.height = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);				// block height
	xptClient->blockWorkInfo.nBits = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);				// nBits
	// New in xpt version 6 - Targets are send in compact format (4 bytes instead of 32)
	uint32 targetCompact = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	uint32 targetShareCompact = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	xptClient_getDifficultyTargetFromCompact(targetCompact, (uint32*)xptClient->blockWorkInfo.target);
	xptClient_getDifficultyTargetFromCompact(targetShareCompact, (uint32*)xptClient->blockWorkInfo.targetShare);
	xptClient->blockWorkInfo.nTime = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);				// nTimestamp
	xptPacketbuffer_readData(xptClient->recvBuffer, xptClient->blockWorkInfo.prevBlockHash, 32, &recvError);	// prevBlockHash
	xptPacketbuffer_readData(xptClient->recvBuffer, xptClient->blockWorkInfo.merkleRoot, 32, &recvError);		// merkleroot
	// coinbase part1 (16bit length + data)
	xptClient->blockWorkInfo.coinBase1Size = xptPacketbuffer_readU16(xptClient->recvBuffer, &recvError);
	xptPacketbuffer_readData(xptClient->recvBuffer, xptClient->blockWorkInfo.coinBase1, xptClient->blockWorkInfo.coinBase1Size, &recvError);
	// coinbase part2 (16bit length + data)
	xptClient->blockWorkInfo.coinBase2Size = xptPacketbuffer_readU16(xptClient->recvBuffer, &recvError);
	xptPacketbuffer_readData(xptClient->recvBuffer, xptClient->blockWorkInfo.coinBase2, xptClient->blockWorkInfo.coinBase2Size, &recvError);
	// information about remaining tx hashes
	xptClient->blockWorkInfo.txHashCount = xptPacketbuffer_readU16(xptClient->recvBuffer, &recvError);
	printf("New block data - height: %d tx count: %d\n", xptClient->blockWorkInfo.height, xptClient->blockWorkInfo.txHashCount);
	for(uint32 i=0; i<xptClient->blockWorkInfo.txHashCount; i++)
	{
		xptPacketbuffer_readData(xptClient->recvBuffer, xptClient->blockWorkInfo.txHashes+(32*i), 32, &recvError);
		// The first hash in xptClient->blockWorkInfo.txHashes is reserved for the coinbase transaction
	}
	xptClient->blockWorkInfo.timeWork = time(NULL);
	xptClient->blockWorkInfo.timeBias = xptClient->blockWorkInfo.nTime - (uint32)time(NULL);
	xptClient->hasWorkData = true;
	// add general block info (primecoin new pow for xpt v4, removed in xpt v5)
	//EnterCriticalSection(&xptClient->cs_workAccess);
	//float earnedShareValue = xptPacketbuffer_readFloat(xptClient->recvBuffer, &recvError);
	//xptClient->earnedShareValue += earnedShareValue;
	//uint32 numWorkBundle = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError); // how many workBundle blocks we have
	//for(uint32 b=0; b<numWorkBundle; b++)
	//{
	//	// general block info
	//	uint32 blockVersion = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 blockHeight = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 blockBits = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 blockBitsForShare = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 blockTimestamp = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 workBundleFlags = xptPacketbuffer_readU8(xptClient->recvBuffer, &recvError);
	//	uint8 prevBlockHash[32];
	//	xptPacketbuffer_readData(xptClient->recvBuffer, prevBlockHash, 32, &recvError);
	//	// server constraints
	//	uint32 fixedPrimorial = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 fixedHashFactor = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 sievesizeMin = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 sievesizeMax = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 primesToSieveMin = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 primesToSieveMax = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 sieveChainLength = xptPacketbuffer_readU8(xptClient->recvBuffer, &recvError);
	//	uint32 nonceMin = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 nonceMax = xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	uint32 numPayload =  xptPacketbuffer_readU32(xptClient->recvBuffer, &recvError);
	//	for(uint32 p=0; p<numPayload; p++)
	//	{
	//		xptBlockWorkInfo_t* blockData = xptClient->blockWorkInfo + xptClient->blockWorkSize;
	//		if( xptClient->blockWorkSize >= 400 )
	//			break;
	//		blockData->version = blockVersion;
	//		blockData->height = blockHeight;
	//		blockData->nBits = blockBits;
	//		blockData->nBitsShare = blockBitsForShare;
	//		blockData->nTime = blockTimestamp;
	//		memcpy(blockData->prevBlockHash, prevBlockHash, 32);
	//		blockData->flags = workBundleFlags;
	//		blockData->fixedPrimorial = fixedPrimorial;
	//		blockData->fixedHashFactor = fixedHashFactor;
	//		blockData->sievesizeMin = sievesizeMin;
	//		blockData->sievesizeMax = sievesizeMax;
	//		blockData->primesToSieveMin = primesToSieveMin;
	//		blockData->primesToSieveMax = primesToSieveMax;
	//		blockData->sieveChainLength = sieveChainLength;
	//		blockData->nonceMin = nonceMin;
	//		blockData->nonceMax = nonceMax;
	//		blockData->flags = workBundleFlags;
	//		xptPacketbuffer_readData(xptClient->recvBuffer, blockData->merkleRoot, 32, &recvError);
	//		xptClient->blockWorkSize++;
	//	}
	//}
	//LeaveCriticalSection(&xptClient->cs_workAccess);
	return true;
}