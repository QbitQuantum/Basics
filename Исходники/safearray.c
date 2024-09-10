/*************************************************************************
 *		SafeArrayGetElement (OLEAUT32.25)
 *
 * Get an item from a SafeArray.
 *
 * PARAMS
 *  psa       [I] SafeArray to get from
 *  rgIndices [I] Indices to get from
 *  pvData    [O] Destination for data
 *
 * RETURNS
 *  Success: S_OK. The item data is returned in pvData.
 *  Failure: An HRESULT error code indicating the error.
 *
 * NOTES
 * See SafeArray.
 */
HRESULT WINAPI SafeArrayGetElement(SAFEARRAY *psa, LONG *rgIndices, void *pvData)
{
  HRESULT hRet;

  TRACE("(%p,%p,%p)\n", psa, rgIndices, pvData);
    
  if (!psa || !rgIndices || !pvData)
    return E_INVALIDARG;

  hRet = SafeArrayLock(psa);

  if (SUCCEEDED(hRet))
  {
    PVOID lpvSrc;

    hRet = SafeArrayPtrOfIndex(psa, rgIndices, &lpvSrc);

    if (SUCCEEDED(hRet))
    {
      if (psa->fFeatures & FADF_VARIANT)
      {
        VARIANT* lpVariant = lpvSrc;
        VARIANT* lpDest = pvData;

        /* The original content of pvData is ignored. */
        V_VT(lpDest) = VT_EMPTY;
        hRet = VariantCopy(lpDest, lpVariant);
	if (FAILED(hRet)) FIXME("VariantCopy failed with 0x%x\n", hRet);
      }
      else if (psa->fFeatures & FADF_BSTR)
      {
        BSTR* lpBstr = lpvSrc;
        BSTR* lpDest = pvData;

        if (*lpBstr)
        {
          *lpDest = SysAllocStringByteLen((char*)*lpBstr, SysStringByteLen(*lpBstr));
          if (!*lpBstr)
            hRet = E_OUTOFMEMORY;
        }
        else
          *lpDest = NULL;
      }
      else if (psa->fFeatures & (FADF_UNKNOWN|FADF_DISPATCH))
      {
        IUnknown **src_unk = lpvSrc;
        IUnknown **dest_unk = pvData;

        if (*src_unk)
          IUnknown_AddRef(*src_unk);
        *dest_unk = *src_unk;
      }
      else if (psa->fFeatures & FADF_RECORD)
      {
        IRecordInfo *record;

        SafeArrayGetRecordInfo(psa, &record);
        hRet = IRecordInfo_RecordCopy(record, lpvSrc, pvData);
        IRecordInfo_Release(record);
      }
      else
        /* Copy the data over */
        memcpy(pvData, lpvSrc, psa->cbElements);
    }
    SafeArrayUnlock(psa);
  }
  return hRet;
}