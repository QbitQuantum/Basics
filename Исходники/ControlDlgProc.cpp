///<summary>Checks whether the given file is a valid image file.</summary>
///<param name="szFile">The path to the file to check.</param>
///<returns>Whether the file is valid.</summary>
BOOL IsValidImageFile(LPTSTR szFile) {
	TCHAR szFileExt[8] = { 0 };   // The file extension of the actual file
	DWORD dwExtSize;              // Size of the file extension
	TCHAR szFilterExt[8] = { 0 }; // The current filter extension being compared
	BOOL  bIsValidExt = FALSE;

	TCHAR* curChar;
	TCHAR period = TEXT('.');
	TCHAR* lastPeriod = NULL;
	for (curChar = szFile; *curChar != 0; curChar++) {
		if (*curChar == period) lastPeriod = curChar;
	}

	// No file extension? Definitely not valid then
	if (lastPeriod == NULL) return FALSE;

	// Extension size of 0 or greater than 7? Never heard of that format...
	dwExtSize = (DWORD)(curChar - lastPeriod - 1);
	if (!dwExtSize || dwExtSize > 7) {
		return FALSE;
	}

	// Save the extension and convert it to uppercase for comparison with our filter
	_tcsnccpy_s(szFileExt, lastPeriod + 1, dwExtSize + 1); // + 1 will copy the null terminator too
	for (curChar = szFileExt; *curChar != 0; curChar++) {
		*curChar = _totupper(*curChar);
	}
	
	// Yep, I'm re-using variables
	// Skip the description part of our filter to get to the actual extensions
	for (curChar = szFilter; *curChar != 0; curChar++);
	curChar += 3; // Skip to first character of the first extension
	lastPeriod = curChar - 1;

	// Compare each valid file extension against the one for our image
	for (; *curChar != 0; curChar++) {
		if (*curChar == TEXT(';')) {
			dwExtSize = (DWORD)(curChar - lastPeriod - 1);
			_tcsnccpy_s(szFilterExt, lastPeriod + 1, dwExtSize);
			szFilterExt[dwExtSize + 1] = 0;
			
			if (_tccmp(szFileExt, szFilterExt) == 0) {
				bIsValidExt = TRUE;
				break;
			}

			curChar += 3; // Skip the "*." after the semicolon in the list
			lastPeriod = curChar - 1;
		}
	}

	// Final comparison if there's no trailing semicolon
	if (*(curChar - 1) != TEXT(';') && !bIsValidExt) {
		dwExtSize = (DWORD)(curChar - lastPeriod - 1);
		_tcsnccpy_s(szFilterExt, lastPeriod + 1, dwExtSize);
		szFilterExt[dwExtSize + 1] = 0;
		if (_tccmp(szFileExt, szFilterExt) == 0) {
			bIsValidExt = TRUE;
		}
	}

	if (!bIsValidExt) return FALSE;

	// Finally, check if the file actually exists
	DWORD dwAttrib = GetFileAttributes(szFile);
	return dwAttrib != INVALID_FILE_ATTRIBUTES;
}