bool ConvertToNtPath(const wchar_t* path, wchar_t* normalized, size_t normalizedLen)
{
	UNICODE_STRING ntPath;
	DWORD size;
	bool result = false;

	size = GetFullPathNameW(path, (DWORD)normalizedLen, normalized, NULL);
	if (size == 0)
		return false;

	memset(&ntPath, 0, sizeof(ntPath));

	if (RtlDosPathNameToRelativeNtPathName_U(normalized, &ntPath, NULL, NULL) == FALSE)
		return false;

	if (normalizedLen * sizeof(wchar_t) > ntPath.Length)
	{
		memcpy(normalized, ntPath.Buffer, ntPath.Length);
		normalized[ntPath.Length / sizeof(wchar_t)] = L'\0';
		result = true;
	}

	HeapFree(GetProcessHeap(), 0, ntPath.Buffer);

	return result;
}