APIERR MNetGetDCName(
 	 const TCHAR FAR	 * pszServer,
    const TCHAR FAR	 * pszDomain,
	 BYTE FAR	** ppbBuffer )
{
    APIERR err = 0 ;

    err = (APIERR) NetGetDCName( (TCHAR *)pszServer,
    		                        (TCHAR *)pszDomain,
				                     ppbBuffer );
    return err ;

}   // MNetGetDCName