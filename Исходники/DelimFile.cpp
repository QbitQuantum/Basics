//--------------------------------------------------------------------------------
void CDelimFile::ParseLine(char cDelim, char cComment, bool bStripQuotes, LPCTSTR pText, CStringArray& sOut)
	{
	CString sIn(pText);

	sIn.TrimLeft();
	sIn.TrimRight();
	if(sIn.IsEmpty())
		return;

	// if this is a comment line then
	// add the whole thing and return
	if(sIn[0] == cComment)
		{
		sOut.Add(sIn);
		return;
		}

	CString sTemp;
	for(int i = 0; i < sIn.GetLength(); i++)
		{
		// is this a quoted string
		if(sIn[i] == '"')
			{
			// find the closing quote
			int nIndex = sIn.Find('"', i + 1);
			// no closing quote
			if(nIndex == -1)
				{
				// add the remainder of the string and return
				sTemp = sIn.Mid(i + 1);
				sTemp.TrimLeft();
				sTemp.TrimRight();
				sOut.Add(sTemp);
				return;
				}
			else
				{
				// start at the quote if quotes are included
				// otherwise start at the next char
				int nOffset = bStripQuotes ? 1 : 0;
				int nBackset = bStripQuotes ? -1 : 1;
				sTemp = sIn.Mid(i + nOffset, nIndex - i + nBackset);
				sTemp.TrimLeft();
				sTemp.TrimRight();
				sOut.Add(sTemp);
				sTemp.Empty();
				i = nIndex + 1;
				}
			}
		else
			if(sIn[i] == cDelim)
				{
				sTemp.TrimLeft();
				sTemp.TrimRight();
				sOut.Add(sTemp);
				sTemp.Empty();
				}
			else
				sTemp += sIn[i];
		}

	if(! sTemp.IsEmpty())
		{
		sTemp.TrimLeft();
		sTemp.TrimRight();
		sOut.Add(sTemp);
		}
	}