HANDLE __stdcall DllInjectionW(PROCESS_INFORMATION *pi,	//プロセスの情報
								   const wchar_t *szDllName)//Dllファイル名
{

	HANDLE hProcess = pi->hProcess;

	//dllファイルの絶対パスを保存する変数
	TCHAR szLibFile[MAX_PATH];
	//dllファイルの絶対パスの文字列の長さ + 1(\0までの長さを保存する)
	int szLibFileLen;

	//もし相対パスなら、
	//自身の絶対パスの取得をして、dllまでの絶対パスを作る。
	//(例 X:/-----/--.... というパスは、1バイト目が':'なので、絶対パスとなる。)
	//絶対パスなら、そのままコピーするだけ。
	if(szDllName[1] != ':'){
		GetModuleFileName(NULL, szLibFile, sizeof(szLibFile));
		lstrcpy(_tcsrchr(szLibFile, _TEXT('\\')) + 1, szDllName);
	} else {
		lstrcpyW(szLibFile,szDllName);
	}
	//長さ(使うメモリ領域)の計算
	szLibFileLen = lstrlen(szLibFile) + 1;
	szLibFileLen = szLibFileLen * sizeof(TCHAR);

	//プロセス内にメモリ領域の確保
	LPSTR RemoteProcessMemory;
	RemoteProcessMemory = (LPSTR)VirtualAllocEx( hProcess, NULL, szLibFileLen, MEM_COMMIT, PAGE_READWRITE);
	if(RemoteProcessMemory == NULL){
		//setErrorString("プロセス内にメモリが確保できませんでした。");
		return NULL;  
	}
	//書き込み
	if(WriteProcessMemory(hProcess, RemoteProcessMemory, (PVOID)szLibFile, szLibFileLen, NULL) == 0){
		//setErrorString("プロセスに書き込みができませんでした。");
		return NULL;
	} 
	//LoadLibraryW関数が始まるポインタの取得
	PTHREAD_START_ROUTINE pfnThreadRtn; 
	pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress( GetModuleHandle(_TEXT("Kernel32")), "LoadLibraryW");
	if (pfnThreadRtn == NULL){
		//setErrorString("LoadLibraryが見つかりませんでした。(何故？)");
		return NULL;  
	} 
	//スレッド作成
	HANDLE hThread;
	hThread = CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, RemoteProcessMemory,CREATE_SUSPENDED, NULL);
	if (hThread == NULL){
		//setErrorString("スレッドが作れませんでした。");
		return NULL;
	}

	//スレッド実行
	ResumeThread(hThread);
	BYTE *modulePointer = (BYTE *)WaitForSingleObject(hThread,INFINITE);
	DWORD dwExitCode;	//終了コード
	GetExitCodeThread(hThread,&dwExitCode);
	CloseHandle(hThread);	//スレッドを閉じる
	
	//プロセス内に確保したメモリの開放
	VirtualFreeEx(hProcess,RemoteProcessMemory,260,MEM_DECOMMIT);

	if(dwExitCode == NULL){
		char a_szLibName[MAX_PATH];
		BOOL bDummy;
		WideCharToMultiByte(CP_ACP,0,szLibFile,-1,a_szLibName,MAX_PATH,"<不明なライブラリ>",&bDummy);
		//setErrorStringEx("%s ---- DLLがロードできませんでした。",a_szLibName);
		return NULL;
	}

	return (HANDLE)dwExitCode;
}