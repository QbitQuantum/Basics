// すべてのモジュールに対してAPIフックを行う関数
bool ReplaceIATEntryInAllMods(
                              PCSTR pszModuleName,
                              PROC pfnCurrent,
                              PROC pfnNew,
                              HMODULE hmodCaller) 
{
	if( hmodCaller ) {
		return ReplaceIATEntryInOneMod(pszModuleName, pfnCurrent, pfnNew, hmodCaller);
	} else {
		bool bResult = false;
		// モジュールリストを取得
		HANDLE hModuleSnap = CreateToolhelp32Snapshot(
								TH32CS_SNAPMODULE, GetCurrentProcessId());
		if(hModuleSnap == INVALID_HANDLE_VALUE) {
			return bResult;
		}

		MODULEENTRY32 me;
		me.dwSize = sizeof(me);
		BOOL bModuleResult = Module32First(hModuleSnap, &me);
		// それぞれのモジュールに対してReplaceIATEntryInOneModを実行
		while(bModuleResult) {
//			OutputDebugString(">>");
//			OutputDebugString(me.szModule);
//			OutputDebugString("\n");
			if( ReplaceIATEntryInOneMod(pszModuleName, pfnCurrent, pfnNew, me.hModule) ) {
				bResult = true;
			}
			bModuleResult = Module32Next(hModuleSnap, &me);
		}
		CloseHandle(hModuleSnap);
		return bResult;
	}
}