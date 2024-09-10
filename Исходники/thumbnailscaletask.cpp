// ---------------------------------------------------------------------------
// CThumbnailScaleTask::StartL()
// ---------------------------------------------------------------------------
//
void CThumbnailScaleTask::StartL()
    {
    TN_DEBUG2( "CThumbnailScaleTask(0x%08x)::StartL()", this );
    OstTrace1( TRACE_NORMAL, CTHUMBNAILSCALETASK_STARTL, "CThumbnailScaleTask::StartL;this=%o", this );

    CThumbnailTask::StartL();

    if ( !iCrop )
        {
        TN_DEBUG2( "CThumbnailScaleTask(0x%08x)::StartL() - cropping OFF", this );
        OstTrace1( TRACE_NORMAL, DUP1_CTHUMBNAILSCALETASK_STARTL, "CThumbnailScaleTask::StartL - cropping OFF;this=%o", this );
    
        // target size at max, keep aspect ratio
        CalculateTargetSize();
        }
    else
        {
        TN_DEBUG2( "CThumbnailScaleTask(0x%08x)::StartL() - cropping ON", this );
        OstTrace1( TRACE_NORMAL, DUP2_CTHUMBNAILSCALETASK_STARTL, "CThumbnailScaleTask::StartL - cropping ON;this=%o", this );
    
        // exact target size, crop excess
        CalculateCropRectangle();
        }
    
    TN_DEBUG2( "CThumbnailScaleTask(0x%08x)::StartL() - sizes calculated", this );
    OstTrace1( TRACE_NORMAL, DUP3_CTHUMBNAILSCALETASK_STARTL, "CThumbnailScaleTask::StartL - sizes calculated;this=%o", this );
    
#ifdef _DEBUG
    aStart.UniversalTime();
#endif
    
    delete iScaledBitmap;
    iScaledBitmap = NULL;
    iScaledBitmap = new( ELeave )CFbsBitmap();
    
    TSize bitmapSize = iBitmap->SizeInPixels();
    
    if(bitmapSize.iHeight == iTargetSize.iHeight && bitmapSize.iWidth == iTargetSize.iWidth)
        {
        TN_DEBUG2( "CThumbnailScaleTask(0x%08x)::StartL() - no need for scaling", this);
        OstTrace1( TRACE_NORMAL, DUP4_CTHUMBNAILSCALETASK_STARTL, "CThumbnailScaleTask::StartL - no need for scaling;this=%o", this );
    
        // copy bitmap 1:1
        User::LeaveIfError( iScaledBitmap->Create( bitmapSize, iBitmap->DisplayMode() ));
        CFbsBitmapDevice* device = CFbsBitmapDevice::NewL(iScaledBitmap);
        CleanupStack::PushL(device);
        CFbsBitGc* gc = NULL;
        User::LeaveIfError(device->CreateContext(gc));
        CleanupStack::PushL(gc);
        gc->BitBlt(TPoint(0, 0), iBitmap);
        CleanupStack::PopAndDestroy(2, device); // gc
        
        TRAPD( err, StoreAndCompleteL());
        Complete( err );
        ResetMessageData();
        }
    else
        {
        TN_DEBUG2( "CThumbnailScaleTask(0x%08x)::StartL() - scaling", this);
        OstTrace1( TRACE_NORMAL, DUP5_CTHUMBNAILSCALETASK_STARTL, "CThumbnailScaleTask::StartL - scaling;this=%o", this );
        
        User::LeaveIfError( iScaledBitmap->Create( iTargetSize, iBitmap->DisplayMode() ));
        iServer.ScaleBitmapL( iStatus, * iBitmap, * iScaledBitmap, iCropRectangle );
        SetActive();
        }  
    
    TN_DEBUG2( "CThumbnailScaleTask(0x%08x)::StartL() end", this );
    OstTrace1( TRACE_NORMAL, DUP6_CTHUMBNAILSCALETASK_STARTL, "CThumbnailScaleTask::StartL - end;this=%o", this );
    }