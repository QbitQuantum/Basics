// -----------------------------------------------------------------------------
// CUpnpDevice::DescriptionUrlPath
// Return description URL path.
// -----------------------------------------------------------------------------
//
EXPORT_C const TPtrC8 CUpnpDevice::DescriptionUrlPath() const
    {

    const TDesC8& url = DescriptionUrl();

    if ( url.Length()> KHttp().Length() )
        {
        TPtrC8 addrAndPath = url.Right( url.Length() - KHttp().Length() );

        TInt index = addrAndPath.Find( KSlash8() );

        if ( index != KErrNotFound )
            {
            TPtrC8 addr = addrAndPath.Right( addrAndPath.Length() - index );
            return addr;
            }
        }
    return TPtrC8( KNullDesC8 );
    }