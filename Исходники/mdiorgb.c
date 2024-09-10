BOOL	MDIORGB_SetColour (OOTint pmClrNum, OOTreal pmRed, OOTreal pmGreen, 
			   OOTreal pmBlue)
{
    PALETTEENTRY 	myPaletteEntry;
    MIOWinInfoPtr	myInfo = MIO_selectedRunWindowInfo;
 
/*   
    BITMAPINFO		myBitMapInfo;
    PBITMAPINFOHEADER	myBitMapInfoHeader;
    void		*myBits;

    ZeroMemory (&myBitMapInfo, sizeof(myBitMapInfo));
    myBitMapInfo.bmiHeader.biSize = sizeof (myBitMapInfo.bmiHeader);
    GetDIBits (myInfo -> offscreenDeviceContext, myInfo -> offscreenBitMap,
	0, 0, NULL, &myBitMapInfo, DIB_PAL_COLORS);
    myBitMapInfoHeader = (BITMAPINFOHEADER *) malloc (sizeof (BITMAPINFO) +
						      sizeof (RGBQUAD) * 256);
    // Duplicate the bitmapinfoheader information into the new struct.
    memcpy(myBitMapInfoHeader , &myBitMapInfo, sizeof(myBitMapInfo.bmiHeader));
    myBits = malloc (myBitMapInfoHeader -> biSizeImage);
    GetDIBits (myInfo -> offscreenDeviceContext, myInfo -> offscreenBitMap,
	0, 1, myBits, &myBitMapInfo, DIB_PAL_COLORS);

/*
1. To fill in a BITMAPINFOHEADER struct. Call Thus:

  BITMAPINFO bmi;

  Here GetDIBits will use the inititlized bmiSize member to determine
  which structure it should be writing to. It will fill in the
  BITMAPINFOHEADER struct with the size and characteristics of the
  bitmap.
    myBitMapInfo = MyCreateBitmapInfo (myInfo -> offscreenBitMap);
    if (myBitMapInfo == NULL)
    {
    	// Error Message
    	return FALSE;
    }
    
    myBitMapInfoHeader = (PBITMAPINFOHEADER) myBitMapInfo;
    myBits = malloc (myBitMapInfoHeader -> biSizeImage);
    if (myBits == NULL)
    {
    	// Error Message
    	return FALSE;
    }

    // Retrieve the color table (RGBQUAD array) and the bits 
    // (array of palette indices) from the DIB. 
//    if (!GetDIBits (myInfo -> deviceContext, myInfo -> offscreenBitMap, 0, 
//    		    (WORD) myBitMapInfoHeader -> biHeight, myBits, myBitMapInfo, 
//		    DIB_RGB_COLORS)) 
//    {
//    	// Error Message
//    	return FALSE;
//    }
*/
/*****/    

    // Now set the new palette entry
    myPaletteEntry.peRed = (int) (pmRed * 255 + 0.5);
    myPaletteEntry.peGreen = (int) (pmGreen * 255 + 0.5);
    myPaletteEntry.peBlue  = (int) (pmBlue * 255 + 0.5);
    myPaletteEntry.peFlags = 0;

    if (SetPaletteEntries (myInfo -> palette, pmClrNum, 1, 
    		           &myPaletteEntry) == 0)
    {
    	return FALSE;
    }    		           

    MDIORGB_UseNewPalette (myInfo);
    RealizePalette (myInfo -> deviceContext);
    RealizePalette (myInfo -> offscreenDeviceContext);
    
    return TRUE;
} // MDIORGB_SetColour