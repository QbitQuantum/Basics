// ---------------------------------------------------------------------------
// If aDevExt contains a valid friendly name, the friendly name will be displayed;
// Otherwise, if the given name from the parameter of a notifier request is valid,
// the given name will be displayed;
// Otherwise, If aDevExt contains a valid device name, the name will be displayed;
// Otherwise, the a name will be created by this function.
// ---------------------------------------------------------------------------
//
void TBTNotifUtil::GetDeviceUiNameL( TDes& aNameBuf, 
            const CBtDevExtension* aDevExt, 
            const TDesC& aNameInParam,
            const TBTDevAddr& aAddr)
    {
    CBtDevExtension* tempDev( NULL );
    TPtrC namePtr;
    if ( aDevExt && 
         aDevExt->Device().IsValidFriendlyName() && 
         aDevExt->Device().FriendlyName().Length() != 0 )
        {
        // We always use the friendly name regardless of 
        // the device-name of the device is available or not.
        namePtr.Set( aDevExt->Device().FriendlyName() );
        }
    else 
        {
        // this will take care of name formating. Either the
        // name from iNameInParam or the address will be
        // the alias:
        tempDev = CBtDevExtension::NewLC( aAddr, aNameInParam );      
        namePtr.Set( tempDev->Alias() );
        }
    // Make sure no overflow:
    if ( aNameBuf.MaxLength() < namePtr.Length() )
        {
        aNameBuf.Copy( namePtr.Left( aNameBuf.MaxLength() ) );
        }
    else
        {
        aNameBuf.Copy( namePtr );
        }
    if ( tempDev )
        {
        CleanupStack::PopAndDestroy( tempDev );
        }
    }