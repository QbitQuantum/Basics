void CSWCommandLine::Parse (CUniversalText utCmdLine)
{
	Cleanup ();
	static CUniversalText utDelimiters = L" \t\r\n";
	
	UINT uBeg = 0, uEnd = 0, uLen; 
	bool fQuoteOpened = false, fTrimmed = false;

	while (uEnd <= (uLen = utCmdLine.GetLength ()))
	{
		if (uEnd == uLen || (utDelimiters.FindWCHAR (utCmdLine.GetWCHAR (uEnd)) != -1 && !fQuoteOpened))
		{
			if (fTrimmed)
			{
				CUniversalText* pNewWord;
				pNewWord = new CUniversalText (utCmdLine.Mid (uBeg, uEnd - uBeg));

				m_rgputAll.Add (pNewWord);
				if (IsKey (*pNewWord))
					m_rgputKeys.Add ((pNewWord));
				else
					m_rgputFormal.Add (pNewWord);
			}
			fTrimmed = false;
			uBeg = uEnd;
		}
		else
		{
			if (utCmdLine.GetWCHAR (uEnd) == L'"')
			{
				fQuoteOpened = !fQuoteOpened;
				utCmdLine.Delete (1, uEnd);
				continue;
			}
			else
			{
				if (!fTrimmed)
				{
					uBeg = uEnd;
					fTrimmed = true;
				}
			}
		}
		uEnd++;
	}
}