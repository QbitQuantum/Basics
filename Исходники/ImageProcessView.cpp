void CImageProcessView::DrawMeOffScreen(CDC *pdc)
{
   //
   // First, we have to allocate a bitmap that is compatible with the
   // screen that we will draw in.  We determine how big it needs to
   // be right here.
   //

   // Get an enclosing rectangle
   CRect rcBounds;
   CSize size = GetTotalSize();
   rcBounds.SetRect(0, 0, size.cx, size.cy);

   // And convert bounds to device units. 
   // This is in case we happened to be using inches or something like that.
   pdc->LPtoDP(&rcBounds) ;

   // Create a Display Context that is compatible with the screen.
   CDC dcMem;
   dcMem.CreateCompatibleDC(pdc) ;

   // Create a really compatible bitmap.
   CBitmap bitOff;
   bitOff.CreateCompatibleBitmap(pdc, rcBounds.Width(), rcBounds.Height());

   // Select the bitmap into the memory DC.
   CBitmap* pOldBitmap = dcMem.SelectObject(&bitOff) ;

   // Save the memory DC state, since DrawMe might change it.
   int iSavedDC = dcMem.SaveDC();

   // Draw our control on the memory DC.
   DrawMe(&dcMem) ;

   // Restore the DC, since DrawMe might have changed mapping modes.
   dcMem.RestoreDC(iSavedDC) ;

   // We don't know what mapping mode pdc is using.
   // BitBlt uses logical coordinates.
   // Easiest thing is to change to MM_TEXT.
   pdc->SetMapMode(MM_TEXT) ;
   pdc->SetWindowOrg(0,0) ;
   pdc->SetViewportOrg(0,0) ;

   // Block transfer the memory device context to the screen.
   pdc->BitBlt( rcBounds.left,
                rcBounds.top,
                rcBounds.Width(),
                rcBounds.Height(),
                &dcMem,
                0,
                0,
                SRCCOPY) ;

   // Clean up.
   dcMem.SelectObject(pOldBitmap) ;
}