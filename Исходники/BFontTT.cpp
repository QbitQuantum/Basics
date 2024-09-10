int CBFontTT::FormatTextW(int X, int Y, BYTE* Text, HDC hDC, int Width, int MaxHeight)
{
	SIZE Size;
	GetTextExtentPoint32(hDC, "Ay", 2, &Size);
	int LineHeight = Size.cy;

	int TextLen = wcslen((wchar_t*)Text);
	wchar_t* Str = (wchar_t*)Text;
	int LastSpace = -1;
	int CurrY = 0;

	if(TextLen==0) return 0;

	while(true)
	{
		if(MaxHeight >=0 && CurrY + LineHeight > MaxHeight) return CurrY;

		int i=0;
		LastSpace = -1;

		do
		{
			i++;
			if(Str[i-1]=='\n')
			{
				i--;
				break;
			}
			GetTextExtentPoint32W(hDC, Str, i, &Size);
			if(Size.cx <= Width)
			{
				if(Str[i-1]==' ') LastSpace = i;				
			}
		}
		while(Str + i <(wchar_t*)Text+TextLen && Size.cx <= Width);

		// safety break
		if(i==1 && Size.cx > Width) return CurrY;

		// we encountered a newline
		if(Size.cx > Width)
		{
			if(LastSpace>=0) i = LastSpace-1;
			else i--;
		}

		UINT Flags = ETO_OPAQUE;
		if(Game->m_TextRTL) Flags |= ETO_RTLREADING;
		ExtTextOutW(hDC, X, Y + CurrY, Flags, NULL, Str, i, NULL);
		if(LastSpace>=0) i++;
		Str+=i;
		if(Str>(wchar_t*)Text+TextLen)
		{
			CurrY+=LineHeight;
			break;
		}

		if(Str[0]=='\n') Str++;
		CurrY+=LineHeight;

		// we're at the end
		if(Str>=(wchar_t*)Text+TextLen) break;
	}
	return CurrY /*+ LineHeight*/;
}