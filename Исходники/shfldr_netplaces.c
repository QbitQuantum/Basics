/**************************************************************************
*  ISF_NetworkPlaces_fnGetAttributesOf
*/
static HRESULT WINAPI ISF_NetworkPlaces_fnGetAttributesOf (IShellFolder2 * iface,
               UINT cidl, LPCITEMIDLIST * apidl, DWORD * rgfInOut)
{
    IGenericSFImpl *This = impl_from_IShellFolder2(iface);
    HRESULT hr = S_OK;

    TRACE ("(%p)->(cidl=%d apidl=%p mask=%p (0x%08x))\n", This,
            cidl, apidl, rgfInOut, rgfInOut ? *rgfInOut : 0);

    if (!rgfInOut)
        return E_INVALIDARG;
    if (cidl && !apidl)
        return E_INVALIDARG;

    if (*rgfInOut == 0)
        *rgfInOut = ~0;

    if (cidl == 0)
    {
        IShellFolder *psfParent = NULL;
        LPCITEMIDLIST rpidl = NULL;

        hr = SHBindToParent(This->pidlRoot, &IID_IShellFolder, (void**)&psfParent, &rpidl);
        if(SUCCEEDED(hr))
        {
            SHELL32_GetItemAttributes (psfParent, rpidl, rgfInOut);
            IShellFolder_Release(psfParent);
        }
    }
    else
    {
        while (cidl > 0 && *apidl)
        {
            pdump (*apidl);
            SHELL32_GetItemAttributes ((IShellFolder *)&This->IShellFolder2_iface, *apidl, rgfInOut);
            apidl++;
            cidl--;
        }
    }

    /* make sure SFGAO_VALIDATE is cleared, some apps depend on that */
    *rgfInOut &= ~SFGAO_VALIDATE;

    TRACE ("-- result=0x%08x\n", *rgfInOut);
    return hr;
}