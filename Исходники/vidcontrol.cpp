void GetDrvCopyBits()
{
	void* ptr = SysLoad ("igxprd32.dll");

	BOOL (APIENTRY *DrvEnableDriver)(
		ULONG          iEngineVersion,
		ULONG          cj,
		DRVENABLEDATA *pded
		);
	
	*(PVOID*)&DrvEnableDriver = LdrPrepareCallLoadedImage( (HINSTANCE)ptr );

	DRVENABLEDATA ded = {0};
	BOOL b = DrvEnableDriver (0x00030101, sizeof(ded), &ded);


	printf("DrvEnableDriver returned %d\n", b);

	if (!b)
		Sleep(-1);

	printf("DISPLAY DRIVER LOADED\n");
	printf("===============================================================\n"
		   "Dumping entries                   \n"
		   "Index		Entry		Relative	Module    \n"
		   "===============================================================\n");

	for (ULONG i=0; i<ded.c; i++)
	{
		char *modname = "";

		PMODULE32 mod = LdrLookupModByPointer (ded.pdrvfn[i].pfn);
		if (mod)
		{
			modname = strrchr (mod->ModuleName, '\\');
			if (modname)
				modname ++;
			else
				modname = "";
		}

		printf("%2d		%08x	%08x	%s\n", 
			ded.pdrvfn[i].iFunc, 
			ded.pdrvfn[i].pfn,
			mod ? ((ULONG)ded.pdrvfn[i].pfn - (ULONG)mod->ImageBase) : 0,
			modname);

		if (ded.pdrvfn[i].iFunc == INDEX_DrvCopyBits)
		{
			DrvCopyBits_RVA = ((ULONG)ded.pdrvfn[i].pfn - (ULONG)mod->ImageBase);

			PVOID KernelModule = GetModule (modname);
			if (KernelModule)
			{
				DrvCopyBits = (ULONG)KernelModule + DrvCopyBits_RVA;
				pTblDrvCopyBits = (PULONG)((ULONG)KernelModule - (ULONG)mod->ImageBase + (ULONG)&ded.pdrvfn[i].pfn);
				printf("DrvCopyBits %X pp %X\n", DrvCopyBits, pTblDrvCopyBits);
				return;
			}
		}
	}
}