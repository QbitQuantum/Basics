// すべてのモジュールに対してAPIフックを行う関数
void CAPIHook::ReplaceIATEntryInAllMods(
										PCSTR pszModuleName, 
										PROC pfnCurrent, 
										PROC pfnNew)
{
	// 自分自身（API_Hook_Lib.dll）のモジュールハンドルを取得
	MEMORY_BASIC_INFORMATION mbi;
	if(VirtualQuery(ReplaceIATEntryInAllMods, &mbi, sizeof(mbi)) == 0)
		return;
	HMODULE hModThisMod = (HMODULE) mbi.AllocationBase;

	// モジュールリストを取得
	HANDLE hModuleSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE, GetCurrentProcessId());
	if(hModuleSnap == INVALID_HANDLE_VALUE)
		return;

	MODULEENTRY32 me;
	me.dwSize = sizeof(me);
	BOOL bModuleResult = Module32First(hModuleSnap, &me);
	// それぞれのモジュールに対してReplaceIATEntryInOneModを実行
	// ただし自分自身（API_Hook_Lib.dll）には行わない
	while(bModuleResult) {
		if(me.hModule != hModThisMod)
			ReplaceIATEntryInOneMod(pszModuleName, pfnCurrent, pfnNew, me.hModule);
		bModuleResult = Module32Next(hModuleSnap, &me);
	}
	CloseHandle(hModuleSnap);
}