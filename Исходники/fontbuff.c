/*********************************************************
**
**  Adds a new font to the buffer.
**
**  If no space is available, the least used font is 
**  replaced.
**
**  NOTE: If an existing font is being replaced, 
**        the function selects the SYSTEM font into the
**        given HDC so that it can be sure that the font 
**        being deleted is not currently selected.
**
**********************************************************/
BOOL __far __pascal AddFont( HWND hWnd, HFONTBUFFER hFontBuffer, HFONT hFont, WORD wFontNumber )
{
  FPFONTBUFFER fpFontBuffer;
  FPFONTINFO   fpFontInfo, 
               fpFontLeastUsed;
  WORD         wIndex;
  HDC          hDC;
   

  /* No font buffer.  */
  if( hFontBuffer == NULL ) return FALSE;
  
  /* Get pointer to the font buffer. */
  fpFontBuffer = ( FPFONTBUFFER ) GlobalLock( hFontBuffer );
  
  /* Get pointer to the first font info node. */
  fpFontInfo = GlobalLock( fpFontBuffer->hFontInfo );

  /* If we haven't reached - add space for the new font to the buffer. */
  if( fpFontBuffer->wNumFonts < MAX_FONTS )
  {
    /* Skip to the next unused slot.*/
    fpFontInfo = fpFontInfo + fpFontBuffer->wNumFonts;

    /* 
    ** Increment the count of how many fonts are
    ** in the font buffer.
    */
    fpFontBuffer->wNumFonts = fpFontBuffer->wNumFonts + 1;
  }


  /* We've reached maximum buffer space. */
  else
  {
    /* 1st font will be replaced. */
    fpFontLeastUsed = fpFontInfo;
    
    /* Find the font that hasn't been used for the longest time. */
    for( wIndex = 0; wIndex < fpFontBuffer->wNumFonts; wIndex++ )
    {
      /* Last time font used. */
      if( fpFontInfo->dwTickCount < fpFontLeastUsed->dwTickCount ) 
      {
        /* New replacement font. */
        fpFontLeastUsed = fpFontInfo;
      }
          
      /* Goto next node. */
      fpFontInfo++;
    }
  
    /* Make sure the font is not selected. */
    hDC = GetDC( hWnd );
    SelectObject( hDC, GetStockObject( SYSTEM_FONT ) ); 
    ReleaseDC( hWnd, hDC );

    /* Free the least used font. */
    DeleteObject( fpFontInfo->hFont );
    
    /* Point to the least used slot. */
    fpFontInfo = fpFontLeastUsed;
  }

  /* Modify the data. */
  fpFontInfo->wFontNumber  = wFontNumber; 
  fpFontInfo->hFont        = hFont;
  fpFontInfo->dwTickCount  = GetTickCount(); 

  /* Unlock the font info. */
  GlobalUnlock( fpFontBuffer->hFontInfo );
  
  /* Unlock the font buffer. */
  GlobalUnlock( hFontBuffer );

  /* Success. */
  return( TRUE );
}