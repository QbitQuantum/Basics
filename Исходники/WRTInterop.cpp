	EXTERN_C HRESULT WINAPI CreateString(PCWSTR Str, HSTRING*pHS)
	{
		return WindowsCreateString(Str, lstrlenW(Str), pHS);
	}