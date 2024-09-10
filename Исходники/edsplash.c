static int	MyPaintSplash (HWND pmSplashWindow, BOOL pmDraw)
{
    SplashWindowInfoPtr	myInfo;
    HDC			myDisplayContext, myMemDC;
    PAINTSTRUCT		myPaintStruct;
    BITMAP		myBitmap;
    HBITMAP		myOldBitmap;
    HPALETTE		myPalette, myOldPalette;
    POINT		myPoint, myOrigin;
    int			myY;

    myInfo = MyGetSplashWindowInfo (pmSplashWindow);
        		
    myDisplayContext = BeginPaint (pmSplashWindow, &myPaintStruct);

    if (pmDraw && myInfo -> usePicture)
    {
    	myMemDC = CreateCompatibleDC (NULL);
    	myOldBitmap = SelectBitmap (myMemDC, myInfo -> picture);

    	GetObject (myInfo -> picture, sizeof(BITMAP), (LPSTR) &myBitmap);

    	myPoint.x = myBitmap.bmWidth;
    	myPoint.y = myBitmap.bmHeight;
    	DPtoLP (myDisplayContext, &myPoint, 1);

    	myOrigin.x = 0;
    	myOrigin.y = 0;
    	DPtoLP (myMemDC, &myOrigin, 1);
    	
    	//
    	// We need to perform all sorts of stuff to get the palette right...
    	//
   	// If the DIBSection is 256 color or less, it has a color table
   	if ((myBitmap.bmBitsPixel * myBitmap.bmPlanes) <= 8)
   	{
	   RGBQUAD      myClrTbl [256];
	   LPLOGPALETTE myLogPal;
	   WORD         cnt;

   	    // Get the DIBSection's color table
   	    GetDIBColorTable (myMemDC, 0, 256, myClrTbl);
   	    
	    // Create a palette from the color tabl
	    myLogPal = (LOGPALETTE *) malloc (sizeof(LOGPALETTE) + 
	    					(256 * sizeof(PALETTEENTRY)));
	    myLogPal -> palVersion = 0x300;
	    myLogPal -> palNumEntries = 256;
	    for (cnt = 0 ; cnt < 256 ; cnt++)
	    {
	 	myLogPal -> palPalEntry [cnt].peRed = myClrTbl [cnt].rgbRed;
		myLogPal -> palPalEntry [cnt].peGreen = myClrTbl [cnt].rgbGreen;
		myLogPal -> palPalEntry [cnt].peBlue = myClrTbl [cnt].rgbBlue;
		myLogPal -> palPalEntry [cnt].peFlags = 0;
	    }
   	    myPalette = CreatePalette (myLogPal);
	    free (myLogPal);
   	    
	    // Select Palette
	    myOldPalette = SelectPalette (myDisplayContext, myPalette, FALSE);
	    RealizePalette (myDisplayContext);
	}

	if (gProgram.isTuring)
	{
    	    BitBlt (myDisplayContext, 0, 0, myPoint.x, myPoint.y,
            	myMemDC, myOrigin.x, myOrigin.y, SRCCOPY);
	}
	else
	{
    	    BitBlt (myDisplayContext, MARGIN, 0, myPoint.x, myPoint.y,
            	myMemDC, myOrigin.x, myOrigin.y, SRCCOPY);
        }

	SelectObject (myMemDC, myOldBitmap);
   	if ((myBitmap.bmBitsPixel * myBitmap.bmPlanes) <= 8)
   	{
   	    SelectPalette (myDisplayContext, myOldPalette, FALSE);
   	    DeleteObject (myPalette);
   	}
    	DeleteDC (myMemDC);
    }

    // Place Ministry message over top of the Sun
    if (gProgram.assistedByIBM && gProgram.isTuring)
    {
    	//
    	// Output "Ministry of Education License Message"
    	//
    	myY = LARGE_GAP;
        MyDrawString (myInfo, myDisplayContext, myInfo -> versionFont,
    		      myInfo -> miniEdMsg [0], &myY, pmDraw, FALSE);
	myY += SMALL_GAP;
        MyDrawStrings (myInfo, myDisplayContext, myInfo -> chiefProgrammerFont,
    		  &myInfo -> miniEdMsg [1], 9, &myY, pmDraw, FALSE);
    } // if (gProgram.assistedByIBM)
       
    if (myInfo -> usePicture)
    {
    	// The starting Y position
    	myY = myInfo -> bitmapHeight + MARGIN;
    }
    else
    {
    	myY = SMALL_GAP;
        MyDrawStrings (myInfo, myDisplayContext, myInfo -> productNameFont,
    		  myInfo -> productNameMsg, myInfo -> productNameLines, 
    		  &myY, pmDraw, TRUE);
    	myY += LARGE_GAP;
    }

    //
    // Output "Created By Holt Software Associates Inc."
    //
    MyDrawString (myInfo, myDisplayContext, myInfo -> createdByFont,
    		  myInfo -> createdByMsg, &myY, pmDraw, TRUE);
    
    if (gProgram.assistedByIBM && gProgram.isJava)
    {
    	//
    	// Output "Development Assisted by IBM Corp."
    	//
        MyDrawString (myInfo, myDisplayContext, myInfo -> createdByFont,
    		      myInfo -> assistedByMsg, &myY, pmDraw, TRUE);
    } // if (gProgram.assistedByIBM)

    //
    //        	    
    // Output "Lead Programmer: Tom West"
    //
    if (gProgram.isJava)
    {
        MyDrawString (myInfo, myDisplayContext, myInfo -> chiefProgrammerFont,
    		      myInfo -> leadProgrammerMsg, &myY, pmDraw, TRUE);
    } // if (gProgram.isJava)
	    	
    //    	    
    // Output version number	    	
    //
    myY += SMALL_GAP;
    MyDrawString (myInfo, myDisplayContext, myInfo -> versionFont,
    		  myInfo -> versionString, &myY, pmDraw, TRUE);

    //
    // Output install kind specific info
    if (gProgram.miniVersion)
    {
    	//
	// Output: Licensed to xxx.
	//	   This version cannot compile programs of greater than 100 lines in length
	//
        myY += SMALL_GAP;
        MyDrawStrings (myInfo, myDisplayContext, myInfo -> chiefProgrammerFont,
    		       myInfo -> miniMsg, 3, &myY, pmDraw, TRUE);
    }
    else if (gProgram.installKind == INSTALL_KIND_EVAL)
    {
    	//
	// Output: This version is for personal evaluation purposes only.
	//	   It may not be redistributed or used for teaching purposes.
	//	   See the "Help" menu for information on obtaining Ready.
	//	   This version is time limited and will not execute Java programs after xxx
	// or
	//
	// Output: This version is for personal evaluation purposes only.
	//	   It may not be redistributed or used for teaching purposes.
	//	   See the "Help" menu for information on obtaining Ready.
	//	   This demonstration version of the software is restricted and
	//		(1) Cannot save programs,
	//    	        (2) Cannot compile programs of greater than 100 lines in length, and
	//		(3) Will not execute programs after xxx
	//
        myY += SMALL_GAP;
	if (gProgram.restrictedVersion)
	{
            MyDrawStrings (myInfo, myDisplayContext, 
            		   myInfo -> chiefProgrammerFont,
    		           myInfo -> evalMsg, 3, &myY, pmDraw, TRUE);
	    myY += SMALL_GAP;    		           
            MyDrawStrings (myInfo, myDisplayContext, 
            		   myInfo -> chiefProgrammerFont,
    		           myInfo -> restrictMsg, 4, &myY, pmDraw, TRUE);
	}
	else
	{
            MyDrawStrings (myInfo, myDisplayContext, 
            		   myInfo -> chiefProgrammerFont,
    		           myInfo -> evalMsg, 4, &myY, pmDraw, TRUE);
	}
    }
    else if (gProgram.installKind == INSTALL_KIND_BETA)
    {
    	//
	// Output: This version is for personal beta test purposes only.
	//	   It may not be redistributed or used for teaching purposes.
	//	   Please report all bugs found in this software to [email protected]
	//	   This version of the software will not execute programs after xxx
	//
        myY += SMALL_GAP;
        MyDrawStrings (myInfo, myDisplayContext, 
            	       myInfo -> chiefProgrammerFont,
    		       myInfo -> betaMsg, 4, &myY, pmDraw, TRUE);
    }
    else if (gProgram.installKind == INSTALL_KIND_PERSONAL)
    {
        myY += SMALL_GAP;
        MyDrawString (myInfo, myDisplayContext, myInfo -> chiefProgrammerFont,
    		      myInfo -> personalMsg, &myY, pmDraw, TRUE);
    }
    else if (gProgram.installKind == INSTALL_KIND_SITE)
    {
        myY += SMALL_GAP;
        MyDrawString (myInfo, myDisplayContext, myInfo -> chiefProgrammerFont,
    		      myInfo -> siteMsg, &myY, pmDraw, TRUE);
    }
    else if (gProgram.installKind == INSTALL_KIND_REDISTRIB)
    {
        myY += SMALL_GAP;
        MyDrawString (myInfo, myDisplayContext, myInfo -> chiefProgrammerFont,
    		      myInfo -> redistribMsg, &myY, pmDraw, TRUE);
    }
    
    if (gProgram.isJava)
    {
    	//
    	// Output "Using IBM's Jikes Java Compiler"
    	//
        myY += SMALL_GAP;
        MyDrawString (myInfo, myDisplayContext, myInfo -> usingJikesFont,
    		      myInfo -> usingJikesMsg, &myY, pmDraw, TRUE);

        myY += SMALL_GAP;
	if (gProgram.operatingSystem == WIN_95)
	{
            MyDrawString (myInfo, myDisplayContext, myInfo -> trademarkFont,
	    		  myInfo -> win95Msg, &myY, pmDraw, TRUE);
	}
	else
	{
            MyDrawString (myInfo, myDisplayContext, myInfo -> trademarkFont,
	    		  myInfo -> jreLevelMsg, &myY, pmDraw, TRUE);
	}

    	//    	        
    	// Output trademark information
    	//
        myY += SMALL_GAP;
        MyDrawString (myInfo, myDisplayContext, myInfo -> trademarkFont,
    		      myInfo -> trademarkMsg, &myY, pmDraw, TRUE);
    } // if (gProgram.isJava)
    
    EndPaint (pmSplashWindow, &myPaintStruct);
    
    return myY;
} // MyPaintSplash