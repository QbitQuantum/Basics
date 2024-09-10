// -----------------------------------------------------------------------------
// CUpnpDeviceLibraryElement::AddInfoFromNotificationTypeHeaderL
//
// Supported NT (Notification Type) messages:
// "uuid:"                         (length: 5 )
// "upnp:rootdevice"               (length: 15)
// "urn:schemas-upnp-org:device:"  (length: 28)
// "urn:schemas-upnp-org:service:" (length: 29)
// -----------------------------------------------------------------------------
//
TBool CUpnpDeviceLibraryElement::AddInfoFromNotificationTypeHeaderL(
    CUpnpSsdpMessage* aMessage )
    {
    TPtrC8 nt = aMessage->St( );

    if ( nt.Length( ) == 0 )
        {
        nt.Set( aMessage->Nt( ) );
        }

    if ( HasPrefix( nt, KUPnPUuid ) )
        {
        // an uuid advertisement
        return ETrue;
        }

    if ( iDeviceType->Length( ) == 0 )
        {
        if ( nt == KUPnPRootDevice )
            {
            // a root device advertisement
            SetDeviceTypeL( nt );
            return ETrue;
            }

        if ( HasPrefix( nt, KUPnPDeviceSchema ) )
            {
            // a device advertisement
            SetDeviceTypeL( nt );
            return ETrue;
            }
        }

    if ( HasPrefix( nt, KUPnPServiceSchema ) )
        {
        // a service advertisement
        AddServiceTypeL( nt );
        return ETrue;
        }

    return EFalse;
    }