/******************************************************************************
 *        AntiMoniker_Save
 ******************************************************************************/
static HRESULT WINAPI
AntiMonikerImpl_Save(IMoniker* iface,IStream* pStm,BOOL fClearDirty)
{
    static const DWORD constant = 1;
    /* data written by this function is only a DWORD constant set to 1 ! */
    return IStream_Write(pStm,&constant,sizeof(constant),NULL);
}