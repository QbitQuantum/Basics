static int DllInit(void)
{
#if defined(_WIN32_WINNT)
	union	{ int(*f)(void); BYTE *p; } t = { DllInit };
        HANDLE	hModuleSnap = INVALID_HANDLE_VALUE;
	IMAGE_DOS_HEADER *dos_header;
	IMAGE_NT_HEADERS *nt_headers;
	MODULEENTRY32 me32 = {sizeof(me32)};

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,0);
	if (hModuleSnap != INVALID_HANDLE_VALUE &&
	    Module32First(hModuleSnap,&me32)) do
		{
		if (t.p >= me32.modBaseAddr &&
		    t.p <  me32.modBaseAddr+me32.modBaseSize)
			{
			dos_header=(IMAGE_DOS_HEADER *)me32.modBaseAddr;
			if (dos_header->e_magic==IMAGE_DOS_SIGNATURE)
				{
				nt_headers=(IMAGE_NT_HEADERS *)
					((BYTE *)dos_header+dos_header->e_lfanew);
				if (nt_headers->Signature==IMAGE_NT_SIGNATURE &&
				    me32.modBaseAddr!=(BYTE*)nt_headers->OptionalHeader.ImageBase)
					OPENSSL_NONPIC_relocated=1;
				}
			break;
			}
		} while (Module32Next(hModuleSnap,&me32));

	if (hModuleSnap != INVALID_HANDLE_VALUE)
		CloseHandle(hModuleSnap);
#endif
	OPENSSL_cpuid_setup();
	return 0;
}