void CRhodesAppView::DrawImage(CWindowGc& aGc,   
    const TRect& aRect) const   
    {   
    TSize bmpSizeInPixels( iBitmap->SizeInPixels() );   
    TInt xDelta = (aRect.Width() - bmpSizeInPixels.iWidth) / 2;   
    TInt yDelta = (aRect.Height() - bmpSizeInPixels.iHeight) / 2;   
    TPoint pos( xDelta, yDelta ); // displacement vector   
    pos += aRect.iTl; // bitmap top left corner position   
   
    // Drawing viewfinder image to bitmap   
    iFbsBitGc->BitBlt( pos, iBitmap, TRect( TPoint( 0, 0 ), bmpSizeInPixels ));   
   
    // Draws bitmap with indicators on the screen   
    TSize size( iOffScreenBitmap->SizeInPixels() );   
    aGc.BitBlt( TPoint(0,0), iOffScreenBitmap, TRect( TPoint(0,0), size ) );   
    }