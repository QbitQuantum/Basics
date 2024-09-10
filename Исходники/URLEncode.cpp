// strURL: URL to decode.
CString CURLEncode::Decode(CString strURL)
{
	int i=strURL.Find(_T('%'));
	TCHAR tc1=0, tc2=0;
	BYTE b=0;
	BOOL bFound=FALSE;
	while (i>-1)
	{
		tc1=strURL.GetAt(i+1);
		tc2=strURL.GetAt(i+2);

		if (isHex(tc1) && isHex(tc2))
		{
			b=hexToDec(tc1, tc2);

			// first deal with 1-byte unprintable characters
			if (b<0x1F || b==0x7F) {
				strURL.SetAt(i, b);
				strURL.Delete(i+1, 2);
			} else {
				// Then deal with 1-byte unsafe/reserved characters
				// We are reading for those static LPCTSTR strings,
				// so we have nice support for Unicode
				bFound=FALSE;
				for (int ii=0; ii<m_iUnsafeLen && !bFound; ii++)
				{
					if (__toascii(m_lpszUnsafeString[ii])==b)
					{
						strURL.SetAt(i, m_lpszUnsafeString[ii]);
						strURL.Delete(i+1, 2);
						bFound=TRUE;
					}
				}
				for (int ii=0; ii<m_iReservedLen && !bFound; ii++)
				{
					if (__toascii(m_lpszReservedString[ii])==b)
					{
						strURL.SetAt(i, m_lpszReservedString[ii]);
						strURL.Delete(i+1, 2);
						bFound=TRUE;
					}
				}
				// Then deal with UTF-8 (2-bytes) characters
				if (!bFound)
				{
					// We need to have 2 bytes for decoding
					if (strURL.GetAt(i+3)==_T('%'))
					{
						tc1=strURL.GetAt(i+4);
						tc2=strURL.GetAt(i+5);

						if (isHex(tc1) && isHex(tc2))
						{
							BYTE b2=hexToDec(tc1, tc2);
							strURL.SetAt(i, fromUTF8(MAKEWORD(b2, b)));
							strURL.Delete(i+1, 5);
						}
					}
				}
			}
		}

		i=strURL.Find(_T('%'), i+1);
	}

	return strURL;
}