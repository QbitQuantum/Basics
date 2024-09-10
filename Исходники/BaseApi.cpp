BOOL WINAPI EnumThread(ThreadVisitor& visitor)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	THREADENTRY32 te = { sizeof(THREADENTRY32), 0 };

	if (hSnap == INVALID_HANDLE_VALUE)
		return FALSE;

	if (!Thread32First(hSnap, &te))
	{
		CloseHandle(hSnap);
		return FALSE;
	}

	do
	{
		try
		{
			if (!visitor.visit(te))
				break;
		}
		catch (...)
		{
			CloseHandle(hSnap);
			return FALSE;
		}
	} while (Thread32Next(hSnap, &te));

	CloseHandle(hSnap);

	return TRUE;
}