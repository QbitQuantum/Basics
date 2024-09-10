CString GetInputLine (const CString &sPrompt)
	{
	char szBuffer[1024];
	printf((LPSTR)sPrompt);
	gets_s(szBuffer, sizeof(szBuffer)-1);
	return CString(szBuffer);
	}