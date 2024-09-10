void SettingsManagerHelpers::GetAsciiFilename(const wchar_t* wfilename, CCharBuffer buffer)
{
	if (buffer.getSizeInElements() <= 0)
	{
		return;
	}

	if (wfilename[0] == 0)
	{
		buffer[0] = 0;
		return;
	}

	if (Utf16ContainsAsciiOnly(wfilename))
	{
		ConvertUtf16ToUtf8(wfilename, buffer);
		return;
	}

	// The path is non-ASCII unicode, so let's resort to short filenames (they are always ASCII-only, I hope)
	wchar_t shortW[MAX_PATH];
	const int bufferCharCount = sizeof(shortW) / sizeof(shortW[0]);
	const int charCount = GetShortPathNameW(wfilename, shortW, bufferCharCount);
	if (charCount <= 0 || charCount >= bufferCharCount)
	{
		buffer[0] = 0;
		return;
	}

	shortW[charCount] = 0;
	if (!Utf16ContainsAsciiOnly(shortW))
	{
		buffer[0] = 0;
		return;
	}

	ConvertUtf16ToUtf8(shortW, buffer);
}