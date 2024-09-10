APIERR MNetAuditWrite(
	UINT		   Type,
	BYTE FAR	 * pbBuffer,
	UINT		   cbBuffer,
	TCHAR FAR	 * pszService,
	TCHAR FAR	 * pszReserved ) 
{
    return (APIERR)NetAuditWrite( (USHORT)Type,
				  (const TCHAR FAR *)pbBuffer,
				  (USHORT)cbBuffer,
				  pszService,
				  pszReserved );

}   // MNetAuditWrite