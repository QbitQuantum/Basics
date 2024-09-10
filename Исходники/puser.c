APIERR MNetUserModalsSet(
	const TCHAR FAR	 * pszServer,
	UINT		   Level,
	BYTE FAR	 * pbBuffer,
	UINT		   cbBuffer,
	UINT		   ParmNum )
{
    UNREFERENCED( cbBuffer );

    if( ParmNum != PARMNUM_ALL )
    {
    	return ERROR_NOT_SUPPORTED;
    }

    return (APIERR)NetUserModalsSet( (TCHAR *)pszServer,
				     Level,
				     pbBuffer,
				     NULL );
}   // MNetUserModalsSet