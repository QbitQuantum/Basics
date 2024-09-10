/******************************************************************************
 *		GetStringTypeA	[OLE2NLS.7]
 */
BOOL16 WINAPI GetStringType16(LCID locale,DWORD dwInfoType,LPCSTR src,
                              INT16 cchSrc,LPWORD chartype)
{
    return GetStringTypeExA(locale,dwInfoType,src,cchSrc,chartype);
}