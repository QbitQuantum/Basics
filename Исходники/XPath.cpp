void XPath::FuncCollection(const wchar_t* str)
{
	if(!wcscmp(str, L"last"))
	{
		int copyCmdIdx = cmdIdx;
		wchar_t* tempNum = new wchar_t[MAX_CHAR_SIZE];
		_itow(searchNodeQ.size(),tempNum,10);
		wcsncpy(&cmdBuf[cmdIdx-4],tempNum,wcslen(tempNum));
		/*
		while(cmdBuf[copyCmdIdx + 2 + strlen(tempNum)] != '\0')
		{
			cmdBuf[copyCmdIdx-4 + strlen(tempNum)] = cmdBuf[copyCmdIdx + 2 + strlen(tempNum)];
			copyCmdIdx++;
		}
		cmdBuf[copyCmdIdx-3] = '\0';
		cmdIdx = cmdIdx - 5;*/
		delete[] tempNum;
	}
	else if(!wcscmp(str, L"position"))
	{
		wprintf(L"position");
	}
	else
	{
		ErrorCollection(L"FuncName");
	}

	cmdBuf[cmdIdx] = L'\0'; //XPathCmdParser()의 while 반복문 정지시키는 기능.
}