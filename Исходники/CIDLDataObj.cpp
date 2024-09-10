HRESULT WINAPI SHCreateDataObject(PCIDLIST_ABSOLUTE pidlFolder, UINT cidl, PCUITEMID_CHILD_ARRAY apidl, IDataObject *pdtInner, REFIID riid, void **ppv)
{
    if (IsEqualIID(riid, IID_IDataObject))
    {
        return CIDLData_CreateFromIDArray(pidlFolder, cidl, apidl, (IDataObject **)ppv);
    }
    return E_FAIL;
}