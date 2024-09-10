int NetManRpcNetIFSendPacket(const void *packet, unsigned int length){
	struct PacketTag *PacketTag;

	WaitSema(NetManTxSemaID);

	NetmanTxWaitingThread=GetThreadId();

	WaitSema(TxBankAccessSema);

	//Check is there is space in the current Tx FIFO. If not, wait for the Tx thread to empty out the other FIFO. */
	while(CurrentTxFIFOData->PacketReqs.NumPackets>=NETMAN_RPC_BLOCK_SIZE){
		SignalSema(TxBankAccessSema);
		WakeupThread(TxThreadID);
		SleepThread();
		WaitSema(TxBankAccessSema);
	}

	memcpy(&CurrentTxFIFOData->FrameBuffer[CurrentTxFIFOData->PacketReqs.TotalLength], packet, length);
	PacketTag=&CurrentTxFIFOData->PacketReqs.tags[CurrentTxFIFOData->PacketReqs.NumPackets];
	PacketTag->offset=CurrentTxFIFOData->PacketReqs.TotalLength;
	PacketTag->length=length;

	CurrentTxFIFOData->PacketReqs.TotalLength+=(length+3)&~3;
	CurrentTxFIFOData->PacketReqs.NumPackets++;

	WakeupThread(TxThreadID);

	SignalSema(TxBankAccessSema);

	NetmanTxWaitingThread=-1;

	SignalSema(NetManTxSemaID);

	return 0;
}