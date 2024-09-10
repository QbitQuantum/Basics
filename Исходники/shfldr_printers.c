/************************************************************************
 *    IPF_Printers_Initialize
 *
 */
static HRESULT WINAPI IPF_Printers_Initialize (
               IPersistFolder2 * iface, LPCITEMIDLIST pidl)
{
    _ICOM_THIS_From_IPersistFolder2 (IGenericSFImpl, iface);
    if (This->pidlRoot)
        SHFree((LPVOID)This->pidlRoot);

    This->pidlRoot = ILClone(pidl);
    return S_OK;
}