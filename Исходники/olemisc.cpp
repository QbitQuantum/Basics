HGLOBAL AFXAPI _AfxOleGetObjectDescriptorData(
	CLSID       clsid,
	DWORD       dwDrawAspect,
	SIZEL       sizel,
	POINTL      pointl,
	DWORD       dwStatus,
	LPCOLESTR   lpszFullUserTypeName,
	LPCOLESTR   lpszSrcOfCopy)
{
	HGLOBAL     hMem = NULL;
	LPOBJECTDESCRIPTOR lpOD;
	DWORD       dwObjectDescSize, dwFullUserTypeNameLen, dwSrcOfCopyLen;

	// Get the length of Full User Type Name; Add 1 for the null terminator
	dwFullUserTypeNameLen = lpszFullUserTypeName ?
		ocslen(lpszFullUserTypeName)+1 : 0;

	// Get the Source of Copy string and it's length;
	//  Add 1 for the null terminator
	if (lpszSrcOfCopy && lpszSrcOfCopy[0] != '\0')
	   dwSrcOfCopyLen = ocslen(lpszSrcOfCopy)+1;
	else
	{
	   // No src moniker so use user type name as source string.
	   lpszSrcOfCopy =  lpszFullUserTypeName;
	   dwSrcOfCopyLen = dwFullUserTypeNameLen;
	}

	// Allocate space for OBJECTDESCRIPTOR and the additional string data
	dwObjectDescSize = sizeof(OBJECTDESCRIPTOR);
	hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT,
	   dwObjectDescSize + (dwFullUserTypeNameLen + dwSrcOfCopyLen) *
		sizeof(OLECHAR));
	if (!hMem)
		return NULL;

	lpOD = (LPOBJECTDESCRIPTOR)GlobalLock(hMem);

	// Set the FullUserTypeName offset and copy the string
	if (lpszFullUserTypeName)
	{
		lpOD->dwFullUserTypeName = dwObjectDescSize;
		ocscpy((LPOLESTR)((LPBYTE)lpOD+lpOD->dwFullUserTypeName), lpszFullUserTypeName);
	}
	else
		lpOD->dwFullUserTypeName = 0;  // zero offset indicates that string is not present

	// Set the SrcOfCopy offset and copy the string
	if (lpszSrcOfCopy)
	{
		lpOD->dwSrcOfCopy = dwObjectDescSize + dwFullUserTypeNameLen * sizeof(OLECHAR);
		ocscpy((LPOLESTR)((LPBYTE)lpOD+lpOD->dwSrcOfCopy), lpszSrcOfCopy);
	}
	else
		lpOD->dwSrcOfCopy = 0;  // zero offset indicates that string is not present

	// Initialize the rest of the OBJECTDESCRIPTOR
	lpOD->cbSize       = dwObjectDescSize +
		(dwFullUserTypeNameLen + dwSrcOfCopyLen) * sizeof(OLECHAR);
	lpOD->clsid        = clsid;
	lpOD->dwDrawAspect = dwDrawAspect;
	lpOD->sizel        = sizel;
	lpOD->pointl       = pointl;
	lpOD->dwStatus     = dwStatus;

	GlobalUnlock(hMem);
	return hMem;
}