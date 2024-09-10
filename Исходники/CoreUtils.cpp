////////////////////////////////////////////////////////////////////
// ConvertBlobToVarVector
//
//  Takes a PROPVARIANT BLOB or pclipdata and converts it to VARIANT SAFEARRAY 
//  which can be treated by VB as vector (1-dim) Byte Array.
//
STDAPI ConvertBinaryToVarVector(PROPVARIANT *pVarBlob, VARIANT *pVarByteArray)
{
    HRESULT hr = S_FALSE;
    SAFEARRAY* pSA;
    DWORD dwSize;

    if ( ( pVarBlob == NULL ) || (pVarBlob->vt != VT_BLOB) && 
		 ( pVarBlob->vt != VT_CF ) || ( pVarByteArray == NULL ) )
        return E_UNEXPECTED;

 // Identify the size
    if ( pVarBlob->vt == VT_BLOB ) 
		dwSize = pVarBlob->blob.cbSize;
	else
		dwSize = pVarBlob->pclipdata->cbSize;

    if ((dwSize) && (dwSize < 0x800000))
    {
     // Create a vector array the size of the blob or clipdata...
        pSA = SafeArrayCreateVector(VT_UI1, 0, dwSize);
        if ( pSA != NULL )
        {
         // Copy the data over to the vector
            BYTE *pByte = NULL;
            hr = SafeArrayAccessData( pSA, (void**)&pByte );
            if ( SUCCEEDED(hr) )
            {
                SEH_TRY
				if ( pVarBlob->vt == VT_BLOB )
					memcpy( pByte, (BYTE*)(pVarBlob->blob.pBlobData), dwSize );
				else
					memcpy( pByte, (BYTE*)(pVarBlob->pclipdata->pClipData), dwSize );
                SEH_EXCEPT(hr)
                SafeArrayUnaccessData( pSA );
            }
        }