void CFilteringTable::RemoveSpace(LPCTSTR textInput, LPTSTR textOutput, size_t size) const
{
	TCHAR buffer[MAX_PATH] = {0};	

	for(PUCHAR inputPointer = PUCHAR(textInput);
		0 < *inputPointer;
		inputPointer = _mbsinc((const PUCHAR)inputPointer))
	{
		LPCTSTR removedSpeicalCharacter = _T("\t\n\r ~`!@#$%^&*()-_=+\\|<,>.?/");

		if(_tcschr(removedSpeicalCharacter, *inputPointer))
		{
			continue;
		}

		_tcsncat(
			buffer,
			LPCTSTR(inputPointer),
			IsDBCSLeadByte(*inputPointer) ? 2 : 1);
	}

	SafeStrCpy(
		textOutput,
		buffer,
		size);
}