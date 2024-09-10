void COleClipSource::DoUpperLowerCase(CClip &clip, bool upper)
{
	IClipFormat *unicodeTextFormat = clip.m_Formats.FindFormatEx(CF_UNICODETEXT);
	if (unicodeTextFormat != NULL)
	{
		HGLOBAL data = unicodeTextFormat->Data();
		wchar_t * stringData = (wchar_t *) GlobalLock(data);
		int size = (int) GlobalSize(data);
		CString cs(stringData);
		GlobalUnlock(data);

		//free the old text we are going to replace it below with an upper case version
		unicodeTextFormat->Free();

		CString val;
		if (upper)
		{
			val = cs.MakeUpper();
		}
		else
		{
			val = cs.MakeLower();
		}
		
		long lLen = val.GetLength();
		HGLOBAL hGlobal = NewGlobalP(val.GetBuffer(), ((lLen+1) * sizeof(wchar_t)));
		val.ReleaseBuffer();

		unicodeTextFormat->Data(hGlobal);		
	}

	IClipFormat *asciiTextFormat = clip.m_Formats.FindFormatEx(CF_TEXT);
	if (asciiTextFormat != NULL)
	{
		HGLOBAL data = asciiTextFormat->Data();
		char * stringData = (char *) GlobalLock(data);
		int size = (int) GlobalSize(data);
		CStringA cs(stringData);
		GlobalUnlock(data);

		//free the old text we are going to replace it below with an upper case version
		asciiTextFormat->Free();
		
		CString val;
		if (upper)
		{
			val = cs.MakeUpper();
		}
		else
		{
			val = cs.MakeLower();
		}

		long lLen = val.GetLength();
		HGLOBAL hGlobal = NewGlobalP(val.GetBuffer(lLen), lLen + sizeof(char));
		val.ReleaseBuffer();

		asciiTextFormat->Data(hGlobal);
	}
}