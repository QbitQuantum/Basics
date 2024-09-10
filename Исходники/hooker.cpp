BOOL HookD3DFunction(DWORD dwRVA, PVOID pvStub)
{
	HMODULE hD3D9;
	PBYTE pbFuncAddress;
	DWORD dwOldProtect;
	BOOL bRet = FALSE;

	hD3D9 = GetModuleHandle("d3d9.dll");
	if(hD3D9)
	{
		pbFuncAddress = (PBYTE)UlongToPtr(PtrToUlong(hD3D9) + dwRVA);
		if(VirtualProtect(pbFuncAddress, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		{
			if(memcmp(pbFuncAddress, "\x8B\xFF\x55\x8B\xEC", 5) == 0)
			{
				*pbFuncAddress = 0xE8;
				*((PDWORD)&pbFuncAddress[1]) = PtrToUlong(pvStub) - (PtrToUlong(pbFuncAddress) + 5);
				bRet = TRUE;
			}
			VirtualProtect(pbFuncAddress, 5, dwOldProtect, &dwOldProtect);
		}
	}
	return bRet;
}