//
//	Writes the specified GUID structure into the specified memory buffer as 0-terminated string.
//
ULONG GuidToBuffer(
	GUID*	pGuid,
	LPTSTR	pBuffer,
	BOOL	bQuoted
	)
{
	LPTSTR	TempStr;

	if (bQuoted)
		TempStr = szGuidStrTemp1;
	else
		TempStr = szGuidStrTemp2;

	return(wsprintf(pBuffer, TempStr, htonL(pGuid->Data1),	htonS(pGuid->Data2), htonS(pGuid->Data3), htonS(*(USHORT*)&pGuid->Data4[0]), 
		htonL(*(ULONG*)&pGuid->Data4[2]), htonS(*(USHORT*)&pGuid->Data4[6])));
}