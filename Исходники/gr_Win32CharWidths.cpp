void GR_Win32CharWidths::setCharWidthsOfRange(HDC hdc, UT_UCSChar c0, UT_UCSChar c1)
{
	if(m_vRanges.getItemCount() == 0)
	{
		_retrieveFontInfo(hdc);
	}
	
	UINT k;
	int w;
#ifdef DEBUG
	DWORD iErrorCode = 0;
#endif

	// Windows NT and Windows 95 support the Unicode Font file. 
	// All of the Unicode glyphs can be rendered if the glyph is found in
	// the font file. However, Windows 95 does  not support the Unicode 
	// characters other than the characters for which the particular codepage
	// of the font file is defined.
	// Reference Microsoft knowledge base:
	// Q145754 - PRB ExtTextOutW or TextOutW Unicode Text Output Is Blank
	if (UT_IsWinNT())
	{
		for (k=c0; k<=c1; k++)
		{
			if(k == 0x200B || k == 0xFEFF || k == UCS_LIGATURE_PLACEHOLDER)
				setWidth(k,0);
			else if(!_doesGlyphExist(k))
			{
				setWidth(k,GR_CW_ABSENT);
			}
			else
			{
				GetCharWidth32W(hdc,k,k,&w);
#ifdef DEBUG
				ABC abc;
				int iRes = GetCharABCWidthsW(hdc,k,k,&abc);
#endif
				// handle overstriking chars here
				UT_uint32 iOver = UT_isOverstrikingChar(k);
				if(!w || iOver != UT_NOT_OVERSTRIKING)
				{
					iOver &= UT_OVERSTRIKING_TYPE;

					if(iOver == UT_OVERSTRIKING_RIGHT)
					{
						w = 0;
					}
					else
					{
						ABC abc;
						UT_DebugOnly<int> iRes = GetCharABCWidthsW(hdc,k,k,&abc);
						UT_ASSERT( iRes );
						

						if(iOver == UT_OVERSTRIKING_LEFT)
						{
							UT_ASSERT( abc.abcB <  GR_OC_MAX_WIDTH);
							w = abc.abcB | GR_OC_LEFT_FLUSHED;
						}
						else
						{
							w = abc.abcB /*+ abc.abcA + abc.abcC*/;
							w = -w;
						}
					}
				}
				
				setWidth(k,w);
			}
		}
	}
	else
	{
		HFONT hFont = (HFONT) GetCurrentObject(hdc, OBJ_FONT);
		LOGFONTW aLogFont;
		UT_DebugOnly<int> iRes = GetObjectW(hFont, sizeof(LOGFONTW), &aLogFont);
		UT_ASSERT(iRes);

		xxx_UT_DEBUGMSG(("gr_Win32Graphics::getCharWidth: extra interchar. spacing %d\n", GetTextCharacterExtra(hdc)));
		
		if(aLogFont.lfCharSet == SYMBOL_CHARSET)
		{
			// Symbol character handling
			for (k=c0; k<=c1; k++)
			{
				if(!_doesGlyphExist(k))
				{
					setWidth(k,GR_CW_ABSENT);
				}
				else
				{
					SIZE Size;
					char str[sizeof(UT_UCSChar)];
					int iConverted = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR) &k, 1,
														 str, sizeof(str), NULL, NULL);
					GetTextExtentPoint32A(hdc, str, iConverted, &Size);
					setWidth(k, Size.cx);
				}
			}
		}
		else
		{
			// Unicode font and default character sets
			for (k=c0; k<=c1; k++)
			{
				if(k == 0x200B || k == 0xFEFF || k == UCS_LIGATURE_PLACEHOLDER)
					setWidth(k,0);
				else if(!_doesGlyphExist(k))
				{
					setWidth(k,GR_CW_ABSENT);
				}
				else
				{
					SIZE Size;
					wchar_t sz1[2];
					sz1[0] = k;
					
					GetTextExtentPoint32W(hdc, sz1, 1, &Size);
					// handle overstriking chars here
					UT_uint32 iOver = UT_isOverstrikingChar(k);
					if(!Size.cx ||  iOver != UT_NOT_OVERSTRIKING)
					{
						iOver &= UT_OVERSTRIKING_TYPE;

						if(iOver == UT_OVERSTRIKING_RIGHT)
						{
							Size.cx = 0;
						}
						else
						{
							ABC abc;
							iRes = GetCharABCWidthsW(hdc,k,k,&abc);

							// I have commented out the assert below,
							// because when the function above is called for
							// the first time, it seems to always
							// return 0, even though it fills the abc
							// structure with reasonable values,
							// Tomas, June 22, 2003
							// UT_ASSERT( iRes );
#ifdef DEBUG
							if(!iRes)
							{
								iErrorCode = GetLastError();
							}
#endif

							if(iOver == UT_OVERSTRIKING_LEFT)
							{
								UT_ASSERT( abc.abcB <  GR_OC_MAX_WIDTH);
								Size.cx = abc.abcB | GR_OC_LEFT_FLUSHED;
							}
							else
							{
								Size.cx = abc.abcB;
								Size.cx = -Size.cx;
							}
						}
					}
				
#ifdef DEBUG
					if(iErrorCode)
					{
						LPVOID lpMsgBuf;
						FormatMessageW( 
									  FORMAT_MESSAGE_ALLOCATE_BUFFER | 
									  FORMAT_MESSAGE_FROM_SYSTEM | 
									  FORMAT_MESSAGE_IGNORE_INSERTS,
									  NULL,
									  iErrorCode,
									  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
									  (LPWSTR) &lpMsgBuf,
									  0,
									  NULL 
									  );
						// Process any inserts in lpMsgBuf.
						// ...
						// Display the string.
						//MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
						UT_DEBUGMSG(("char width error: %s\n", lpMsgBuf));
						// Free the buffer.
						LocalFree( lpMsgBuf );
					}
#endif
					setWidth(k,Size.cx);
					xxx_UT_DEBUGMSG(("gr_Win32Graphics::getCharWidths: 0x%x: Size.cx %d\n", k, Size.cx));
				}
			}
		}
	}
}