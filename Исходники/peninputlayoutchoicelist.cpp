// CFepLayoutChoiceList::DrawBitmap
// Draw bitmap helper function.
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//
void CFepLayoutChoiceList::DrawBitmap(const TRect& aDestRect, const TRect& aSrcRect, 
                                      CFbsBitmap* aBmp, TBool aFast)
    {
    CFbsBitGc* gc = static_cast<CFbsBitGc*>(BitGc());
    if( aFast )
        {
         gc->BitBlt(aDestRect.iTl, aBmp, aSrcRect);
        }
    else
        {
        gc->DrawBitmap(aDestRect, aBmp, aSrcRect);
        }
    }