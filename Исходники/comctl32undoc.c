/**************************************************************************
 * Str_SetPtrAtoW [internal]
 *
 * Converts a multi byte string to a unicode string.
 * If the pointer to the destination buffer is NULL a buffer is allocated.
 * If the destination buffer is too small to keep the converted multi byte
 * string the destination buffer is reallocated. If the source pointer is
 * NULL, the destination buffer is freed.
 *
 * PARAMS
 *     lppDest [I/O] pointer to a pointer to the destination buffer
 *     lpSrc   [I] pointer to a multi byte string
 *
 * RETURNS
 *     TRUE: conversion successful
 *     FALSE: error
 */
BOOL Str_SetPtrAtoW (LPWSTR *lppDest, LPCSTR lpSrc)
{
    TRACE("(%p %s)\n", lppDest, lpSrc);

    if (lpSrc) {
	INT len = MultiByteToWideChar(CP_ACP,0,lpSrc,-1,NULL,0);
	LPWSTR ptr = ReAlloc (*lppDest, len*sizeof(WCHAR));

	if (!ptr)
	    return FALSE;
	MultiByteToWideChar(CP_ACP,0,lpSrc,-1,ptr,len);
	*lppDest = ptr;
    }
    else {
        Free (*lppDest);
        *lppDest = NULL;
    }

    return TRUE;
}