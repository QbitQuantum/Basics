wchar_t* charToWChar(const char* text)
{
	size_t newsize = strlen(text) + 1;
	wchar_t * wcstring = new wchar_t[newsize];

	// Convert char* string to a wchar_t* string.
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, text, _TRUNCATE);
	return wcstring;
}