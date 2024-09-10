void hook(char *addressFrom, char *addressTo, unsigned long *saveAddress)
{
	DWORD oldProtect = 0;
	x86_insn_t insn;
    memset (&insn, 0, sizeof (insn));
	int totalSize = 0;

	totalSize += x86_disasm ((unsigned char *)addressFrom, INTEL_MAXINSTRLEN, 0, 0, &insn);
	while(totalSize < FUNCTION_PATCHLEN)
	{
		int newTotalSize = x86_disasm ((unsigned char *)(addressFrom + totalSize), INTEL_MAXINSTRLEN, 0, 0, &insn);
		totalSize += newTotalSize;
	}
	
	char *mbuf = (char *)VirtualAlloc(NULL,1024,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE);

	// memset(mbuf,0,1024);
	// sprintf(mbuf,"* starting hook...\n");
	// OutputDebugString(mbuf);

	// memset(mbuf,0,1024);
	// sprintf(mbuf,"* total size of function prelude is %d\n",totalSize);
	// OutputDebugString(mbuf);

	char *codeCave = (char *)VirtualAlloc(NULL,totalSize + FUNCTION_TAILLEN,MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	DWORD unused;
	VirtualProtect(codeCave,totalSize + FUNCTION_TAILLEN,PAGE_READWRITE,&oldProtect);

	// memset(mbuf,0,1024);
	// sprintf(mbuf,"* code cave lives at %08x\n",(unsigned long )codeCave);
	// OutputDebugString(mbuf);

	// memset(mbuf,0,1024);
	// sprintf(mbuf,"* addressfrom at %08x\n",(unsigned long )addressFrom);
	// OutputDebugString(mbuf);

	// memset(mbuf,0,1024);
	// sprintf(mbuf,"* trying to write code cave...\n");
	// OutputDebugString(mbuf);

	VirtualProtect(codeCave,totalSize + FUNCTION_TAILLEN,PAGE_READWRITE,&unused);
	memset(codeCave,'\xCC',totalSize);
	memcpy(codeCave,addressFrom,totalSize);
	codeCave[totalSize] = '\xE9';
	DWORD *cp = (DWORD *)((unsigned long )codeCave + totalSize + 1);
	cp[0] = (unsigned long )(addressFrom + totalSize - ((unsigned long )codeCave + totalSize + 5));
	saveAddress[0] = (unsigned long )codeCave;
	VirtualProtect(codeCave,totalSize + FUNCTION_TAILLEN,PAGE_EXECUTE_READ,&unused);

	// memset(mbuf,0,1024);
	// sprintf(mbuf,"* trying to rewrite function entry...\n");
	// OutputDebugString(mbuf);

	VirtualProtect(addressFrom,7,PAGE_READWRITE,&oldProtect);
	memset(addressFrom,'\xCC',totalSize);

	addressFrom[0] = '\xE9';
	DWORD *p =  (DWORD *)((unsigned long ) addressFrom + 1 );
	p[0] = (DWORD )(addressTo - ((unsigned long ) addressFrom   + 5));
	VirtualProtect(addressFrom,7,oldProtect,&unused);

	// memset(mbuf,0,1024);
	// sprintf(mbuf,"* all done\n");
	// OutputDebugString(mbuf);

	/*

	  hook structure:
	  hookFrom: E9 addressTo
	  addressTo: our function
	  codeCave is the new function	  

	*/

	memset(mbuf,0,1024);
	wsprintf(mbuf,"* [%08x] %02x %02x%02x%02x%02x (%08x)\n",(unsigned long )addressFrom,
													(unsigned char )addressFrom[0],
													(unsigned char )addressFrom[1],
													(unsigned char )addressFrom[2],
													(unsigned char )addressFrom[3],
													(unsigned char )addressFrom[4],
													(unsigned long )addressTo);
	OutputDebugString(mbuf);

	VirtualFree(mbuf,0,MEM_RELEASE);

	return;
}