//-----------------------------------------------------------------------------
//  CBrowserViewImagesListBox::CreateIconL(
//                                      CFbsBitmap* aBitmap, TBool aShrinkIt )
//-----------------------------------------------------------------------------
//
CGulIcon* CBrowserViewImagesListBox::CreateIconL(
                                        CFbsBitmap* aBitmap, TBool aShrinkIt)
    {
    CGulIcon* icon = NULL;

    // create icon
    if(aShrinkIt)
        {
        CFbsBitmap* bmp = new(ELeave)CFbsBitmap;
        CleanupStack::PushL(bmp);
        User::LeaveIfError(bmp->Create(TSize(42,32), EColor16M));
    
        // create bitmap device
        CFbsBitmapDevice* dev = CFbsBitmapDevice::NewL(bmp);
        CleanupStack::PushL(dev);
    
        // create graphics context for bitmap device
        CGraphicsContext* ctx = NULL;
        User::LeaveIfError( dev->CreateContext(ctx) );
        CleanupStack::PushL(ctx);
    
        // calculate aspect ratio
        TSize targetSize = Fit(aBitmap->SizeInPixels(), bmp->SizeInPixels());
        // copy bitmap to temporary bitmap
        ctx->DrawBitmap(TRect(TPoint(0,0), targetSize), aBitmap, TRect(TPoint(0,0), aBitmap->SizeInPixels()));

        CleanupStack::PopAndDestroy(2);   // ctx, dev

        icon = CGulIcon::NewL(bmp); // bmp is owned, no mask used
        CleanupStack::Pop();  // bmp
        delete aBitmap;
        } 
    else 
        {
        icon = CGulIcon::NewL(aBitmap); // bitmap is owned, no mask used
        }

    return icon;
    }