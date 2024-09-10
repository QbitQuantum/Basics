// ---------------------------------------------------------------------------
// CThumbnailAudioProvider::GetThumbnailL()
// Provides the thumbnail image
// ---------------------------------------------------------------------------
//
void CThumbnailAudioProvider::GetThumbnailL( RFs& aFs, RFile64& aFile, const
    TDataType& aMimeType  , const CThumbnailManager::TThumbnailFlags aFlags,
    const TDisplayMode /*aDisplayMode*/, const CThumbnailManager::TThumbnailQualityPreference /*aQualityPreference*/  )
    {   
    TN_DEBUG1( "CThumbnailAudioProvider::GetThumbnailL() - rfile " );
    OstTrace0( TRACE_NORMAL, CTHUMBNAILAUDIOPROVIDER_GETTHUMBNAILL, "CThumbnailAudioProvider::GetThumbnailL - rfile" );
    CMetaDataUtility* metaDataUtil = CMetaDataUtility::NewL();
    CleanupStack::PushL( metaDataUtil );
    
    RArray<TMetaDataFieldId> wantedFields;
    CleanupClosePushL(wantedFields);
    wantedFields.AppendL(EMetaDataJpeg);
    
    metaDataUtil->OpenFileL(aFile, wantedFields, aMimeType.Des8());
    const CMetaDataFieldContainer& metaCont = metaDataUtil->MetaDataFieldsL();
    TPtrC8 ptr = metaCont.Field8( EMetaDataJpeg );
    HBufC8* data = ptr.AllocL();
    
    CleanupStack::PopAndDestroy(&wantedFields);
    CleanupStack::PopAndDestroy(metaDataUtil);
    CleanupStack::PushL( data );
    
    if(data->Length() == 0)
      {
      User::Leave( KErrNotFound );            
      }
    
    if ( !iImageDecoderv3 )
        {
        iImageDecoderv3 = new( ELeave )CThumbnailImageDecoderv3( aFs );
        }
    
    iMimeType = TDataType(KJpegMime);
    iFlags = aFlags;
	//set default mode displaymode from global constants
    iDisplayMode = KStoreDisplayMode;
    TRAPD( err, iImageDecoderv3->CreateL( data, *iObserver, iFlags, iMimeType, iTargetSize ) );
    if (err == KErrNone)
        {
        CleanupStack::Pop( data );
        }
    else
        {
        // this is because data buffer is already released in CreateDecoderL
        // and we must prevent automatic PopAndDestroy
        CleanupStack::Pop( data );
        User::Leave(err);
        } 
    
    iOriginalSize = iImageDecoderv3->OriginalSize();
    iImageDecoderv3->DecodeL( iDisplayMode );
    }