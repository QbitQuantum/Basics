/**************************************************************************
 * WNetCachePassword [MPR.@]  Saves password in cache
 *
 * NOTES
 *	Only the parameter count is verified
 *
 *	---- everything below this line might be wrong (js) -----
 * RETURNS
 *    Success: WN_SUCCESS
 *    Failure: WN_ACCESS_DENIED, WN_BAD_PASSWORD, WN_BADVALUE, WN_NET_ERROR,
 *             WN_NOT_SUPPORTED, WN_OUT_OF_MEMORY
 */
DWORD WINAPI WNetCachePassword(
    LPSTR pbResource, /* [in] Name of workgroup, computer, or resource */
    WORD cbResource,  /* [in] Size of name */
    LPSTR pbPassword, /* [in] Buffer containing password */
    WORD cbPassword,  /* [in] Size of password */
    BYTE nType,       /* [in] Type of password to cache */
    WORD x)

{
    HKEY hkey;
    DWORD r;
    LPSTR valname;

    WARN( "(%p(%s), %d, %p(%s), %d, %d, 0x%08x): totally insecure\n",
           pbResource, debugstr_a(pbResource), cbResource,
	   pbPassword, debugstr_a(pbPassword), cbPassword,
	   nType, x );

    /* @@ Wine registry key: HKCU\Software\Wine\Wine\Mpr */
    r = RegCreateKeyA( HKEY_CURRENT_USER, mpr_key, &hkey );
    if( r )
        return WN_ACCESS_DENIED;

    valname = MPR_GetValueName( pbResource, cbResource, nType );
    if( valname )
    {
        r = RegSetValueExA( hkey, valname, 0, REG_BINARY, 
                            (LPBYTE)pbPassword, cbPassword );
        if( r )
            r = WN_CANCEL;
        else
            r = WN_SUCCESS;
        HeapFree( GetProcessHeap(), 0, valname );
    }
    else
        r = WN_OUT_OF_MEMORY;

    RegCloseKey( hkey );

    return r;
}