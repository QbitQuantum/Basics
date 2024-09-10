/**
 * @brief   遍历虚拟内存
 * 
 * @details 遍历指定进程的整个虚拟内存并对用户显示其属性的工作程序的方法 
 *  
 * @param hProcess 待遍历的进程的进程句柄
 */
void WalkVM(HANDLE hProcess)
{
	// 首先，获得系统信息
	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);

	// 分配要存放信息的缓冲区
	MEMORY_BASIC_INFORMATION mbi;
	ZeroMemory(&mbi, sizeof(mbi));

	// 循环整个应用程序地址空间
	LPCVOID pBlock = (LPVOID)si.lpMinimumApplicationAddress;
	while (pBlock < si.lpMaximumApplicationAddress)
	{
		// 获得下一个虚拟内存块的信息
		if (VirtualQueryEx(
			hProcess,        // 相关的进程
			pBlock,          // 开始位置
			&mbi,            // 缓冲区
			sizeof(mbi)      // 大小的确认
			) == sizeof(mbi))
		{
			// 计算块的结尾及其大小
			LPCVOID pEnd = (PBYTE)pBlock + mbi.RegionSize;
			TCHAR szSize[MAX_PATH];
			StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH);

			// 显示块地址和大小
			_tprintf(TEXT("%08x-%08x"), (DWORD)pBlock, (DWORD)pEnd);
			_tprintf(TEXT(" (%7s) "), szSize);
			switch (mbi.State)
			{
			case MEM_COMMIT:
				_tprintf(TEXT("Committed"));
				break;
			case MEM_FREE:
				_tprintf(TEXT("Free"));
				break;
			case MEM_RESERVE:
				_tprintf(TEXT("Reserved"));
				break;
			}

			// 显示保护
			if (mbi.Protect == 0 && mbi.State != MEM_FREE)
				mbi.Protect = PAGE_READONLY;
			ShowProtection(mbi.Protect);

			// 显示类型
			switch (mbi.Type)
			{
			case MEM_IMAGE:
				_tprintf(TEXT(", Image"));
				break;
			case MEM_MAPPED:
				_tprintf(TEXT(", Mapped"));
				break;
			case MEM_PRIVATE:
				_tprintf(TEXT(", Private"));
				break;
			}

			// 检验可执行的影像
			TCHAR szFilename[MAX_PATH];
			if (GetModuleFileName(
				(HMODULE)pBlock,
				szFilename,
				MAX_PATH
				) > 0)
			{
				// 除去路径并显示
				PathStripPath(szFilename);
				_tprintf(TEXT(", Module: %s"), szFilename);
			}

			_putts(TEXT(""));

			// 移动块指针以获得下一个块
			pBlock = pEnd;
		}
	}
}