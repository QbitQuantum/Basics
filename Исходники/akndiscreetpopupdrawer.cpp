// ---------------------------------------------------------------------------
// CAknDiscreetPopupDrawer::CreatePopupBitmap
// ---------------------------------------------------------------------------
//
void CAknDiscreetPopupDrawer::CreatePopupBitmapL( const TRect& aRect )
    {
    delete iPopupBitmap;
    iPopupBitmap = NULL;
    
    // create a bitmap to draw to
    CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap;
    CleanupStack::PushL( bitmap );

    bitmap->Create( 
        aRect.Size(), CCoeEnv::Static()->ScreenDevice()->DisplayMode() );
    CFbsBitGc* fbsBitGc = CFbsBitGc::NewL();
    CleanupStack::PushL( fbsBitGc );
    CFbsBitmapDevice* bmpDevice = CFbsBitmapDevice::NewL( bitmap );
    CleanupStack::PushL( bmpDevice );
    fbsBitGc->Activate( bmpDevice );

    // draw background of the popup	
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::DrawFrame( skin, *fbsBitGc, aRect, aRect, 
        KAknsIIDQsnFrPopupPreview, KAknsIIDDefault, KAknsDrawParamDefault );
    
    // Draw the texts
    TRgb textColor( EikonEnv()->ControlColor( EColorControlText, *iControl ) );
    if ( iAction )
        {
        fbsBitGc->SetUnderlineStyle( EUnderlineOn );
        AknsUtils::GetCachedColor( skin,
                                   textColor,
                                   KAknsIIDQsnHighlightColors,
                                   EAknsCIQsnHighlightColorsCG3 );
        }
    else
        {
        AknsUtils::GetCachedColor( skin,
                                   textColor,
                                   KAknsIIDQsnTextColors,
                                   EAknsCIQsnTextColorsCG55 );
        }
    fbsBitGc->SetPenColor( textColor );
    DrawTexts( fbsBitGc );
    fbsBitGc->SetUnderlineStyle( EUnderlineOff );

    // draw the icon
    if ( iIcon && iIcon->Bitmap() && iIcon->Mask() )
        {
        fbsBitGc->BitBltMasked( iIconRect.iTl,
                                iIcon->Bitmap(), 
                                iIcon->Bitmap()->SizeInPixels(), 
                                iIcon->Mask(), 
                                EFalse );

        }
    else if( iIcon && iIcon->Bitmap() )
        {
        fbsBitGc->BitBlt( iIconRect.iTl, iIcon->Bitmap() );
        }

    CleanupStack::PopAndDestroy( bmpDevice );
    CleanupStack::PopAndDestroy( fbsBitGc );
    CleanupStack::Pop( bitmap );
    
    iPopupBitmap = bitmap;
    }