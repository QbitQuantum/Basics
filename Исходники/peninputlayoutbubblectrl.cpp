EXPORT_C void CBubbleCtrl::Draw()
    {
    if(!AbleToDraw() || iFreeze ) //|| !iShowing )
	    {
	    return;
	    }
    
    CFbsBitGc* gc = static_cast<CFbsBitGc*>(BitGc());
    
    //mask bitmaps
  	DrawOpaqueMaskBackground();  
  	
    TRect rect = Rect();        
    TRect innerRect = rect;
    
    if ( ( iLeftDiff == 0 ) && ( iTopDiff == 0 )
         && ( iRightDiff == 0 ) && ( iBottomDiff == 0 ) )
        {
        innerRect.Shrink( KShrinkSize, 0 );
        }
    else
        {
        innerRect.iTl.iX = innerRect.iTl.iX + iLeftDiff;
        innerRect.iTl.iY = innerRect.iTl.iY + iTopDiff;
        innerRect.iBr.iX = innerRect.iBr.iX - iRightDiff;
        innerRect.iBr.iY = innerRect.iBr.iY - iBottomDiff;
        
        }
    
    // ----- draw bitmaps -----
    gc->Activate( BitmapDevice() );                
    //gc->Clear(rect);
    		
	// Draw background
	if ( iBgSkinId.iMajor )
	    {
    	AknsDrawUtils::DrawFrame( AknsUtils::SkinInstance(), 
                         *gc,
                         rect,
                         innerRect,
                         iBgSkinId,
                         KAknsIIDDefault ); 	        
	    }
	else if( iFirstBmpId.iMajor && iMiddleBmpId.iMajor && iLastBmpId.iMajor )
		{
		AknPenInputDrawUtils::Draw3PiecesFrame( AknsUtils::SkinInstance(),
						 *gc,
						 rect,
						 innerRect,
						 iFirstBmpId,
						 iMiddleBmpId,
						 iLastBmpId);	
		}
	else
	    {
	    DrawBackground();    
	    }
                     
    if ( iForgroundBmp )
        {
        if( iForgroundBmp->SizeInPixels() != innerRect.Size() )
        	{
        	AknIconUtils::SetSize( iForgroundBmp, innerRect.Size(), EAspectRatioNotPreserved );
        	}
        	
    	TRect srcRect( TPoint( 0, 0 ), iForgroundBmp->SizeInPixels() );
    	
    	if( iForgroundBmpMask )
    		{
            if( iForgroundBmpMask->SizeInPixels() != innerRect.Size() )
            	{
            	AknIconUtils::SetSize( iForgroundBmpMask, innerRect.Size(), EAspectRatioNotPreserved);
            	}
            	        

    		gc->BitBltMasked( innerRect.iTl, 
    						  iForgroundBmp, 
    						  srcRect,
    						  iForgroundBmpMask,
    						  EFalse);
    		}
        else
            {
    		gc->BitBlt( innerRect.iTl,
    					iForgroundBmp,
    					srcRect );
            }            
        }
        
    if ( iText )
        {
        gc->SetBrushStyle( CGraphicsContext::ENullBrush );
        TAknLayoutText textLayout;
        textLayout.LayoutText(Rect(), iTextFormat);
        TRgb color( KRgbBlack );  // sane default for nonskinned case
	    if ( AknsUtils::AvkonSkinEnabled() )
	        {
	        AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
	                               color, KAknsIIDQsnTextColors, iTextColorIndex );
	        }
	     textLayout.DrawText(*gc, *iText, EFalse, color);
        }
    }