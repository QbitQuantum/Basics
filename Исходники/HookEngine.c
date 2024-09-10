VOID WPON()
{
#ifndef _WIN64		
	
	_asm
	{
		mov eax,cr0
		or eax,10000h
		mov cr0,eax
		sti					
	}; 
#else	 
	UINT64 cr0=__readcr0();
	cr0 &= 0xfffffffffffeffff;
	__writecr0(cr0);
	_disable(); 

#endif //_WIN64  
}