//先从PEB中获取待隐藏的DLL的基址
ULONG GetDllBaseFromProcessPEB(PEPROCESS Process,char *szDllName)
{
	ULONG Peb;
	PPEB_LDR_DATA pLdrData;
	PLDR_DATA_TABLE_ENTRY pLdrDataEntry;
	PLIST_ENTRY pListHead,pListNext;
	ANSI_STRING ansiDllName;
	ULONG DllBase=0;
	Peb=*(ULONG*)((char*)Process+EPROCESS_PEB_OFFSET);
	dprintf("PEB=0x%08X\n",Peb);
	__try
	{
		pLdrData=(PPEB_LDR_DATA)*(ULONG*)((char*)Peb+0xC);
		pListHead=&(pLdrData->InLoadOrderModuleList);
		pListNext=pListHead->Flink;
		for (pListHead;pListNext!=pListHead;pListNext=pListNext->Flink)
		{
			pLdrDataEntry=(PLDR_DATA_TABLE_ENTRY)pListNext;
			if (pLdrDataEntry->BaseDllName.Buffer)
			{
				RtlUnicodeStringToAnsiString(&ansiDllName,& (pLdrDataEntry->BaseDllName),TRUE);
				//dprintf("Base=0x%08X %s\n",pLdrDataEntry->DllBase,ansiDllName.Buffer);
				if (!_stricmp(szDllName,ansiDllName.Buffer))
				{
					DllBase=(ULONG)pLdrDataEntry->DllBase;
				}
				RtlFreeAnsiString(&ansiDllName);
				//若找到就退出循环
				if (DllBase) break;
			}//end of if
			
		}
		return DllBase;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		DbgPrint("Error occured while searching module in PEB.\n");
		return 0;
	}
}