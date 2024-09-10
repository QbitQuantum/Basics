void CDib::CreatePaletteFromImage( CPalette& palette)const
{
	if( palette.m_hObject )
		palette.DeleteObject();


	ASSERT( IsIndexed() == GetBPP() <= 8);
	if( GetBPP() <= 8)
	{
		GetPalette(palette);
		//CPalette* pal =  CPalette::FromHandle(m_hPalette);
		//PALETTEENTRY colors[256] = {0};
		//pal->GetPaletteEntries(0, 256, colors);
		
		//palette.SetPaletteEntries( 0, 256, colors );
	}
	else
	{
		LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) +
		256 * sizeof(PALETTEENTRY)];

		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = 256;

		palette.CreatePalette(pLogPal);
		delete pLogPal;	
		pLogPal = NULL;

	
		
		CArray<COLORREF, COLORREF> colorArray;

		int height= GetHeight();
		int width = GetWidth();
		for(int i=0; i<width; i++)
		{
			for(int j=0; j<height; j++)
			{
				COLORREF color = GetPixel(i, j);
				if( UtilWin::FindInArray( colorArray, color) == -1)
					colorArray.Add(color);
				if( colorArray.GetSize() == 256)
					break;
			}
			
			if( colorArray.GetSize() == 256)
					break;
		}

		PALETTEENTRY pe[256]={0};
    
		
		for (int i = 0; i < colorArray.GetSize(); i++) 
		{
			COLORREF color = colorArray[i];
			pe[i].peRed = GetRValue(color);
			pe[i].peGreen = GetGValue(color);
			pe[i].peBlue = GetBValue(color);
		}

		palette.SetPaletteEntries(0, 256, pe);
	}
}