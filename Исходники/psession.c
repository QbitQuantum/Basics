APIERR MNetSessionDel(
        const TCHAR FAR  * pszServer,
        const TCHAR FAR  * pszClientName,
        const TCHAR FAR  * pszUserName )
{
    return (APIERR)NetSessionDel( (TCHAR *)pszServer,
                                  (TCHAR *)pszClientName,
                                  (TCHAR *)pszUserName );

}   // MNetSessionDel