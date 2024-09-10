/******************************************************************************
 *        ItemMoniker_Save
 ******************************************************************************/
static HRESULT WINAPI ItemMonikerImpl_Save(IMoniker* iface, IStream* pStm, BOOL fClearDirty)
{
    ItemMonikerImpl *This = impl_from_IMoniker(iface);
    HRESULT res;
    CHAR *itemNameA,*itemDelimiterA;

    /* data written by this function are : 1) DWORD : size of item delimiter string ('\0' included ) */
    /*                                    2) String (type A): item delimiter string ('\0' included)          */
    /*                                    3) DWORD : size of item name string ('\0' included)       */
    /*                                    4) String (type A): item name string ('\0' included)               */

    DWORD nameLength = WideCharToMultiByte( CP_ACP, 0, This->itemName, -1, NULL, 0, NULL, NULL);
    DWORD delimiterLength = WideCharToMultiByte( CP_ACP, 0, This->itemDelimiter, -1, NULL, 0, NULL, NULL);
    itemNameA=HeapAlloc(GetProcessHeap(),0,nameLength);
    itemDelimiterA=HeapAlloc(GetProcessHeap(),0,delimiterLength);
    WideCharToMultiByte( CP_ACP, 0, This->itemName, -1, itemNameA, nameLength, NULL, NULL);
    WideCharToMultiByte( CP_ACP, 0, This->itemDelimiter, -1, itemDelimiterA, delimiterLength, NULL, NULL);

    TRACE("%p, %s\n", pStm, fClearDirty ? "TRUE" : "FALSE");

    res=IStream_Write(pStm,&delimiterLength,sizeof(DWORD),NULL);
    res=IStream_Write(pStm,itemDelimiterA,delimiterLength * sizeof(CHAR),NULL);
    res=IStream_Write(pStm,&nameLength,sizeof(DWORD),NULL);
    res=IStream_Write(pStm,itemNameA,nameLength * sizeof(CHAR),NULL);

    HeapFree(GetProcessHeap(), 0, itemNameA);
    HeapFree(GetProcessHeap(), 0, itemDelimiterA);

    return res;
}