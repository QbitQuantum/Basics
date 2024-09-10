mDNSBool
LsaSetSecret( const char * inDomain, const char * inKey, const char * inSecret )
{
    size_t					inDomainLength;
    size_t					inKeyLength;
    char					domain[ 1024 ];
    char					key[ 1024 ];
    LSA_OBJECT_ATTRIBUTES	attrs;
    LSA_HANDLE				handle = NULL;
    NTSTATUS				res;
    LSA_UNICODE_STRING		lucZoneName;
    LSA_UNICODE_STRING		lucKeyName;
    LSA_UNICODE_STRING		lucSecretName;
    BOOL					ok = TRUE;
    OSStatus				err;

    require_action( inDomain != NULL, exit, ok = FALSE );
    require_action( inKey != NULL, exit, ok = FALSE );
    require_action( inSecret != NULL, exit, ok = FALSE );

    // If there isn't a trailing dot, add one because the mDNSResponder
    // presents names with the trailing dot.

    ZeroMemory( domain, sizeof( domain ) );
    inDomainLength = strlen( inDomain );
    require_action( inDomainLength > 0, exit, ok = FALSE );
    err = strcpy_s( domain, sizeof( domain ) - 2, inDomain );
    require_action( !err, exit, ok = FALSE );

    if ( domain[ inDomainLength - 1 ] != '.' )
    {
        domain[ inDomainLength++ ] = '.';
        domain[ inDomainLength ] = '\0';
    }

    // <rdar://problem/4192119>
    //
    // Prepend "$" to the key name, so that there will
    // be no conflict between the zone name and the key
    // name

    ZeroMemory( key, sizeof( key ) );
    inKeyLength = strlen( inKey );
    require_action( inKeyLength > 0 , exit, ok = FALSE );
    key[ 0 ] = '$';
    err = strcpy_s( key + 1, sizeof( key ) - 3, inKey );
    require_action( !err, exit, ok = FALSE );
    inKeyLength++;

    if ( key[ inKeyLength - 1 ] != '.' )
    {
        key[ inKeyLength++ ] = '.';
        key[ inKeyLength ] = '\0';
    }

    // attrs are reserved, so initialize to zeroes.

    ZeroMemory( &attrs, sizeof( attrs ) );

    // Get a handle to the Policy object on the local system

    res = LsaOpenPolicy( NULL, &attrs, POLICY_ALL_ACCESS, &handle );
    err = translate_errno( res == 0, LsaNtStatusToWinError( res ), kUnknownErr );
    require_noerr( err, exit );

    // Intializing PLSA_UNICODE_STRING structures

    err = MakeLsaStringFromUTF8String( &lucZoneName, domain );
    require_noerr( err, exit );

    err = MakeLsaStringFromUTF8String( &lucKeyName, key );
    require_noerr( err, exit );

    err = MakeLsaStringFromUTF8String( &lucSecretName, inSecret );
    require_noerr( err, exit );

    // Store the private data.

    res = LsaStorePrivateData( handle, &lucZoneName, &lucKeyName );
    err = translate_errno( res == 0, LsaNtStatusToWinError( res ), kUnknownErr );
    require_noerr( err, exit );

    res = LsaStorePrivateData( handle, &lucKeyName, &lucSecretName );
    err = translate_errno( res == 0, LsaNtStatusToWinError( res ), kUnknownErr );
    require_noerr( err, exit );

exit:

    if ( handle )
    {
        LsaClose( handle );
        handle = NULL;
    }

    return ok;
}