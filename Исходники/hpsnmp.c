BOOL SnmpProcessAttach()
{
	HPSNMPInitCriticalSection();
	dwTLSIndex = TlsAlloc();
	return(AllocThreadStorage());
}