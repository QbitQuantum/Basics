void BWMem::WriteBytes(HANDLE hProcess, char *adr, const char *buffer, int size)
{
	DWORD written=0;
	if(!WriteProcessMemory(hProcess,adr,(void*)buffer,size,&written))
		written=0;
}