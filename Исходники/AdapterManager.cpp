/******************
 * get the destination address of a gateway using ARP API.
 * Note that there are cases that this won't work , so 
 * there will probably have to be a usage of a function that
 * listens to the network connection and monitors the gateway IP and dest MAC.
 *
 */
bool __cdecl AdapterManager::getDestMAC(char *gatewayAddress ,unsigned int *destMAC )
{
	DWORD status;
	IPAddr destIP = inet_addr(gatewayAddress);
	ULONG   ulLen=6;
	void* voidPtr = (void*)&ulLen;
	PULONG ulongPtr = (PULONG)(voidPtr);
	void* voidPtr2 = (void*)destMAC;
	PULONG ulongPtr2 = (PULONG)(voidPtr2);
	status = SendARP(destIP , 0 , ulongPtr2 , ulongPtr);
	if (status!=NO_ERROR)
		return false;
	return true;
}