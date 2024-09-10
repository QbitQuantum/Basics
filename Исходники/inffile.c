BOOLEAN
INF_GetDataField(
	IN PINFCONTEXT Context,
	IN ULONG FieldIndex,
	OUT PWCHAR *Data)
{
#ifdef __REACTOS__
	return InfGetDataField(Context, FieldIndex, Data);
#else
	static PWCHAR pLastCallsData[] = { NULL, NULL, NULL };
	static DWORD NextIndex = 0;
	DWORD dwSize;
	BOOL ret;

	*Data = NULL;

	ret = SetupGetStringFieldW(
		Context,
		FieldIndex,
		NULL,
		0,
		&dwSize);
	if (!ret)
		return FALSE;
	HeapFree(GetProcessHeap(), 0, pLastCallsData[NextIndex]);
	pLastCallsData[NextIndex] = HeapAlloc(GetProcessHeap(), 0, dwSize * sizeof(WCHAR));
	ret = SetupGetStringFieldW(
		Context,
		FieldIndex,
		pLastCallsData[NextIndex],
		dwSize,
		NULL);
	if (!ret)
		return FALSE;

	*Data = pLastCallsData[NextIndex];
	NextIndex = (NextIndex + 1) % (sizeof(pLastCallsData) / sizeof(pLastCallsData[0]));
	return TRUE;
#endif /* !__REACTOS__ */
}