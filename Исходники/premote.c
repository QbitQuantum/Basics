APIERR MNetRemoteTOD(
	const TCHAR FAR	 * pszServer,
	BYTE FAR	** ppbBuffer )
{
    return (APIERR)NetRemoteTOD( (TCHAR *)pszServer,
    				 ppbBuffer );

}   // MNetRemoteTOD