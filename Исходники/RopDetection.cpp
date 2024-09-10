VOID
DbgReportRop(
	IN CONST PVOID Address,
	IN CONST DWORD APINumber
	)
{
	PLDR_DATA_TABLE_ENTRY TableEntry;
	LPVOID lpAddress;
	LPVOID lpCodeSectionAddress;
	CHAR szAssciFullModuleName[MAX_MODULE_NAME32];
	CHAR szAssciModuleName[MAX_MODULE_NAME32];
	PCHAR szRopInst;
	DWORD dwCodeSectionSize;
	DWORD i;
	PXMLNODE XmlLogNode;
	PXMLNODE XmlIDLogNode;;

	XmlIDLogNode = CreateXmlElement( XmlShellcode, "row");
    // type
	XmlLogNode = mxmlNewElement( XmlIDLogNode, "type");
	mxmlNewText( XmlLogNode, 0, "0");
    // data
	XmlLogNode = CreateXmlElement( XmlIDLogNode, "function");
	SecureZeroMemory(szAssciFullModuleName, MAX_MODULE_NAME32);
	SecureZeroMemory(szAssciModuleName, MAX_MODULE_NAME32);
	szRopInst = (PCHAR)LocalAlloc(LMEM_ZEROINIT, 2048);
	lpAddress = Address;
	bRopDetected = TRUE;

    /* Get function name which reports rop */
	switch (APINumber)
	{
	case CalleeVirtualAlloc:
		SetTextNode( XmlLogNode, 0, "VirtualAlloc");
		break;
	case CalleeVirtualAllocEx:
		SetTextNode( XmlLogNode, 0, "VirtualAllocEx");
		break;
	case CalleeVirtualProtect:
		SetTextNode( XmlLogNode, 0, "VirtualProtect");
		break;
	case CalleeVirtualProtectEx:
		SetTextNode( XmlLogNode, 0, "VirtualProtectEx");
		break;
	case CalleeMapViewOfFile:
		SetTextNode( XmlLogNode, 0, "MapViewOfFile");
		break;
	case CalleeMapViewOfFileEx:
		SetTextNode( XmlLogNode, 0, "MapViewOfFileEx");
		break;
	case CalleeNtAllocateVirtualMemory:
		SetTextNode(XmlLogNode, 0, "NtAllocateVirtualMemory");
		break;
	case CalleeNtProtectVirtualMemory:
		SetTextNode(XmlLogNode, 0, "NtProtectVirtualMemory");
		break;
	}

    /* Get the module that used for rop gadgets */
	if ( DbgGetRopModule( lpAddress, szAssciFullModuleName, MAX_MODULE_NAME32) == MCEDP_STATUS_SUCCESS )
	{
		XmlLogNode = CreateXmlElement( XmlIDLogNode, "module");
		SetTextNode( XmlLogNode, 0, szAssciFullModuleName);
		SaveXml( XmlLog );
	}

    /* Dump possible ROP gadgets */
	if ( MCEDP_REGCONFIG.ROP.DUMP_ROP == TRUE )
	{
		lpAddress = (PVOID)((DWORD_PTR)lpAddress - MCEDP_REGCONFIG.ROP.ROP_MEM_FAR);
		for ( i = 0 ; i <= MCEDP_REGCONFIG.ROP.MAX_ROP_MEM ; i++ , lpAddress = (LPVOID)((DWORD)lpAddress + 4) )
		{
			if ( LdrFindEntryForAddress((PVOID)(*(DWORD *)lpAddress), &TableEntry) == MCEDP_STATUS_SUCCESS )
			{
				/* get module name */
				wcstombs( szAssciModuleName, TableEntry->FullDllName.Buffer, TableEntry->FullDllName.Length );

				/* Get module .text section start address */
				if ( ( lpCodeSectionAddress = PeGetCodeSectionAddress( TableEntry->DllBase ) ) == NULL )
				{
					DEBUG_PRINTF(LROP, NULL, "[ 0x%p ]\t\t\t\tDB 0x%p [FAILD -- MODULE CODE SECTION ADDRESS NULL]\n", lpAddress, (*(ULONG_PTR *)lpAddress));
					break;
				}

				/* Get module .text section size */
				if ( ( dwCodeSectionSize = PeGetCodeSectionSize( TableEntry->DllBase ) ) == NULL )
				{
					DEBUG_PRINTF(LROP, NULL, "[ 0x%p ]\t\t\t\tDB 0x%p [FAILD - MODULE CODE SECTION SIZE NULL]\n", lpAddress, (*(ULONG_PTR *)lpAddress));
					break;
				}

				/* Check if instruction lies inside the .text section */
				if ( (*(ULONG_PTR *)lpAddress) >= (ULONG_PTR)lpCodeSectionAddress && (*(ULONG_PTR *)lpAddress) < ( (ULONG_PTR)lpCodeSectionAddress + dwCodeSectionSize ) )
				{

					if ( ShuDisassmbleRopInstructions( (PVOID)(*(ULONG_PTR *)lpAddress), szRopInst, MCEDP_REGCONFIG.ROP.MAX_ROP_INST ) == MCEDP_STATUS_SUCCESS )
					{
						DEBUG_PRINTF(LROP, NULL, "[ 0x%p ] %s + 0x%p :\n", (*(ULONG_PTR *)lpAddress), szAssciModuleName, (*(ULONG_PTR *)lpAddress - (ULONG_PTR)TableEntry->DllBase));
						DEBUG_PRINTF(LROP, NULL, "%s", szRopInst);
					} else
					{
						DEBUG_PRINTF(LROP, NULL, "[ 0x%p ]\t\t\t\tDB 0x%p [FAILD TO DISASSMBLE]\n", lpAddress, (*(ULONG_PTR *)lpAddress));
					}

					SecureZeroMemory(szRopInst, 2048);

				} else
					DEBUG_PRINTF(LROP, NULL, "[ 0x%p ]\t\t\t\tDB 0x%p [OUT OF CODE SECTION]\n", lpAddress, (*(ULONG_PTR *)lpAddress));

			} else
				DEBUG_PRINTF(LROP, NULL, "[ 0x%p ]\t\t\t\tDB 0x%p\n", lpAddress, (*(ULONG_PTR *)lpAddress));
		}
	}

	LocalFree(szRopInst);
}