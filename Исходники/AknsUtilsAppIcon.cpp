EXPORT_C TInt AknsUtils::GetAppIcon(
    MAknsSkinInstance* aInstance, TUid aAppUid, TSize aSize,
    CApaMaskedBitmap& aAppBitmap )
    {
    AKNS_TRACE_OBSOLETE("AknsUtils::GetAppIcon (4 param)");

    __ASSERT_DEBUG( aAppBitmap.Mask(),
        AKNS_DEBUG_PANIC( EAknsDPanicInvalidParameter ) );

    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* mask = NULL;

    TInt ret = KErrNone;
    TBool configuredIcon = EFalse;

    if ( !configuredIcon )
        {
        ret = GetAppIconFromSkin( aInstance, aAppUid, aSize, bitmap, mask );
        if( ret == KErrNone )
            {
            if( bitmap && mask && bitmap->Handle() && mask->Handle() )
                {
                ret = aAppBitmap.Duplicate( bitmap->Handle() );
                ret |= aAppBitmap.Mask()->Duplicate( mask->Handle() );
                delete bitmap;
                delete mask;
                return ret;
                }
            else
                {
                // Delete bitmaps and proceed
                delete bitmap;
                bitmap = NULL; 
                delete mask;
                mask = NULL; 
                }
            }
        }

    RApaLsSession lsSession;
    ret = lsSession.Connect();
    if( ret == KErrNone )
        {
        ret = lsSession.GetAppIcon( aAppUid, aSize, aAppBitmap );
        lsSession.Close();
        if(ret == KErrNone) //icon case
        	AknInternalIconUtils::SetAppIcon(bitmap); //icon case
        }

    return ret;
    } //lint !e1746 GetAppIcon syntax