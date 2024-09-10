void CTextService::_DelUserDic(WCHAR command, const std::wstring &key, const std::wstring &candidate)
{
	DWORD bytesWrite, bytesRead;

	_ConnectDic();

	ZeroMemory(pipebuf, sizeof(pipebuf));

	_snwprintf_s(pipebuf, _TRUNCATE, L"%c\n%s\t%s\n",
		command, key.c_str(), candidate.c_str());

	bytesWrite = (DWORD)((wcslen(pipebuf) + 1) * sizeof(WCHAR));
	if(WriteFile(hPipe, pipebuf, bytesWrite, &bytesWrite, nullptr) == FALSE)
	{
		goto exit;
	}

	ZeroMemory(pipebuf, sizeof(pipebuf));

	bytesRead = 0;
	if(ReadFile(hPipe, pipebuf, sizeof(pipebuf), &bytesRead, nullptr) == FALSE)
	{
		goto exit;
	}

exit:
	ZeroMemory(pipebuf, sizeof(pipebuf));

	_DisconnectDic();
}