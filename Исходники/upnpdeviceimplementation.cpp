// -----------------------------------------------------------------------------
// CUpnpDeviceImplementation::NewL
// -----------------------------------------------------------------------------
//
EXPORT_C CUpnpDeviceImplementation* CUpnpDeviceImplementation::NewL( 
        const TDesC8& aUri, 
        CUpnpDeviceDescriptionStore& aDescriptionStore,
        MUpnpDeviceDescriptionProvider& aProvider )
    {
    LOGS("CUpnpDevice:: CUpnpDevice::NewL( const TDesC& aFilename, TInt aIapId, TInt aHandle )" );

    HBufC8* descr = UpnpFileUtil::ReadFileL( aDescriptionStore.DescriptionFile() );
    if ( descr->Length()> KMaxDeviceDescriptionLenght )
        {
        delete descr;
        User::Leave( KErrTooBig );
        }
    CleanupStack::PushL( descr );

    CUpnpContentHandlersController* controller = CUpnpContentHandlersController::NewLC();

    CUpnpDeviceImplementation* deviceImpl = controller->ParseDeviceImplL( *descr );
    CleanupStack::PushL( deviceImpl );
    deviceImpl->ConstructL( aUri, aDescriptionStore, aProvider );
    CleanupStack::Pop( deviceImpl );

    CleanupStack::PopAndDestroy( controller );
    CleanupStack::PopAndDestroy( descr );

    return deviceImpl;
    }