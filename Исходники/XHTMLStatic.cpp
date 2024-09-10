///////////////////////////////////////////////////////////////////////////////
// FormatText
int CXHTMLStatic::FormatText(HDC hdc, 
							 LPCTSTR lpszText, 
							 RECT * pRect, 
							 int nInitialXOffset)
{
	TRACE(_T("in CXHTMLStatic::FormatText:  nInitialXOffset=%d  <%-20.20s>\n"), 
		nInitialXOffset, lpszText);
	//TRACERECT(*pRect);
	int		xStart, /*yStart,*/ nWord, xNext, xLast, nLeftMargin;
	TCHAR	*pText = (TCHAR *) lpszText;
	SIZE	size;

	xNext = nInitialXOffset;
	nLeftMargin = nInitialXOffset;
	xLast = 0;

	if (pRect->top >= (pRect->bottom-1))
		return 0;

	// set initial size
	TCHAR * szTest = _T("abcdefgABCDEFG");
	GetTextExtentPoint32(hdc, szTest, _tcslen(szTest), &size);

	// prepare for next line - clear out the error term
	SetTextJustification(hdc, 0, 0);

	CString strOut = _T("");

	BOOL bReturnSeen = FALSE;

	TEXTMETRIC tm;
	::GetTextMetrics(hdc, &tm);

	do									// for each text line
	{
		nWord = 0;						// initialize number of spaces in line

		// skip to first non-space in line
		while (/**pText != _T('\0') && */*pText == _T(' '))
		{
			if (xNext)
				strOut += *pText;
			pText++;
		}

		for(;;)							// process each word
		{
			CString strWord;
			TCHAR *saved_pText = pText;
			strWord = GetNextWord(&pText, &bReturnSeen);

			CString strTrial;
			strTrial = strOut + strWord;

			// after each word, calculate extents
			nWord++;
			GetTextExtentPoint32(hdc, strTrial, strTrial.GetLength(), &size);

			BOOL bOverflow = (size.cx >= (pRect->right - xNext - 2));	
											// don't get too close to margin,
											// in case of italic text

			if (bOverflow)
			{
				if (strOut.IsEmpty())
				{
					bOverflow = FALSE;
					strOut = strWord;
				}
			}
			else
			{
				strOut += strWord;
			}

			if (bReturnSeen || bOverflow || (*pText == _T('\0')))
			{
				if (strOut.IsEmpty())
					break;

				if (bOverflow)
					pText = saved_pText;
				nWord--;               // discount last space at end of line

				// if end of text and no space characters, set pEnd to end

				GetTextExtentPoint32(hdc, strOut, strOut.GetLength(), &size);

				xStart = pRect->left;
				xStart += xNext;
				xNext = 0;
				xLast = xStart + size.cx;

				// display the text

				if ((m_yStart <= (pRect->bottom-size.cy)))// && (!IsBlank(strOut)))
				{
					TextOut(hdc, xStart, m_yStart, strOut, strOut.GetLength());
					if (*pText || bReturnSeen)
					m_yStart += size.cy;
				}

				// prepare for next line - clear out the error term
				SetTextJustification(hdc, 0, 0);

				strOut.Empty();
			}
			else	// new word will fit
			{

			}
		}

		nWord--;               // discount last space at end of line

		// if end of text and no space characters, set pEnd to end

		// prepare for next line - clear out the error term
		SetTextJustification(hdc, 0, 0);

		strOut.Empty();

	} while (*pText && (m_yStart < pRect->bottom));

	if (m_yStart > (pRect->bottom-size.cy))
		pRect->top = pRect->bottom;
	else
		pRect->top = m_yStart;

	return xLast;
}