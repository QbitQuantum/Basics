void
InitializeForClients()
{
	InitializeSRWLock(&srwClientsLock);

	clientsHeader.next = NULL;
}