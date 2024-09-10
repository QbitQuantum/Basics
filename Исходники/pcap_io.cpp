int pcap_io_recv(void* packet, int max_len)
{
	if (PacketCount==0)
		return 0;

	u32 len=*(u32*)&PacketBuffer[ReadCursor];
	if ((u32)max_len<len)
		__debugbreak;
	
	memcpy(packet,(void*)&PacketBuffer[ReadCursor+4],len);

	//Make sure ReadCursor allways has a valid value :)
	//not even sure that much is needed tbh, bored to think :P

	u32 RCpos=ReadCursor;

	RCpos+=len+4;
	if (RCpos>=PacketBufferSize)
		RCpos=0;
	ReadCursor=RCpos;

	//This however, needs to be interlocked
	_InterlockedDecrement(&PacketCount);
	//EnterCriticalSection(&cs);
	//PacketCount--;
	//ExitCriticalSection(&cs);
	return len;
}