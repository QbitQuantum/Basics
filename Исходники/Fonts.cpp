/**************************************************************************
*  CFontsFolder::GetAttributesOf
*/
HRESULT WINAPI CFontsFolder::GetAttributesOf(UINT cidl, PCUITEMID_CHILD_ARRAY apidl, DWORD *rgfInOut)
{
    HRESULT hr = S_OK;

    TRACE ("(%p)->(cidl=%d apidl=%p mask=%p (0x%08x))\n", this,
           cidl, apidl, rgfInOut, rgfInOut ? *rgfInOut : 0);

    if (!rgfInOut)
        return E_INVALIDARG;
    if (cidl && !apidl)
        return E_INVALIDARG;

    if (*rgfInOut == 0)
        *rgfInOut = ~0;

    if (cidl == 0)
    {
        CComPtr<IShellFolder>            psfParent;
        LPCITEMIDLIST rpidl = NULL;

        hr = SHBindToParent(pidlRoot, IID_PPV_ARG(IShellFolder, &psfParent), (LPCITEMIDLIST *)&rpidl);
        if (SUCCEEDED(hr))
            SHELL32_GetItemAttributes (psfParent, rpidl, rgfInOut);
    }
    else
    {
        while (cidl > 0 && *apidl)
        {
            pdump (*apidl);
            SHELL32_GetItemAttributes (this, *apidl, rgfInOut);
            apidl++;
            cidl--;
        }
    }

    /* make sure SFGAO_VALIDATE is cleared, some apps depend on that */
    *rgfInOut &= ~SFGAO_VALIDATE;

    TRACE ("-- result=0x%08x\n", *rgfInOut);
    return hr;
}