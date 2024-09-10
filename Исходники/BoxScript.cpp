UINT CBoxScript::ParseScriptTextCodePage(LPCSTR pstrText, int nCount)
{
	static struct
	{
		char *pstrName;
		int nSize;
	}CmdName[] =
	{
		{"#codepage", 9}
	};
	#define CMD_COUNT (sizeof(CmdName) / sizeof(CmdName[0]))
	int i;
	LPCSTR pstrTemp, pstrTemp1;
	int nTempCount;
	int nLineCount = 1;

	while(nCount > 0 && IsBlank(pstrText[0]))
	{
		if(pstrText[0] == '\n')
			nLineCount ++;

		pstrText ++;
		nCount --;
	}

	while(nCount > 0 && pstrText[0] == '#')
	{
		for(i = 0; i < CMD_COUNT; i ++)
			if(nCount > CmdName[i].nSize &&
				!_strnicmp(pstrText, CmdName[i].pstrName, CmdName[i].nSize) &&
				IsBlankChar(pstrText[CmdName[i].nSize]))
				break;

		if(i == CMD_COUNT)
			break;

		pstrText += CmdName[i].nSize;
		nCount -= CmdName[i].nSize;

		while(nCount > 0 && IsBlankChar(pstrText[0]))
		{
			pstrText ++;
			nCount --;
		}

		if(nCount > 0 && pstrText[0] == '\"')
		{
			pstrText ++;
			nCount --;
		}

		pstrTemp = pstrText;
		nTempCount = nCount;
		while(nTempCount > 0 && !IsLineChar(pstrTemp[0]))
		{
			pstrTemp ++;
			nTempCount --;
		}

		pstrTemp1 = pstrTemp;
		while(pstrTemp1 > pstrText && IsBlankChar(pstrTemp1[0]))
			pstrTemp1 --;

		if(pstrTemp1 > pstrText && pstrTemp1[-1] == '\"')
			pstrTemp1 --;

		CStringA strValue;

		strValue.SetString(pstrText, (int)(pstrTemp1 - pstrText));

		pstrText = pstrTemp;
		nCount = nTempCount;

		if (i == 0) return atoi(strValue);

		while(nCount > 0 && IsBlank(pstrText[0]))
		{
			if(pstrText[0] == '\n')
				nLineCount ++;

			pstrText ++;
			nCount --;
		}
	}

	return 0;
}