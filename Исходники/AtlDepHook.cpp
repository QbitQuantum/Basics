	BOOL FixThunk(LONG dwLong)
	{
		_WndProcThunk* pThunk = (_WndProcThunk*)dwLong;

		MEMORY_BASIC_INFORMATION mbi;
		DWORD dwOldProtect;

		if (IsBadReadPtr(pThunk, sizeof(_WndProcThunk)) || !CheckThunk(pThunk))
		{
			return TRUE;
		}

		if (VirtualQuery((LPCVOID)pThunk, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == 0)
		{
			return FALSE;
		}
		// The memory is already PAGE_EXECUTE_READWRITE, so don't need fixing
		if (mbi.AllocationProtect == PAGE_EXECUTE_READWRITE)
		{
			return TRUE;
		}

		return VirtualProtect((LPVOID)pThunk, sizeof(_WndProcThunk), PAGE_EXECUTE_READWRITE, &dwOldProtect);
	}