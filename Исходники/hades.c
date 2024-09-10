//-----------------------------------------------------------------------------
// hooked_ZwLoadDriver - Debugger/Data Code Mining protocol
//-----------------------------------------------------------------------------
NTSTATUS hooked_ZwLoadDriver(PUNICODE_STRING name)
{
	NTSTATUS ret = 0;

	// look for our identifier - our BP was pushed on the stack from shared_mem
	_asm
	{
		push eax
		mov eax, edx        // EDX == ESP 
		mov gORIG_ESP, eax  // Save off the ESP to be restored from the driver.
		                    // however, the alignment is off by 2 DWORDs...
		sub eax, 8          
		mov eax, [eax]
		mov gBP, eax
		pop eax
	}

	debug("\n[ user -> kernel ] hooked_ZwLoadDriver() gateway\n\n");

#if DATA_MINING
	{
		handle_hooked_calls();
		return ret;	
	}
#endif

	// found our breakpoint
#if BREAK_POINT	
	if (gBP == BP1)
	{
		handle_bp();
		return ret;
	}
#endif

	if (name)
	{
		ANSI_STRING strf;
		RtlUnicodeStringToAnsiString(&strf, name, TRUE);
		DbgPrint("\nZwLoadDriver( = ");
		DbgPrint(strf.Buffer);
		DbgPrint(")\n");
	}
	else
		DbgPrint("ZwLoadDriver(NULL)\n");

	ret = ((typeZwLoadDriver)(orig_ZwLoadDriver)) (name);

	DbgPrint("\nZwLoadDriver -> %d \n", ret);

	return ret;
}