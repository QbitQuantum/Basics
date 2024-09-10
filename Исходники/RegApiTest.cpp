// рекурсивная ф-я
void EnumRegistry(PWCHAR RootKey/* должно быть выделено MAX_REGPATH_LEN WCHARов*/, ULONG Depth)
{
// не будем перегружать стек
	PWCHAR KeyName = (PWCHAR)HeapAlloc(GetProcessHeap(), 0, sizeof(WCHAR)*MAX_KEYVALUENAME_LEN);
	if (!KeyName)
		return;
	PWCHAR ValueName = (PWCHAR)HeapAlloc(GetProcessHeap(), 0, sizeof(WCHAR)*MAX_KEYVALUENAME_LEN);
	if (!ValueName)
	{
		HeapFree(GetProcessHeap(), 0, KeyName);
		return;
	}

// енумерим валушки, начиная с дефолтовой
	PrintTabs(Depth);
	printf("Values:\n");

// дефолтовая не установлена
	if (!PrintValue(RootKey, L"", Depth))
	{
		PrintTabs(Depth);
		printf("(Default):\tvalue not set\n");
	}
	for (ULONG ValueIndex = 0; EnumValues(RootKey, ValueIndex, ValueName); ValueIndex++)
	{
// пропускаем установленное дефолтовое значение
		if (ValueName[0])
			PrintValue(RootKey, ValueName, Depth);
	}

	ULONG OldLen = lstrlenW(RootKey);
	for (ULONG KeyIndex = 0; EnumKeys(RootKey, KeyIndex, KeyName); KeyIndex++)
	{
		lstrcatW(RootKey, L"\\");
		lstrcatW(RootKey, KeyName);

		PrintTabs(Depth);
		printf("%S\n", KeyName);

		EnumRegistry(RootKey, Depth+1);

		RootKey[OldLen] = 0;
	}

	HeapFree(GetProcessHeap(), 0 ,ValueName);
	HeapFree(GetProcessHeap(), 0, KeyName);
}