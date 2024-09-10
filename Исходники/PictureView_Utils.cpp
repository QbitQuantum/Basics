// Плагин может быть вызван в первый раз из фоновой нити (диалог поиска при поиске в архивах)
// Поэтому простой "gnMainThreadId = GetCurrentThreadId();" не прокатит. Нужно искать первую нить процесса!
DWORD GetMainThreadId()
{
	DWORD nThreadID = 0;
	DWORD nProcID = GetCurrentProcessId();
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (h != INVALID_HANDLE_VALUE)
	{
		THREADENTRY32 ti = {sizeof(THREADENTRY32)};
		if (Thread32First(h, &ti))
		{
			do {
				// Нужно найти ПЕРВУЮ нить процесса
				if (ti.th32OwnerProcessID == nProcID) {
					nThreadID = ti.th32ThreadID;
					break;
				}
			} while (Thread32Next(h, &ti));
		}
		CloseHandle(h);
	}

	// Нехорошо. Должна быть найдена. Вернем хоть что-то (текущую нить)
	if (!nThreadID) {
		_ASSERTE(nThreadID!=0);
		nThreadID = GetCurrentThreadId();
	}
	return nThreadID;
}