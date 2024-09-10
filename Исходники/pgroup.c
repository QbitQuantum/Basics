APIERR MNetGroupSetUsers(
	const TCHAR FAR	 * pszServer,
	const TCHAR FAR	 * pszGroupName,
	UINT		   Level,
	BYTE FAR	 * pbBuffer,
	UINT		   cbBuffer,
	UINT		   cEntries ) 
{
    return NetGroupSetUsers( pszServer,
			     pszGroupName,
			     Level,
			     pbBuffer,
			     cbBuffer,
			     cEntries );

}   // MNetGroupSetUsers