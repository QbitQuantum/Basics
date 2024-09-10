void CCrystalParser::WrapLine( int nLineIndex, int nMaxLineWidth, int *anBreaks, int &nBreaks )
{
	// The parser must be attached to a view!
	ASSERT( m_pTextView );

	int			nLineLength = m_pTextView->GetLineLength( nLineIndex );
	int			nTabWidth = m_pTextView->GetTabSize();
	int			nLineCharCount = 0;
	int			nCharCount = 0;
	LPCTSTR	szLine = m_pTextView->GetLineChars( nLineIndex );
	int			nLastBreakPos = 0;
	int			nLastCharBreakPos = 0;
	bool		bBreakable = false;
	TCHAR		ch;
	int			nCharWidth = m_pTextView->GetCharWidth();
	WORD		wCharType;

	for( int i = 0; i < nLineLength; i++ )
	{
		ch = szLine[i]; 
		// remember position of whitespace for wrap
		if( bBreakable )
		{
			nLastBreakPos = i;
			nLastCharBreakPos = nCharCount;
			bBreakable = false;
		}

		// increment char counter (evtl. expand tab)
		if( ch == _T('\t') )
		{
			nLineCharCount+= (nTabWidth - nCharCount % nTabWidth);
			nCharCount+= (nTabWidth - nCharCount % nTabWidth);
			// remember whitespace
			bBreakable = true;
		}
		else
		{
#ifndef _UNICODE
			if( IsDBCSLeadByte((BYTE)ch) )
			{
				nLineCharCount += 2;
				nCharCount += 2;
				GetStringTypeA(LOCALE_USER_DEFAULT,CT_CTYPE3, &szLine[i], 2, &wCharType);
				// remember whitespace
				if( (wCharType & (C3_IDEOGRAPH | C3_HIRAGANA | C3_KATAKANA)))
					bBreakable = true;
			}
			else
			{
				nLineCharCount ++;
				nCharCount ++;
				// remember whitespace
				if( ch == _T(' ') )
					bBreakable = true;
			}
#else
			if (ch & 0xff80)
			{
				int n = m_pTextView->GetCharWidthFromChar(ch) / nCharWidth;
				nLineCharCount += n;
				nCharCount += n;
				GetStringTypeW(CT_CTYPE3, &ch, 1, &wCharType);
				// remember whitespace
				if( wCharType & (C3_IDEOGRAPH | C3_HIRAGANA | C3_KATAKANA) )
					bBreakable = true;
			}
			else
			{
				nLineCharCount ++;
				nCharCount ++;
				// remember whitespace
				if( ch == _T(' ') )
					bBreakable = true;
			}
#endif
		}

		// wrap line
		if( nLineCharCount >= nMaxLineWidth )
		{
			// if no wrap position found, but line is to wide, 
			// wrap at current position
			if( nLastBreakPos == 0 )
			{
				nLastBreakPos = i;
				nLastCharBreakPos = nCharCount;
			}
			if( anBreaks )
				anBreaks[nBreaks++] = nLastBreakPos;
			else
				nBreaks++;

			nLineCharCount = nCharCount - nLastCharBreakPos;
			nLastBreakPos = 0;
		}

#ifndef _UNICODE
		if (IsDBCSLeadByte((BYTE)ch))
			i++;
#endif
	}
}