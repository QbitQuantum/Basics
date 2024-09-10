/*************************************************************************
 *      @	[SHLWAPI.17]
 *
 * Write a DataBlock list to an IStream object.
 *
 * PARAMS
 *  lpStream  [I] IStream object to write the list to
 *  lpList    [I] List of items to write
 *
 * RETURNS
 *  Success: S_OK. The object is written to the stream.
 *  Failure: An HRESULT error code
 *
 * NOTES
 *  Ordinals 17,18,19,20,21 and 22 are related and together provide a compact
 *  list structure (a "DataBlock List"), which may be stored and retrieved from
 *  an IStream object.
 *
 *  The exposed API consists of:
 *
 *  - SHWriteDataBlockList() - Write a DataBlock list to a stream,
 *  - SHReadDataBlockList() - Read and create a list from a stream,
 *  - SHFreeDataBlockList() - Free a list,
 *  - SHAddDataBlock() - Insert a new item into a list,
 *  - SHRemoveDataBlock() - Remove an item from a list,
 *  - SHFindDataBlock() - Find an item in a list.
 *
 *  The DataBlock list is stored packed into a memory array. Each element has a
 *  size and an associated ID. Elements must be less than 64k if the list is
 *  to be subsequently read from a stream.
 *
 *  Elements are aligned on DWORD boundaries. If an elements data size is not
 *  a DWORD size multiple, the element is wrapped by inserting a surrounding
 *  element with an Id of 0xFFFFFFFF, and size sufficient to pad to a DWORD boundary.
 *
 *  These functions are slow for large objects and long lists.
 */
HRESULT WINAPI SHWriteDataBlockList(IStream* lpStream, LPDBLIST lpList)
{
  ULONG ulSize;
  HRESULT hRet = S_OK;

  TRACE("(%p,%p)\n", lpStream, lpList);

  if(lpList)
  {
    while (lpList->cbSize)
    {
      LPDATABLOCK_HEADER lpItem = lpList;

      if(lpList->dwSignature == CLIST_ID_CONTAINER)
        lpItem++;

      hRet = IStream_Write(lpStream,lpItem,lpItem->cbSize,&ulSize);
      if (FAILED(hRet))
        return hRet;

      if(lpItem->cbSize != ulSize)
        return STG_E_MEDIUMFULL;

      lpList = NextItem(lpList);
    }
  }

  if(SUCCEEDED(hRet))
  {
    ULONG ulDummy;
    ulSize = 0;

    /* Write a terminating list entry with zero size */
    hRet = IStream_Write(lpStream, &ulSize,sizeof(ulSize),&ulDummy);
  }

  return hRet;
}