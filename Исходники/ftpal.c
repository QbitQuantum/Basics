VOID vTestXlates(HDC hdc, RECT *prcl)
{
    HPALETTE ahpal[4];
    HPALETTE hPalOld;
    DWORD ulTemp;

    LOGPALETTE256 alog256[4];

    alog256[0].palVersion = 0x300;
    alog256[0].palNumEntries = 256;
    alog256[1].palVersion = 0x300;
    alog256[1].palNumEntries = 256;
    alog256[2].palVersion = 0x300;
    alog256[2].palNumEntries = 256;
    alog256[3].palVersion = 0x300;
    alog256[3].palNumEntries = 256;

    for (ulTemp = 0; ulTemp < 256; ulTemp++)
    {
	alog256[0].palPalEntry[ulTemp].peRed	  = ulTemp;
	alog256[0].palPalEntry[ulTemp].peBlue	  = 0;
	alog256[0].palPalEntry[ulTemp].peGreen	  = 0;
	alog256[0].palPalEntry[ulTemp].peFlags	  = 0;

	alog256[1].palPalEntry[ulTemp].peRed	  = 0;
	alog256[1].palPalEntry[ulTemp].peBlue	  = ulTemp;
	alog256[1].palPalEntry[ulTemp].peGreen	  = 0;
	alog256[1].palPalEntry[ulTemp].peFlags	  = 0;

	alog256[2].palPalEntry[ulTemp].peRed	  = 0;
	alog256[2].palPalEntry[ulTemp].peBlue	  = 0;
	alog256[2].palPalEntry[ulTemp].peGreen	  = ulTemp;
	alog256[2].palPalEntry[ulTemp].peFlags	  = PC_RESERVED;

	alog256[3].palPalEntry[ulTemp].peRed	  = ulTemp;
	alog256[3].palPalEntry[ulTemp].peBlue	  = ulTemp;
	alog256[3].palPalEntry[ulTemp].peGreen	  = ulTemp;
	alog256[3].palPalEntry[ulTemp].peFlags	  = PC_RESERVED;
    }

    ahpal[0] = CreatePalette((LOGPALETTE *) &alog256[0]);
    ahpal[1] = CreatePalette((LOGPALETTE *) &alog256[1]);
    ahpal[2] = CreatePalette((LOGPALETTE *) &alog256[2]);
    ahpal[3] = CreatePalette((LOGPALETTE *) &alog256[3]);

    hPalOld = SelectPalette(hdc,ahpal[0],0);

    for (ulTemp = 0; ulTemp < 20; ulTemp++)
    {
    	SelectPalette(hdc, ahpal[ulTemp % 4], 0);
    	RealizePalette(hdc);
    	UpdateColors(hdc);
    	SetPaletteEntries(ahpal[ulTemp % 4], 0, 256, alog256[ulTemp % 4].palPalEntry);
    	RealizePalette(hdc);
    	UpdateColors(hdc);
    }

    SelectPalette(hdc,hPalOld,0);

    DeleteObject(ahpal[0]);
    DeleteObject(ahpal[1]);
    DeleteObject(ahpal[2]);
    DeleteObject(ahpal[3]);
}