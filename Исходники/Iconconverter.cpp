// ============================================================================
// CIconConverter::DoIconStoreL()
// Store icon and mask files
//
// @since 3.1
// ============================================================================
void CIconConverter::DoIconStoreL()
    {
    // Store the icon and its mask in temporary files until we are ready
    // to create the final icon

    // Icon is stored at index n, mask at index n+1
    TInt iconIndex = iCurrentSizeIndex * 2;
    TFileName iconFile = *iTempPath;
    GetTempIconName( iconIndex++, iconFile );

    TFileName maskFile = *iTempPath;
    GetTempIconName( iconIndex, maskFile );

    // invert the masks before saving

    CFbsBitmapDevice* device = CFbsBitmapDevice::NewL( iTempBitmapMask );
    CleanupStack::PushL( device );

    CFbsBitGc* gc;
    User::LeaveIfError( device->CreateContext( gc ) );
    gc->SetDrawMode( CGraphicsContext::EDrawModeNOTSCREEN );
    gc->Clear();

    delete gc;
    CleanupStack::PopAndDestroy( device );

    // save the bitmaps
    User::LeaveIfError( iTempBitmap->Save( iconFile ) );
    User::LeaveIfError( iTempBitmapMask->Save( maskFile ) );

    if ( ++iCurrentSizeIndex < iIconSizes->Count() )
        {
        // do the next icon size
        DoIconScalingL();
        }
    else
        {
        DoCreateFinalIconL();
        }

    }