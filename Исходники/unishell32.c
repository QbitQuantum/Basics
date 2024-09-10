/* MAKE_EXPORT DragQueryFileW_new=DragQueryFileW */
UINT WINAPI DragQueryFileW_new(HDROP hDrop, UINT iFile, LPWSTR lpszFileW, UINT cch)
{
	UINT ret;
	ALLOC_A(lpszFile, cch * 2);

	ret = DragQueryFileA(hDrop, iFile, lpszFileA, cch);

	if (ret && lpszFileA && iFile != 0xffffffff)
	{
		DWORD lasterr = GetLastError();

		ret = AtoW(lpszFile, cch);
		if (!ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			ret = cch;

		if (ret) ret--;

		SetLastError(lasterr);
	}

	return ret;
}