///////////////////////////////////////////////////////////////////////////////
// load lua code
///////////////////////////////////////////////////////////////////////////////
bool widePathToShortAsciiPath(const wchar_t* wPath, char* cPath)
{
	wchar_t transformString[MAX_PATH];
	ZeroMemory(transformString, MAX_PATH * sizeof(wchar_t));
	ZeroMemory(cPath, MAX_PATH);

	do
	{
		if (GetShortPathNameW(wPath, NULL, 0) == 0) break;
		if (GetShortPathNameW(wPath, transformString, MAX_PATH) == 0) break;
		for (int i = 0; i < MAX_PATH; i++)
			cPath[i] = ((char*)&transformString[0])[i*2];
		return true;
	} while (0);

	return false;
}