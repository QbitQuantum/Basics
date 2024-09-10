uLong PackerJob::getFileTime(wchar_t *file, tm_zip*, uLong *dt)
{
	FILETIME ftLocal;
	HANDLE hFind;
	WIN32_FIND_DATA ff32;

	hFind = FindFirstFile(file, &ff32);
	if (hFind != INVALID_HANDLE_VALUE) {
		FileTimeToLocalFileTime(&(ff32.ftLastWriteTime), &ftLocal);
		FileTimeToDosDateTime(&ftLocal, ((LPWORD)dt) + 1, ((LPWORD)dt) + 0);
		FindClose(hFind);
		return 1;
	}

	return 0;
}