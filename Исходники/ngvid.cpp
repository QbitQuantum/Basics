VOID 
REINITIALIZE_ADAPTER( 
	PVOID 
	)

/*++

Routine Description

	This routine re-initializes display driver
	 to obtains its DrvCoptBits pointer.
	This routine executed as a separate thread in the context of CSRSS.EXE

Arguments

	PVOID

		Thread context, always NULL

Return Value

	None, thread terminates by call PsTerminateSystemThread

Environment

	Separate thread of CSRSS process

--*/

{
	//
	// This routine runs in the context of csrss.exe
	//
	
	KdPrint(("REINITIALIZE_ADAPTER enter\n"));

	HANDLE hDrv = EngLoadImage (L"vid_copy.dll");
	KdPrint(("vid_copy is %X\n", hDrv));
	if (hDrv)
	{
		BOOLEAN (NTAPI *pOriginalDrvEnableDriver)(
			ULONG iEngineVersion,
			ULONG cj,
			PDRVENABLEDATA pded
			);

		*(PVOID*)&pOriginalDrvEnableDriver = EngFindImageProcAddress (hDrv, "DrvEnableDriver");

		KdPrint(("pOriginalDrvEnableDriver = %X\n", pOriginalDrvEnableDriver));

		if (pOriginalDrvEnableDriver)
		{
			BOOLEAN Ret;
			DRVENABLEDATA DrvEnableData = {0};
		
			Ret = pOriginalDrvEnableDriver (DDI_DRIVER_VERSION_NT5_01_SP1,
				sizeof(DrvEnableData),
				&DrvEnableData);

			KdPrint(("pOriginalDrvEnableDriver returned %X\n", Ret));

			if (Ret)
			{
				for (ULONG i = 0; i<DrvEnableData.c; i++)
				{
					if (DrvEnableData.pdrvfn[i].iFunc == INDEX_DrvCopyBits)
					{
						KdPrint(("Found DrvCopyBits: %X\n", DrvEnableData.pdrvfn[i].pfn));

						HANDLE hKey;
						wchar_t value[512];

						hKey = RegOpenKey (L"\\Registry\\Machine\\Software\\NGdbg", KEY_QUERY_VALUE);
						if (hKey)
						{
							ULONG Len = sizeof(value);

							if (RegQueryValue (hKey, L"DisplayDriver", REG_SZ, value, &Len))
							{
								KdPrint(("Display driver: %S\n", value));

								wcscat (value, L".dll");

								PVOID OrigBase = FindImage (value);
								PVOID VidBase = FindImage (L"vid_copy.dll");

								if (OrigBase && VidBase)
								{
									ULONG Offset = (ULONG)DrvEnableData.pdrvfn[i].pfn - (ULONG)VidBase;

									KdPrint(("Offset %X\n", Offset));

									pDrvCopyBits = (PUCHAR)OrigBase + Offset;

									KdPrint(("DrvCopyBits %X\n", pDrvCopyBits));
								}
								else
								{
									KdPrint(("FindImage failed: OrigBase %X, VidBase %X\n", OrigBase, VidBase));
								}
							}
							else
							{
								KdPrint(("RegQueryValue failed\n"));
							}

							ZwClose (hKey);
						}
						else
						{
							KdPrint(("RegOpenKey failed\n"));
						}
					}
				}
			}
		}

		EngUnloadImage (hDrv);
	}

	KdPrint(("REINITIALIZE_ADAPTER exit\n"));

	PsTerminateSystemThread (0);
}