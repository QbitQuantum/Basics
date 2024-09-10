APIERR MNetMessageBufferSend(
	const TCHAR FAR	 * pszServer,
	TCHAR FAR	 * pszRecipient,
	BYTE FAR	 * pbBuffer,
	UINT		   cbBuffer ) 
{
    return NetMessageBufferSend( pszServer,
				 pszRecipient,
				 pbBuffer,
				 cbBuffer );

}   // MNetMessageBufferSend